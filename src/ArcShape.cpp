
#include "ArcShape.h"

namespace Netlist {

  ArcShape::ArcShape      ( Symbol* owner, const Box& box )
    :Shape(owner), box_(box), start_(start), span_(span)
  { }

  ArcShape::ArcShape      ( Symbol* owner, int x1, int x2, int y1, int y2 )
    :Shape(owner), box_(x1, x2, y1, y2), start_(start), span_(span)
  { }

  ArcShape::~ArcShape      ( ) 
  { }

  Box     Arcshape::getBoundingBox () const
  { return box_; }

}

