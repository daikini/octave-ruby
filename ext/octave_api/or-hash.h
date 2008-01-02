#ifndef OR_HASH_DEFINED_H_
#define OR_HASH_DEFINED_H_

#include "ruby.h"
#include "octave-includes.h"

class OR_Hash
{
  private:
    VALUE ruby_val;
    
  public:
    OR_Hash(VALUE r) : ruby_val(r) { };
    ~OR_Hash();
  
    octave_value to_octave();
};

#endif /* OR_HASH_DEFINED_H_ */
