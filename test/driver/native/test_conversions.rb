$:.unshift File.dirname(__FILE__) + "/../../../lib"
require 'test/unit'
require 'octave'
require 'octave/driver/native/driver'
require 'rubygems'
require 'mocha'
require 'yaml'

class ConversionsTest < Test::Unit::TestCase
  def setup
    @driver = Octave::Driver::Native::Driver.new
    @driver.feval "eval", "function r = to_octave(val); r = val; endfunction"
  end
  
  def to_octave_to_ruby(value)
    @driver.feval "to_octave", value
  end
  
  def assert_octave_and_ruby_equal(value)
    result = to_octave_to_ruby(value)
    assert_equal value, result
    assert_equal value.class, result.class
  end
  
  def test_should_convert_string
    assert_octave_and_ruby_equal "foo"
  end
  
  def test_should_convert_true
    assert_octave_and_ruby_equal true
  end
  
  def test_should_convert_false
    assert_octave_and_ruby_equal false
  end
  
  def test_should_convert_nil
    assert_octave_and_ruby_equal nil
  end
  
  def test_should_convert_float
    assert_octave_and_ruby_equal 12.345
  end
  
  def test_should_convert_fixnum
    # Fixnums are sent to and returned from Octave as Float
    result = to_octave_to_ruby(12345)
    assert_equal 12345.0, result
    assert_instance_of Float, result
  end
  
  def test_should_convert_array
    assert_octave_and_ruby_equal [1, nil, 3.0]
    assert_octave_and_ruby_equal [1, "2", false, ["foo", "bar", "baz"]]
  end
  
  def test_should_convert_hash
    assert_octave_and_ruby_equal "foo" => "bar"
    assert_octave_and_ruby_equal "foo" => [1,2,3]
    assert_octave_and_ruby_equal "foo" => { "bar" => [1,2,3, [4,5,6]] }
    assert_octave_and_ruby_equal "foo" => { "bar" => [1,2,3, [4,5,6]], "baz" => "buz", "bob" => [7,8,9] }
  end
  
  def test_should_convert_octave_matrix
    matrix = Octave::Matrix.new(3, 3)
    3.times { |m| 3.times { |n| matrix[m, n] = rand } }
    matrix[1, 1] = nil
    
    assert_octave_and_ruby_equal matrix
  end
  
  def test_should_convert_a_0x0_octave_matrix_to_an_empty_array
    matrix = Octave::Matrix.new(0, 0)
    
    expected_array = []
    result = to_octave_to_ruby(matrix)
    
    assert_equal expected_array, result
    assert_instance_of Array, result
  end
  
  def test_should_convert_an_empty_ruby_array
    assert_octave_and_ruby_equal []
  end
  
  def test_should_convert_a_1xn_octave_matrix_to_an_array
    matrix = Octave::Matrix.new(1, 3)
    matrix[0, 0] = 1
    matrix[0, 1] = 2
    matrix[0, 2] = 3
    
    expected_array = [1,2,3]
    result = to_octave_to_ruby(matrix)
    
    assert_equal expected_array, result
    assert_instance_of Array, result
  end
  
  def test_should_convert_an_nx1_octave_matrix_to_an_array
    matrix = Octave::Matrix.new(3, 1)
    matrix[0, 0] = 1
    matrix[1, 0] = 2
    matrix[2, 0] = 3
    
    expected_array = [1,2,3]
    result = to_octave_to_ruby(matrix)
    
    assert_equal expected_array, result
    assert_instance_of Array, result
  end
  
  def test_should_convert_octave_struct_matrix
    struct_matrix = Octave::StructMatrix.new(17, 2, "name", "age", "married", "cats", "car")
    17.times do |m|
      2.times do |n|
        struct_matrix[m, n]["name"] = "Bob #{m}.#{n}"
        struct_matrix[m, n]["age"] = (rand * 100).to_i
        struct_matrix[m, n]["married"] = (rand > 0.5)
        struct_matrix[m, n]["cats"] = { "name" => "Kitty #{m}.#{n}" }
        struct_matrix[m, n]["car"] = nil
      end
    end
    
    assert_octave_and_ruby_equal struct_matrix
  end
  
  def test_should_convert_a_1x1_struct_matrix_to_a_hash
    struct_matrix = Octave::StructMatrix.new(1, 1, "foo")
    struct_matrix[0,0]["foo"] = { "bar" => [1,2,3] }
    
    expected_hash = { "foo" => { "bar" => [1,2,3] } }
    result = to_octave_to_ruby(struct_matrix)
    
    assert_equal expected_hash, result
    assert_instance_of Hash, result
  end
  
  def test_should_convert_octave_cell_matrix
    cell_matrix = Octave::CellMatrix.new(3, 3)
    cell_matrix[0, 0] = 1
    cell_matrix[1, 0] = "2"
    cell_matrix[2, 0] = false
    
    assert_octave_and_ruby_equal cell_matrix
  end
  
  def test_should_convert_a_1x1_cell_matrix_to_value
    cell_matrix = Octave::CellMatrix.new(1, 1)
    cell_matrix[0,0] = [1, 2, 3]
    
    assert_equal [1, 2, 3], to_octave_to_ruby(cell_matrix)
  end
  
  def test_should_convert_a_1xn_cell_matrix_to_an_array
    cell_matrix = Octave::CellMatrix.new(1, 3)
    cell_matrix[0,0] = "foo"
    cell_matrix[0,1] = "bar"
    cell_matrix[0,2] = "baz"
    
    assert_equal %w(foo bar baz), to_octave_to_ruby(cell_matrix)
  end
  
  def test_should_convert_a_nx1_cell_matrix_to_an_array
    cell_matrix = Octave::CellMatrix.new(3, 1)
    cell_matrix[0,0] = "foo"
    cell_matrix[1,0] = "bar"
    cell_matrix[2,0] = "baz"
    
    assert_equal %w(foo bar baz), to_octave_to_ruby(cell_matrix)
  end
  
  def test_should_convert_boolean_matrix
    assert_octave_and_ruby_equal [true, false, true]
    boolean_matrix = @driver.feval "eval", "x = [1,2]; (x > 2 | x < 2)"
    assert_equal [true, false], boolean_matrix
  end
end
