
#include "Shape.h"

namespace Netlist {
  
  Shape::Shape        ( Symbol* owner )
    :owner_(owner)
  {
    owner->add(this);
  }

  Shape::~Shape       ()
  {
    owner->remove(this);
  }
}
