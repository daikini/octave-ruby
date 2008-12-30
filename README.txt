octave-ruby
    http://octave-ruby.rubyforge.org/
    jonathan@daikini.com
    A big thank you to Lipomics Technologies, Inc. http://www.lipomics.com for sponsoring this project.
    
== DESCRIPTION:
  
A Ruby interface to the Octave interpreted language.

== FEATURES:
  
* Data type conversion between Octave and Ruby String, Boolean, Nil and Numeric values
* Matrix, CellMatrix and StructMatrix helper classes for working with Octave matrices

== USAGE:

  require 'octave'
  
  engine = Octave::Engine.new
  engine.eval "123.456 * 789.101112"
  engine.rand(10)
  
  matrix = Octave::Matrix.new(20, 400)
  20.times { |m| 400.times { |n| matrix[m, n] = rand } }
  engine.put_variable("m", matrix)
  
  engine.save "/tmp/20_x_400_matrix"

== REQUIREMENTS:

* Octave
* GCC or some other compiler to build the included extension
* Mocha (For testing only)

== INSTALL:

Simply do the following, after installing Octave:

  * ruby setup.rb config
  * ruby setup.rb setup
  * ruby setup.rb install

Alternatively, you can download and install the RubyGem package for
octave-ruby (you must have RubyGems and Octave installed, first):

  * gem install octave-ruby

If you have Octave installed in a non-standard location, you can specify the location of the include and lib files by doing:

  * gem install octave-ruby -- --with-octave-include=/usr/local/include/octave-3.0.0/octave \
     --with-octave-lib=/usr/local/lib/octave-3.0.0 \
     --with-dep-include=/usr/local/include/octave-3.0.0
  
== LICENSE

octave-ruby is licensed under the GPL License.

Copyright (c) 2007 Jonathan Younger <jonathan.younger@lipomics.com>