#ifndef OR_STRING_DEFINED_H_
#define OR_STRING_DEFINED_H_

#include "ruby.h"
#include "octave-includes.h"

class OR_String
{
  private:
    VALUE ruby_val;
    octave_value octave_val;
    
  public:
    OR_String(VALUE r) : ruby_val(r) { };
    OR_String(octave_value o) : octave_val(o) { };
    ~OR_String();
  
    VALUE to_ruby();
    octave_value to_octave();
};

#endif /* OR_STRING_DEFINED_H_ */
