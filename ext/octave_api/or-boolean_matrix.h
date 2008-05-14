#ifndef OR_BOOLEAN_MATRIX_DEFINED_H_
#define OR_BOOLEAN_MATRIX_DEFINED_H_

#include "ruby.h"
#include "octave-includes.h"

class OR_BooleanMatrix
{
  private:
    VALUE ruby_val;
    octave_value octave_val;

  public:
    OR_BooleanMatrix(octave_value o) : octave_val(o) { };
    ~OR_BooleanMatrix();
  
    VALUE to_ruby();
};

#endif /* OR_BOOLEAN_MATRIX_DEFINED_H_ */
