# -*- encoding: utf-8 -*-
lib = File.expand_path('../lib', __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require 'cicu/version'

Gem::Specification.new do |gem|
  gem.name          = "cicu"
  gem.version       = Cicu::VERSION
  gem.authors       = ["Benjamin Groessing"]
  gem.email         = ["contact@BYTEQ.com"]
  gem.description   = %q{ Custom ICU rulesets for collation in ruby - requires libicu }
  gem.summary       = %q{ Custom ICU rulesets for collation }
  gem.homepage      = "https://github.com/groe/cicu"
  gem.license       = "MIT"

  gem.add_development_dependency "rspec", ">= 2.13.0"
  gem.add_development_dependency "rake", ">= 1.9.1"
  gem.add_development_dependency "rake-compiler", ">= 0.8.3"

  gem.files         = `git ls-files`.split($/)
  gem.executables   = gem.files.grep(%r{^bin/}).map{ |f| File.basename(f) }
  gem.test_files    = gem.files.grep(%r{^(test|spec|features)/})
  gem.extensions    = gem.files.grep(%r{/extconf\.rb$})
  gem.require_paths = ["lib"]
end
