begin
  require 'octave_api'
rescue LoadError
  require File.dirname(__FILE__) + '/../../../../ext/octave_api/octave_api'
end

module Octave ; module Driver ; module Native
  class Driver
    def call(function_name, *args)
      API.Call function_name, args
    end
  end
end ; end ; end