
#ifndef NETLIST_INSTANCE_H
#define NETLIST_INSTANCE_H

#include <string>
#include "Cell.h"
#include "Term.h"
#include "Point.h"
#include "Net.h"

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
/* [X] */   Instance    ( Cell* owner, Cell* model, const std::string& );
/* [X] */   ~Instance   ();

            // Accessors
/* [X] */   const std::string&        getName       () const;
/* [X] */   Cell*                     getMasterCell () const;
/* [X] */   Cell*                     getCell       () const;
/* [X] */   const std::vector<Term*>& getTerms      () const;
/* [X] */   Term*                     getTerm       (const std::string&) const;
/* [X] */   Point                     getPosition   () const;
            
            // Modificators
/* [X] */   bool  connect       ( const std::string& name, Net* );
/* [X] */   void  setPosition   ( const Point& );
/* [X] */   void  setPosition   ( int x, int y );
/* [X] */   void  add( Term* );
/* [X] */   void  remove( Term* );

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

