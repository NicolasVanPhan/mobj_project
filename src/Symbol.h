// -*- explicit-buffer-name: "Symbol.h<M1-MOBJ/7>" -*-

#ifndef NETLIST_SYMBOL_H
#define NETLIST_SYMBOL_H

#include  <libxml/xmlreader.h>
#include  <string>
#include  <vector>
#include  "Box.h"
#include "TermShape.h"
#include "BoxShape.h"
#include "LineShape.h"
#include "ArcShape.h"
#include "EllipseShape.h"
#include  "Shape.h"

namespace Netlist {

  class Term;
  class Cell;

  class Shape;
  class TermShape;
  class LineShape;
  class BoxShape;
  class EllipseShape;
  class ArcShape;

  class Symbol {
    public:
                                        Symbol          ( Cell* );
                                       ~Symbol          ();
             Cell*                      getCell         () const;
             Box                        getBoundingBox  () const;
             Point                      getTermPosition ( Term* ) const;
             const TermShape*           getTermShape    ( Term* ) const;
      inline const std::vector<Shape*>  getShapes       () const;
             void                       add             ( Shape* );
             void                       remove          ( Shape* );
             void                       toXml           ( std::ostream& ) const;
      static Symbol*                    fromXml         ( Cell*, xmlTextReaderPtr );
    private:                                            
                                        Symbol          ( const Symbol& );
             Symbol&                    operator=       ( const Symbol& );
    private:
      Cell*                owner_;
      std::vector<Shape*>  shapes_;
  };


  inline const std::vector<Shape*> Symbol::getShapes () const { return shapes_; }


}  // Netlist namespace.

#endif  // NETLIST_SYMBOL_H
