
#ifndef NETLIST_SHAPE_H
#define NETLIST_SHAPE_H

#include <string>
#include <fstream>
#include <libxml/xmlreader.h>

namespace Netlist {

  class Shape {

    // Forward declaration

    public:
      /* ---------- Class function ---------- */
      /* ---------- Instance function ---------- */

      // Constructors and Destructors
                          Shape       ( Symbol* owner );
      virtual             ~Shape      ();

      // Accessors
      inline Symbol*      getSymbol   () const;
      virtual Box         getBoundingBox() const = 0;

      // Modificators
      //
    private:
      /* ---------- Attributes ---------- */
      Symbol*         owner_;
  };

  inline Symbol*          getSymbol () const
  { return owner_; }
}

#endif
