
#ifndef NETLIST_BOXSHAPE_H
#define NETLIST_BOXSHAPE_H

#include "Shape.h"
#include <string>
#include <fstream>
#include <vector>
#include <libxml/xmlreader.h>
#include "Symbol.h"

namespace Netlist {

  class Shape;
  class Term;
  class Box;
  class Symbol;

  class TermShape : public Shape {

    public:
      enum NameAlign { TopLeft=1, TopRight, BottomLeft, BottomRight };

      /* ---------- Class function ---------- */
      static  bool        fromXml         ( Symbol*, xmlTextReaderPtr );

      /* ---------- Instance function ---------- */

      // Constructors and Destructors
                          TermShape       ( Symbol* owner, std::string name, int x, int y, NameAlign align);
                          ~TermShape      ();

      // Accessors
              Box         getBoundingBox  () const;
      inline  Term*       getTerm         () const;
      inline  int         getX            () const;
      inline  int         getY            () const;
              void        toXml           ( std::ostream& ) const;
      static  std::string alignToString   ( NameAlign );

      // Modificators
      
    private:
      /* ---------- Attributes ---------- */
      int                 x_;
      int                 y_;
      Term*               term_;
      NameAlign           align_;
  };

  inline  Term*       TermShape::getTerm         () const
  { return term_; }

  inline  int         TermShape::getX            () const
  { return x_; }

  inline  int         TermShape::getY            () const
  { return y_; }
}

#endif
