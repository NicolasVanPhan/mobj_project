
#ifndef NETLIST_INSTANCE_H
#define NETLIST_INSTANCE_H

#include <string>
#include "Cell.h"
#include "Term.h"
#include "Point.h"
#include "Net.h"
#include "Indentation.h"

namespace Netlist {

  // Forward declaration
  class Cell;
  class Term;
  class Point;
  class Net;

  class Instance {
    public :
      /* ---------------- Functions -------------- */
      // CTOR and DTOR
      Instance    ( Cell* owner, Cell* model, const std::string& );
      ~Instance   ();

      // Accessors
      const std::string&        getName       () const;
      Cell*                     getMasterCell () const;
      Cell*                     getCell       () const;
      const std::vector<Term*>& getTerms      () const;
      Term*                     getTerm       (const std::string&) const;
      Point                     getPosition   () const;

      // Modificators
      bool  connect       ( const std::string& name, Net* );
      void  setPosition   ( const Point& );
      void  setPosition   ( int x, int y );
      void  add( Term* );
      void  remove( Term* );

      void toXml ( std::ostream& ostream );

    private:
      /* ---------------- Attributes ------------- */
      Cell*               owner_;
      Cell*               masterCell_;
      std::string         name_;
      std::vector<Term*>  terms_;
      Point               position_;
  };
}

#endif

