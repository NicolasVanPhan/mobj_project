
#ifndef NETLIST_ELLIPSESHAPE_H
#define NETLIST_ELLIPSESHAPE_H

#include <string>
#include <fstream>
#include <vector>
#include <libxml/xmlreader.h>
#include "Shape.h"

namespace Netlist {

  class Shape;
  class Symbol;

  class EllipseShape : public Shape {

    // Forward declaration

    public:
      /* ---------- Class function ---------- */
      static  EllipseShape*        fromXml        ( Symbol*, xmlTextReaderPtr );

      /* ---------- Instance function ---------- */

      // Constructors and Destructors
                          EllipseShape       ( Symbol* owner, const Box& box );
                          EllipseShape       ( Symbol* owner, int x1, int y1, int x2, int y2 );
                          ~EllipseShape      ();

      // Accessors
      Box                 getBoundingBox() const;
      void                toXml          ( std::ostream& ) const;

      // Modificators
      
    private:
      /* ---------- Attributes ---------- */
      Box                 box_;
  };
}

#endif
