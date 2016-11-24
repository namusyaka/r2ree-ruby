require 'rake/testtask'

begin
  require 'rake/extensiontask'
rescue LoadError
  abort 'rake-compiler is missing'
end

gemspec = Gem::Specification::load(File.expand_path('../r2ree.gemspec', __FILE__))

Rake::ExtensionTask.new('r2ree', gemspec) do |r|
  r.lib_dir = 'lib/'
end

task :checkout do
  sh 'git submodule update --init'
end

Rake::Task[:compile].prerequisites.insert(0, :checkout)

Rake::TestTask.new do |t|
  t.libs << 'test'
  t.test_files = Dir['test/**/test_*.rb']
  t.verbose = true
end

task :build do |t|
  sh 'cd ext/r2ree && ruby extconf.rb && make'
end

task default: [:compile, :test]
