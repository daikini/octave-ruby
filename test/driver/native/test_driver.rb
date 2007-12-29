$:.unshift "../../../lib"
require 'test/unit'
require 'octave'
require 'octave/driver/native/driver'
require 'rubygems'
require 'mocha'

class DriverTest < Test::Unit::TestCase
  include Octave::Driver::Native
  
  def setup
    @driver = Driver.new
  end
  
  def test_call
    API.expects(:Call).with("some_function_name", ["argument 1", "argument 2"])
    @driver.call("some_function_name", "argument 1", "argument 2")
  end
end