# Loads mkmf which is used to make makefiles for Ruby extensions
require 'mkmf'

octave_dirs = dir_config( "octave", "/usr/local/octave/include", "/usr/local/octave/lib" )
dep_dirs = dir_config( "dep", "/usr/local/include", "/usr/local/lib" )
if have_header("octave.h" ) &&
  have_library("octinterp", "octave_main" ) &&
  have_library("octave") &&
  have_library("cruft")

  
  if Config::CONFIG["arch"] =~ /-darwin\d/
    CONFIG['LDSHARED'] = "g++ -pipe -bundle"
    if octave_dirs.any?
      octave_dirs << File.dirname(octave_dirs.first)
      octave_includes = (dep_dirs + octave_dirs).collect { |dir| "-I#{dir}" }.join(" ")
      with_cppflags(octave_includes) { true }
    end
  else
    CONFIG['LDSHARED'] = "g++ -shared"
  end
  
  create_makefile( "octave_api" )
end
