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
  
  def test_feval
    API.expects(:feval).with("some_function_name", ["argument 1", "argument 2"])
    @driver.feval("some_function_name", "argument 1", "argument 2")
  end
  
  def test_put_and_get_variable
    assert_equal "some_value", @driver.put_variable("some_variable_name", "some_value")
    assert_equal "some_value", @driver.get_variable("some_variable_name")
  end
  
  def test_putting_variable_with_same_name_multiple_times
    assert_equal "foo", @driver.put_variable("some_variable_name", "foo")
    assert_equal "foo", @driver.get_variable("some_variable_name")
    
    assert_equal "bar", @driver.put_variable("some_variable_name", "bar")
    assert_equal "bar", @driver.get_variable("some_variable_name")
    
    assert_equal "baz", @driver.put_variable("some_variable_name", "baz")
    assert_equal "baz", @driver.get_variable("some_variable_name")
  end
end