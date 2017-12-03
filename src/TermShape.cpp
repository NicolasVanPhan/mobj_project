
#include "BoxShape.h"

namespace Netlist {

  TermShape::TermShape      ( Symbol* owner, int x, int y, Term* term, NameAlign align )
    :Shape(owner), x_(x), y_(y), term_(NULL), align_(TopLeft)
  {
    term_ = getCell()->getTerm(name);
  }

  TermShape::~TermShape     ()
  {
  }


  static  bool        TermShape::fromXml        ( Symbol*, xmlTextReaderPtr )
  {
  }


  Box                 TermShape::getBoundingBox() const
  { return Box(x_, y_, x_, y_); }

  void                TermShape::toXml          ( std::ostream& ) const
  {
  }


}

