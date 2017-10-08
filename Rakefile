require "bundler/gem_tasks"
require "rake/extensiontask"

Rake::ExtensionTask.new "teensy_rawhid" do |ext|
  ext.lib_dir = "lib/rawhid"
end

task :default => :spec
Rake::ExtensionTask.new 'rawhid'
