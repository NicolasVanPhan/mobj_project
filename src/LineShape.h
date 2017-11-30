
#ifndef NETLIST_BOXSHAPE_H
#define NETLIST_BOXSHAPE_H

#include <string>
#include <fstream>
#include <libxml/xmlreader.h>

namespace Netlist {

  class LineShape : public Shape {

    // Forward declaration

    public:
      /* ---------- Class function ---------- */
      /* ---------- Instance function ---------- */

      // Constructors and Destructors
                          LineShape       ( Symbol* owner, int x1, int y1, int x2, int y2 );
                          ~LineShape      ();

      // Accessors
      Box                 getBoundingBox() const;

      // Modificators
      
    private:
      /* ---------- Attributes ---------- */
      int                 x1_;
      int                 y1_;
      int                 x2_;
      int                 y2_;
  };
}

#endif
