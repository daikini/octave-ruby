module Octave
  
  # The Matrix class is used for storing values that are sent to
  # or received from Octave numeric matrices
  # Usage:
  #
  #   require 'octave'
  #
  #   matrix = Octave::Matrix.new(20, 400)
  #   20.times { |m| 400.times { |n| matrix[m, n] = rand } }
  #
  class Matrix
    include Comparable
    
    attr_reader :m # Rows
    attr_reader :n # Columns
    attr_reader :cells
    
    # Creates a new Matrix with the given dimensions for row and column size
    def initialize(m, n)
      @m, @n = m, n
      @cells = Array.new(m) { Array.new(n) }
    end
    
    # Gets the value at the given row and column position
    def [](m, n)
      @cells[m][n]
    end
    
    # Sets the given value at the row and column position
    def []=(m, n, value)
      @cells[m][n] = value
    end
    
    # Enables comparisons of matrices to each other
    def ==(other)
      @cells == other.cells
    end
  end
  
  # The CellMatrix class is used for storing values that are sent to
  # or received from Octave cell matrices.
  # Usage:
  #
  #   require 'octave'
  #
  #   cell_matrix = Octave::CellMatrix.new(20, 400)
  #   20.times { |m| 400.times { |n| cell_matrix[m, n] = rand.to_s } }
  #
  class CellMatrix < Matrix; end
  
  # The StructMatrix class is used for storing hash values that are sent to
  # or received from Octave struct matrices.
  # Usage:
  #
  #   require 'octave'
  #
  #   struct_matrix = Octave::StructMatrix.new(17, 1, "name", "age", "married"
  #   17.times do |m|
  #     struct_matrix[m, 0]["name"] = "Bob #{m}"
  #     struct_matrix[m, 0]["age"] = (rand * 100).to_i
  #     struct_matrix[m, 0]["married"] = (rand > 0.5)
  #   end
  #
  #   p struct_matrix[16, 0]
  #
  class StructMatrix < Matrix
    attr_reader :names
    
    # Creates a new StructMatrix with the given dimensions for row and column size
    # and the names of the attributes
    def initialize(m, n, *names)
      super(m, n)
      @names = names
      
      # Populate the matrix with a hash using the names provided
      m.times do |row_index|
        n.times do |column_index|
          @cells[row_index][column_index] = names.inject({}) { |s,e| s.merge( { e.to_s => nil } ) }
        end
      end
    end
  end
end