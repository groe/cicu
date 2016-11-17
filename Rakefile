require "bundler/gem_tasks"
require "rspec/core/rake_task"
require 'rake/extensiontask'

desc "Cicu unit tests"
RSpec::Core::RakeTask.new(:test) do |t|
  t.pattern = "spec/*_spec.rb"
  t.verbose = true
end

gemspec = Gem::Specification.load('cicu.gemspec')
Rake::ExtensionTask.new do |ext|
  ext.name = 'cicu'
  ext.source_pattern = "*.{c,h}"
  ext.ext_dir = 'ext/cicu'
  ext.lib_dir = 'lib/cicu'
  ext.gem_spec = gemspec
end

task :default => [:compile, :test]
