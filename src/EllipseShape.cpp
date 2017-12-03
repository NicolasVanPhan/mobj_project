
#include "EllipseShape.h"

namespace Netlist {

  EllipseShape::EllipseShape      ( Symbol* owner, const Box& box )
    :Shape(owner), box_(box)
  { }

  EllipseShape::EllipseShape      ( Symbol* owner, int x1, int x2, int y1, int y2 )
    :Shape(owner), box_(x1, x2, y1, y2)
  { }

  EllipseShape::~EllipseShape      ( ) 
  { }

  Box     Ellipseshape::getBoundingBox () const
  { return box_; }

}

