require 'mkmf'

$CXXFLAGS += " -std=c++11 -Wall -Wextra -I../../r2ree/include"

CWD = File.expand_path(__dir__)
R2REE_DIR = File.join(CWD, '..', '..', 'r2ree')

Dir.chdir(R2REE_DIR) do
  FileUtils.cp File.join('include', 'r2ree.hh'), File.join('..', 'ext', 'r2ree', 'libr2ree.hh')
  FileUtils.cp File.join('src',     'r2ree.cc'), File.join('..', 'ext', 'r2ree', 'libr2ree.cc')
end

create_makefile('r2ree/r2ree')
