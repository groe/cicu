#include "cicu.h"

#include <unicode/ustring.h>

#define BUF_SIZE 10000

static void str_to_utf16(VALUE string, UChar *ustr, int32_t *ulen)
{
  UErrorCode status = U_ZERO_ERROR;
  string = StringValue(string);
  u_strFromUTF8(ustr, BUF_SIZE, ulen, RSTRING_PTR(string), RSTRING_LEN(string), &status);
  if (status == U_INVALID_CHAR_FOUND) ulen = 0;
}

static VALUE ruleset_allocate(VALUE klass)
{
  UCollator *collator = NULL;

  return Data_Wrap_Struct(klass, NULL, ruleset_deallocate, collator);
}

static void ruleset_deallocate(void * collator)
{
  if(collator != NULL) {
    ucol_close(collator);
  }
}

static VALUE ruleset_initialize(VALUE self, VALUE rules) {
  UChar uRules[BUF_SIZE];
  UErrorCode status = U_ZERO_ERROR;
  int32_t uRulesLen = 0;
  UCollator *collator;

  if (TYPE(rules) != T_STRING) {
    rb_raise(rb_eTypeError, "rules must be a string");
  }
  if (RSTRING_LEN(rules) > BUF_SIZE) {
    rb_raise(rb_eArgError, "given ruleset string exceeds buffer size");
  }

  str_to_utf16(rules, uRules, &uRulesLen);
  collator = ucol_openRules(uRules, uRulesLen, UCOL_ON, UCOL_DEFAULT_STRENGTH, NULL, &status); 

  if (U_SUCCESS(status)) {
    DATA_PTR(self) = collator;
  }
  else {
    rb_raise(rb_eArgError, u_errorName(status));
  }

  return self;
}

static VALUE ruleset_sort_key(VALUE self, VALUE string) {
  UCollator *collator;
  char str[BUF_SIZE];
  UChar ustr[BUF_SIZE];
  int32_t len = 0;
  int32_t uLen = 0;

  if (TYPE(string) != T_STRING) {
    rb_raise(rb_eTypeError, "sort_key expects a string argument");
  }
  if (RSTRING_LEN(string) > BUF_SIZE) {
    rb_raise(rb_eArgError, "given string for sort_key exceeds buffer size");
  }

  Data_Get_Struct(self, UCollator, collator);
  str_to_utf16(string, ustr, &uLen);
  len = ucol_getSortKey(collator, ustr, uLen, (uint8_t*)str, BUF_SIZE);

  return rb_str_new(str, len-1);
}

void Init_cicu() {
  VALUE rb_mCicu = rb_define_module("Cicu");
  VALUE rb_cRuleset = rb_define_class_under(rb_mCicu, "Ruleset", rb_cObject);
  rb_define_alloc_func(rb_cRuleset, ruleset_allocate);
  rb_define_method(rb_cRuleset, "initialize", ruleset_initialize, 1);
  rb_define_method(rb_cRuleset, "sort_key", ruleset_sort_key, 1);
}
