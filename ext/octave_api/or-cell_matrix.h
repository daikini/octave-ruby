#ifndef OR_CELL_MATRIX_DEFINED_H_
#define OR_CELL_MATRIX_DEFINED_H_

#include "ruby.h"
#include "octave-includes.h"

class OR_CellMatrix
{
  private:
    VALUE ruby_val;
    octave_value octave_val;
    
  public:
    OR_CellMatrix(VALUE r) : ruby_val(r) { };
    OR_CellMatrix(octave_value o) : octave_val(o) { };
    ~OR_CellMatrix();
  
    VALUE to_ruby();
    octave_value to_octave();
};

#endif /* OR_CELL_MATRIX_DEFINED_H_ */
