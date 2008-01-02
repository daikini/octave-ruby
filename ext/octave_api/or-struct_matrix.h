#ifndef OR_STRUCT_MATRIX_DEFINED_H_
#define OR_STRUCT_MATRIX_DEFINED_H_

#include "ruby.h"
#include "octave-includes.h"

class OR_StructMatrix
{
  private:
    VALUE ruby_val;
    octave_value octave_val;
    
  public:
    OR_StructMatrix(VALUE r) : ruby_val(r) { };
    OR_StructMatrix(octave_value o) : octave_val(o) { };
    ~OR_StructMatrix();
  
    VALUE to_ruby();
    octave_value to_octave();
};

#endif /* OR_STRUCT_MATRIX_DEFINED_H_ */
