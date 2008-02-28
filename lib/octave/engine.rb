module Octave
  
  # The Engine class encapsulates a single connection to a Octave instance.
  # Usage:
  #
  #   require 'octave'
  #
  #   engine = Octave::Engine.new
  #   engine.eval "123.456 * 789.101112"
  #   engine.rand(10)
  #
  # Functions are called in Octave by calling a method on the
  # engine with the function name of interest and passing any parameters as needed.
  class Engine
    # A reference to the underlying Octave driver used by this engine.
    attr_reader :driver
    
    # Create a new Engine object that connects to Octave
    def initialize(options = {})
      load_driver(options[:driver])
      
      if block_given?
        begin
          yield self
        ensure
          close
        end
      end
    end
    
    # Put a variable in to Octave with the given name
    def put_variable(name, value)
      @driver.put_variable(name, value)
    end
    
    # Retrieve a variable from Octave with the given name
    def get_variable(name)
      @driver.get_variable(name)
    end
    
    # Call the Octave function via a given name
    def method_missing(method_id, *args)
      method_name = method_id.id2name
      
      @driver.feval(method_name, *args)
    end
    
    private
      # Loads the corresponding driver, or if it is nil, attempts to locate a
      # suitable driver.
      def load_driver(driver)
        case driver
          when Class
            # do nothing--use what was given
          when Symbol, String
            require "octave/driver/#{driver.to_s.downcase}/driver"
            driver = Octave::Driver.const_get(driver)::Driver
          else
            [ "Native" ].each do |d|
              begin
                require "octave/driver/#{d.downcase}/driver"
                driver = Octave::Driver.const_get(d)::Driver
                break
              rescue SyntaxError
                raise
              rescue ScriptError, Exception, NameError
              end
            end
            raise "no driver for octave found" unless driver
        end

        @driver = driver.new
      end
  end
end
