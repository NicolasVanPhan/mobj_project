
#ifndef NETLIST_BOXSHAPE_H
#define NETLIST_BOXSHAPE_H

#include <string>
#include <fstream>
#include <libxml/xmlreader.h>

namespace Netlist {

  class ArcShape : public Shape {

    // Forward declaration

    public:
      /* ---------- Class function ---------- */
      static  bool        fromXml         ( Symbol*, xmlTextReaderPtr );

      /* ---------- Instance function ---------- */

      // Constructors and Destructors
                          ArcShape        ( Symbol* owner, const Box& box, int start, int span);
                          ArcShape        ( Symbol* owner, int x1, int y1, int x2, int y2, int start
                                            int span);
                          ~ArcShape       ();

      // Accessors
      Box                 getBoundingBox  () const;
      void                toXml           ( std::ostream& ) const;

      // Modificators
      
    private:
      /* ---------- Attributes ---------- */
      Box                 box_;
      int                 start_;
      int                 span_;
  };
}

#endif
