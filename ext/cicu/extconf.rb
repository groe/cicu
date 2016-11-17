# ext/cicu/extconf.rb
require 'mkmf'
have_library('icui18n')
have_library('icuio')
create_makefile('cicu/cicu')
