require 'rake/testtask'

Rake::TestTask.new do |t|
  t.libs << 'test'
  t.test_files = Dir['test/**/test_*.rb']
  t.verbose = true
end

task :build do |t|
  sh 'cd ext/r2ree && ruby extconf.rb && make'
end

task default: :test
