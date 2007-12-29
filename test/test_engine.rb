require 'test/unit'
require 'octave'
require 'octave/engine'
require 'rubygems'
require 'mocha'

class Driver
end

class EngineTest_Init < Test::Unit::TestCase
  def test_new
    driver = mock()
    Driver.expects(:new).returns(driver)
    
    engine = Octave::Engine.new(:driver => Driver)
  end
  
  def test_new_with_invalid_driver
    exception = assert_raise(LoadError) do
      engine = Octave::Engine.new(:driver => "foo")
    end
    assert_equal "no such file to load -- octave/driver/foo/driver", exception.message
    
    exception = assert_raise(LoadError) do
      engine = Octave::Engine.new(:driver => :bar)
    end
    assert_equal "no such file to load -- octave/driver/bar/driver", exception.message
  end
  
  def test_new_with_native_driver
    assert_nothing_raised do
      engine = Octave::Engine.new
    end
  end
end

class EngineTest < Test::Unit::TestCase
  def setup
    @driver = mock()
    @handle = mock()
    Driver.expects(:new).returns(@driver)
    
    @engine = Octave::Engine.new(:driver => Driver)
  end
  
  def test_method_missing
    @driver.expects(:call).with("some_method_name", "argument 1", "argument 2")
    @engine.some_method_name("argument 1", "argument 2")
  end
end