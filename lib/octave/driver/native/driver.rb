begin
  require 'octave_api'
rescue LoadError
  require File.dirname(__FILE__) + '/../../../../ext/octave_api/octave_api'
end

module Octave ; module Driver ; module Native
  class Driver
    def feval(function_name, *args)
      API.feval function_name, args
    end
  end
end ; end ; end