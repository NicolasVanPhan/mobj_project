
#include "BoxShape.h"

namespace Netlist {

  BoxShape::BoxShape      ( Symbol* owner, const Box& box )
    :Shape(owner), box_(box)
  { }

  BoxShape::BoxShape      ( Symbol* owner, int x1, int x2, int y1, int y2 )
    :Shape(owner), box_(x1, x2, y1, y2)
  { }

  BoxShape::~BoxShape      ( ) 
  { }

  Box     Boxshape::getBoundingBox () const
  { return box_; }

}

