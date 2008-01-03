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
      global_name = "octave_ruby_#{name}"
      feval("eval", "function octave_ruby_put_variable(value) global #{global_name}; #{global_name} = value; endfunction")
      feval("octave_ruby_put_variable", value)
      result = feval("eval", "global #{global_name}; #{name} = #{global_name}")
      feval("clear", global_name)
      result
    end
    
    def get_variable(name)
      feval("eval", name)
    end  
  end
end ; end ; end