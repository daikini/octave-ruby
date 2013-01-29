Gem::Specification.new do |s|
  s.name = %q{octave-ruby}
  s.version = "2.0.2"

  s.required_rubygems_version = Gem::Requirement.new(">= 0") if s.respond_to? :required_rubygems_version=
  s.authors = ["Jonathan Younger"]
  s.date = %q{2013-01-21}
  s.description = %q{== USAGE:  require 'octave'  engine = Octave::Engine.new engine.eval "123.456 * 789.101112" engine.rand(10)  matrix = Octave::Matrix.new(20, 400) 20.times { |m| 400.times { |n| matrix[m, n] = rand } } engine.put_variable("m", matrix)  engine.save "/tmp/20_x_400_matrix"  == REQUIREMENTS:  * Octave * GCC or some other compiler to build the included extension * Mocha (For testing only)}
  s.email = ["jonathan@daikini.com"]
  s.extensions = ["ext/octave_api/extconf.rb"]
  s.extra_rdoc_files = ["History.txt", "LICENSE.txt", "Manifest.txt", "README.txt"]
  s.files = ["History.txt", "LICENSE.txt", "Manifest.txt", "README.txt", "Rakefile", "ext/octave_api/MANIFEST", "ext/octave_api/extconf.rb", "ext/octave_api/octave-includes.h", "ext/octave_api/octave-ruby.cpp", "ext/octave_api/octave-ruby.h", "ext/octave_api/octave_api.c", "ext/octave_api/octave_api.h", "ext/octave_api/or-array.cpp", "ext/octave_api/or-array.h", "ext/octave_api/or-boolean_matrix.cpp", "ext/octave_api/or-boolean_matrix.h", "ext/octave_api/or-cell_matrix.cpp", "ext/octave_api/or-cell_matrix.h", "ext/octave_api/or-hash.cpp", "ext/octave_api/or-hash.h", "ext/octave_api/or-matrix.cpp", "ext/octave_api/or-matrix.h", "ext/octave_api/or-string.cpp", "ext/octave_api/or-string.h", "ext/octave_api/or-struct_matrix.cpp", "ext/octave_api/or-struct_matrix.h", "ext/octave_api/or-variable.cpp", "ext/octave_api/or-variable.h", "lib/octave.rb", "lib/octave/driver/native/driver.rb", "lib/octave/engine.rb", "lib/octave/matrix.rb", "lib/octave/version.rb", "octave-ruby.gemspec", "setup.rb", "test/driver/native/test_conversions.rb", "test/driver/native/test_driver.rb", "test/test_engine.rb"]
  s.has_rdoc = true
  s.homepage = %q{http://octave-ruby.rubyforge.org/}
  s.rdoc_options = ["--main", "README.txt"]
  s.require_paths = ["lib", "ext"]
  s.rubyforge_project = %q{octave-ruby}
  s.rubygems_version = %q{1.3.1}
  s.summary = %q{A Ruby interface to the Octave interpreted language.}
  s.test_files = ["test/driver/native/test_conversions.rb", "test/driver/native/test_driver.rb", "test/test_engine.rb"]
end
