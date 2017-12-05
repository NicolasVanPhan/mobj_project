
#ifndef NETLIST_BOXSHAPE_H
#define NETLIST_BOXSHAPE_H

#include <string>
#include <fstream>
#include <vector>
#include <libxml/xmlreader.h>
#include "Shape.h"
#include "XmlUtil.h"

namespace Netlist {

  class Shape;
  class Symbol;

  class BoxShape : public Shape {

    // Forward declaration

    public:
      /* ---------- Class function ---------- */
      static  BoxShape*        fromXml        ( Symbol*, xmlTextReaderPtr );

      /* ---------- Instance function ---------- */

      // Constructors and Destructors
                          BoxShape       ( Symbol* owner, const Box& box );
                          BoxShape       ( Symbol* owner, int x1, int y1, int x2, int y2 );
                          ~BoxShape      ();

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
