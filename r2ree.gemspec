# coding: utf-8
require File.expand_path('ext/r2ree/r2ree', __dir__)

Gem::Specification.new do |spec|
  spec.name          = "r2ree"
  spec.version       = R2ree::VERSION
  spec.authors       = ["namusyaka"]
  spec.email         = ["namusyaka@gmail.com"]

  spec.summary       = %q{r2ree radix tree implementation for ruby}
  spec.description   = spec.summary
  spec.homepage      = "https://github.com/namusyaka/r2ree-ruby"
  spec.license       = "MIT"
  spec.extensions    = %w[ext/r2ree/extconf.rb]

  spec.files         = `git ls-files -z`.split("\x0").reject { |f| f.match(%r{^(test|spec|features)/}) }
  spec.bindir        = "exe"
  spec.executables   = spec.files.grep(%r{^exe/}) { |f| File.basename(f) }
  spec.require_paths = ["lib"]
end
