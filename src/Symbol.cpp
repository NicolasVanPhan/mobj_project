
#include "Symbol.h"

namespace Netlist {

  Symbol::Symbol ( Cell* owner )
    : owner_(owner), shapes_()
  {
  }

  Symbol::Symbol ( const Symbol& symbol)
    : owner_(symbol.getCell()), shapes_(symbol.getShapes()) // for shapes, the copy CTOR is called
  {
  }

  Symbol::~Symbol ()
  {
  }


  Cell*              Symbol::getCell         () const
  { return owner_; }

  Box                Symbol::getBoundingBox  () const
  {
    Box   bbox;
    std::vector<Shape*>::iterator it;
    for (it = shapes_.begin(); it != shapes_.end(); ++shapes_ ) {
      bbox.merge((*it)->getBoundingBox());
    }
    return bbox;
  }

  Point              Symbol::getTermPosition ( Term* ) const
  {
    // Which position should be returned ?
  }

  TermShape*         Symbol::getTermShape    ( Term* term) const
  {
    std::vector<Shape*>::const_iterator it;
    TermShape*    tshape;
    for (it = shapes_.begin(); it != shapes_.end(); ++it) {
      tshape = dynamic_cast<TermShape*>(*it);
      // if the current Shape* is indeed a TermShape* and points to the given Term
      if (tshape != NULL and tshape->getTerm() == term)
        return tshape;
    }
    return NULL;
  }

  void               Symbol::add             ( Shape* shape )
  {
    shapes_.push_back(shape);
  }

  void               Symbol::remove          ( Shape* shape )
  {
  }

  void               Symbol::toXml           ( std::ostream& ) const
  {
  }

  static Symbol*     Symbol::fromXml         ( Cell*, xmlTextReaderPtr )
  {
  }

  Symbol&            Symbol::operator=       ( const Symbol& )
  {
  }
}

