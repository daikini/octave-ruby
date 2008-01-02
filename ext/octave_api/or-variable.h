#ifndef OR_VARIABLE_DEFINED_H_
#define OR_VARIABLE_DEFINED_H_

#include "ruby.h"
#include "octave-includes.h"

class OR_Variable
{
  private:
    VALUE ruby_val;
    octave_value octave_val;
    
  public:
    OR_Variable(VALUE r) : ruby_val(r) { };
    OR_Variable(octave_value o) : octave_val(o) { };
    ~OR_Variable();
  
    VALUE to_ruby();
    octave_value to_octave();
};

#endif /* OR_VARIABLE_DEFINED_H_ */
