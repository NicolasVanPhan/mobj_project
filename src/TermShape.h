
#ifndef NETLIST_BOXSHAPE_H
#define NETLIST_BOXSHAPE_H

#include <string>
#include <fstream>
#include <libxml/xmlreader.h>

namespace Netlist {

  class TermShape : public Shape {

    // Forward declaration

    public:
      enum NameAlign { TopLeft=1, TopRight, BottomLeft, BottomRight };

      /* ---------- Class function ---------- */
      static  bool        fromXml         ( Symbol*, xmlTextReaderPtr );

      /* ---------- Instance function ---------- */

      // Constructors and Destructors
                          TermShape       ( Symbol* owner, std::string name, int x, int y );
                          ~TermShape      ();

      // Accessors
              Box         getBoundingBox  () const;
      inline  Term*       getTerm         () const;
      inline  int         getX            () const;
      inline  int         getY            () const;
              void        toXml           ( std::ostream& ) const;

      // Modificators
      
    private:
      /* ---------- Attributes ---------- */
      int                 x_;
      int                 y;
      Term*               term_;
      NameAlign           align_;
  };

  inline  Term*       getTerm         () const
  { return term_; }

  inline  int         getX            () const
  { return x_; }

  inline  int         getY            () const
  { return y_; }
}

#endif
