#include "or-string.h"

OR_String::~OR_String() {}

VALUE OR_String::to_ruby()
{
  return rb_str_new2(octave_val.string_value().c_str());
}

octave_value OR_String::to_octave()
{
  return std::string(RSTRING(ruby_val)->ptr);
}
