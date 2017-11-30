
#ifndef NETLIST_BOXSHAPE_H
#define NETLIST_BOXSHAPE_H

#include <string>
#include <fstream>
#include <libxml/xmlreader.h>

namespace Netlist {

  class BoxShape : public Shape {

    // Forward declaration

    public:
      /* ---------- Class function ---------- */
      /* ---------- Instance function ---------- */

      // Constructors and Destructors
                          BoxShape       ( Symbol* owner, const Box& box );
                          BoxShape       ( Symbol* owner, int x1, int y1, int x2, int y2 );
                          ~BoxShape      ();

      // Accessors
      Box                 getBoundingBox() const;

      // Modificators
      
    private:
      /* ---------- Attributes ---------- */
      Box                 box_;
  };
}

#endif
