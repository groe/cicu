#include <ruby.h>
#include <unicode/ucol.h>

static void str_to_utf16(VALUE, UChar *, int32_t*);

static VALUE ruleset_allocate(VALUE);

static void ruleset_deallocate(void *);

static VALUE ruleset_initialize(VALUE, VALUE);

static VALUE ruleset_sort_key(VALUE, VALUE);

void Init_cicu();
