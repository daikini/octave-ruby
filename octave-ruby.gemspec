Gem::Specification.new do |s|
  s.name     = "octave-ruby"
  s.version  = "1.0.9"
  s.date     = "2008-12-30"
  s.summary  = "A Ruby interface to the Octave interpreted language"
  s.email    = "jonathan@daikini.com"
  s.homepage = "http://github.com/daikini/octave-ruby"
  s.description = "A Ruby interface to the Octave interpreted language."
  s.has_rdoc = true
  s.authors  = ["Jonathan Younger"]
  s.files    = [
    "History.txt",
    "LICENSE.txt",
    "Manifest.txt",
    "README.txt",
    "Rakefile",
    "ext/octave_api/MANIFEST",
    "ext/octave_api/Makefile",
    "ext/octave_api/extconf.rb",
    "ext/octave_api/octave-includes.h",
    "ext/octave_api/octave-ruby.cpp",
    "ext/octave_api/octave-ruby.h",
    "ext/octave_api/octave_api.c",
    "ext/octave_api/octave_api.h",
    "ext/octave_api/or-array.cpp",
    "ext/octave_api/or-array.h",
    "ext/octave_api/or-boolean_matrix.cpp",
    "ext/octave_api/or-boolean_matrix.h",
    "ext/octave_api/or-cell_matrix.cpp",
    "ext/octave_api/or-cell_matrix.h",
    "ext/octave_api/or-hash.cpp",
    "ext/octave_api/or-hash.h",
    "ext/octave_api/or-matrix.cpp",
    "ext/octave_api/or-matrix.h",
    "ext/octave_api/or-string.cpp",
    "ext/octave_api/or-string.h",
    "ext/octave_api/or-struct_matrix.cpp",
    "ext/octave_api/or-struct_matrix.h",
    "ext/octave_api/or-variable.cpp",
    "ext/octave_api/or-variable.h",
    "lib/octave.rb",
    "lib/octave/driver/native/driver.rb",
    "lib/octave/engine.rb",
    "lib/octave/matrix.rb",
    "lib/octave/version.rb",
    "octave-ruby.gemspec",
    "setup.rb"
  ]
  s.test_files = [
    "test/driver/native/test_conversions.rb",
    "test/driver/native/test_driver.rb",
    "test/test_engine.rb"
  ]
  s.rdoc_options = ["--main", "README.txt"]
  s.extra_rdoc_files = ["History.txt", "Manifest.txt", "README.txt"]
end
