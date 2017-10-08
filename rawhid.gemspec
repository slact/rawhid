# coding: utf-8
lib = File.expand_path("../lib", __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require "rawhid/version"

Gem::Specification.new do |spec|
  spec.name          = "rawhid"
  spec.version       = RawHID::VERSION
  spec.authors       = ["Leo P."]
  spec.email         = ["junk@slact.net"]

  spec.summary       = "Ruby binding for Teensy RawHID C code"
  spec.description   = "same as above"
  spec.homepage      = ""
  spec.license       = "MIT"

  spec.files         = `git ls-files -z`.split("\x0").reject do |f|
    f.match(%r{^(test|spec|features)/})
  end

  spec.bindir        = "exe"
  spec.executables   = spec.files.grep(%r{^exe/}) { |f| File.basename(f) }
  spec.extensions = ["ext/teensy_rawhid/extconf.rb"]
  spec.require_paths = ["lib"]

  spec.add_development_dependency "bundler", "~> 1.15"
  spec.add_development_dependency "rake", "~> 10.0"
  spec.add_development_dependency "rake-compiler"
  spec.add_development_dependency "pry"
end
