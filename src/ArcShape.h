
#ifndef NETLIST_ARCSHAPE_H
#define NETLIST_ARCSHAPE_H

#include <string>
#include <fstream>
#include <vector>
#include <libxml/xmlreader.h>
#include "Shape.h"

namespace Netlist {

  class Shape;
  class Symbol;

  class ArcShape : public Shape {

    // Forward declaration

    public:
      /* ---------- Class function ---------- */
      static  ArcShape*        fromXml         ( Symbol*, xmlTextReaderPtr );

      /* ---------- Instance function ---------- */

      // Constructors and Destructors
      ArcShape        ( Symbol* owner, const Box& box, int start, int span);
      ArcShape        ( Symbol* owner, int x1, int y1, int x2, int y2,
          int start, int span);
                          ~ArcShape       ();

      // Accessors
      Box                 getBoundingBox  () const;
      void                toXml           ( std::ostream& ) const;
      inline int          getStart        ( ) const;
      inline int          getSpan         ( ) const;

      // Modificators
      
    private:
      /* ---------- Attributes ---------- */
      Box                 box_;
      int                 start_;
      int                 span_;
  };

  inline int          ArcShape::getStart        ( ) const
  { return start_; }

  inline int          ArcShape::getSpan         ( ) const
  { return span_; }

}

#endif
