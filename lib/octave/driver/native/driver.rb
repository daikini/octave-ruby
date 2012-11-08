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
    
    def put_variable(name, value)
      API.put_variable(name, value)
    end
    
    def get_variable(name)
      API.get_variable(name)
    end  
  end
end ; end ; end