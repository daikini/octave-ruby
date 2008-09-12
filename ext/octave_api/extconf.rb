# Loads mkmf which is used to make makefiles for Ruby extensions
require 'mkmf'

octave_dirs = dir_config( "octave", "/usr/local/octave/include", "/usr/local/octave/lib" )
dep_dirs = dir_config( "dep", octave_dirs.first.split(File::SEPARATOR)[0..-3].join(File::SEPARATOR), octave_dirs.last.split(File::SEPARATOR)[0..-2].join(File::SEPARATOR) )

if have_header("octave.h" ) &&
  have_library("octave") &&
  have_library("cruft") &&
  have_library("octinterp", "octave_main" )
  
  if Config::CONFIG["arch"] =~ /-darwin\d/
    CONFIG['LDSHARED'] = "g++ -pipe -bundle"
    if octave_dirs.any?
      octave_dirs << File.dirname(octave_dirs.first)
      octave_includes = (dep_dirs + octave_dirs).collect { |dir| "-I#{dir}" }.join(" ")
      with_cppflags(octave_includes) { true }
    end
  else
    CONFIG['LDSHARED'] = "g++ -shared"
    if octave_dirs.any?
      octave_dirs << File.dirname(octave_dirs.first)
      octave_dirs << "/usr/local/include"
      octave_includes = (dep_dirs + octave_dirs).collect { |dir| "-I#{dir}" }.join(" ")
      with_cppflags(octave_includes) { true }
    end
  end
  
  create_makefile( "octave_api" )
end