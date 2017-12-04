
#ifndef NETLIST_SHAPE_H
#define NETLIST_SHAPE_H

#include <string>
#include <fstream>
#include <vector>
#include <libxml/xmlreader.h>
#include "TermShape.h"
#include "LineShape.h"
#include "BoxShape.h"
#include "ArcShape.h"
#include "EllipseShape.h"
#include "Shape.h"

namespace Netlist {

  class Box;

  class Symbol;

  class Shape {

    // Forward declaration

    public:
      /* ---------- Class function ---------- */
      static Shape*       fromXml ( Symbol*, xmlTextReaderPtr );

      /* ---------- Instance function ---------- */

      // Constructors and Destructors
                          Shape       ( Symbol* owner );
      virtual             ~Shape      ();

      // Accessors
      inline  Symbol*     getSymbol   () const;
      virtual Box         getBoundingBox() const = 0;
      
      // Modificators
      //

      virtual void toXml       ( std::ostream& ) const;  

    private:
      /* ---------- Attributes ---------- */
      Symbol*         owner_;
  };

  inline Symbol*          Shape::getSymbol () const
  { return owner_; }
}

#endif
