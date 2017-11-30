
#include "LineShape.h"

namespace Netlist {

  LineShape::LineShape        ( Symbol* owner, int x1, int y1, int x2, int y2)
    :Shape(owner),
    x1_(x1),
    x2_(x2),
    y1_(y1),
    y2_(y2),
  {
  }

  LineShape::~LineShape        ( )
  { }

  Box     LineShape::getBoundingBox () const
  {
    return Box(std::min(x1, x2), std::min(y1, y2), std::max(x1, x2), std::max(y1, y2));
  }

}

