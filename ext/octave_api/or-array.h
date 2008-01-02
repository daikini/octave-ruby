#ifndef OR_ARRAY_DEFINED_H_
#define OR_ARRAY_DEFINED_H_

#include "ruby.h"
#include "octave-includes.h"

class OR_Array
{
  private:
    VALUE ruby_val;
    
    bool should_convert_to_cell_matrix();
  public:
    OR_Array(VALUE r) : ruby_val(r) { };
    ~OR_Array();
  
    octave_value to_octave();
};

#endif /* OR_ARRAY_DEFINED_H_ */
