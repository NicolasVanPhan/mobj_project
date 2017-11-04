
# ifndef NETLIST_NET_H
# define NETLIST_NET_H

#include <string>
#include <vector>
#include "Term.h"
#include "Cell.h"
#include "Node.h"
#include "Instance.h"
#include "Indentation.h"

namespace Netlist {

    // Fowwwd declaration
    class Term;
    class Cell;
    class Node;
    class Instance;

    class Net {
        public :
            /* --------- FUNCTIONS --------- */
            // CTOR and DTOR
/* [X] */   Net     ( Cell* cell, const std::string& name, Term::Type );
/* [X] */   ~Net    ( );

            // Accessors
/* [X] */   Cell*                     getCell       () const;
/* [X] */   const std::string&        getName       () const;
/* [X] */   unsigned int              getId         () const;
/* [X] */   Term::Type                getType       () const;
/* [X] */   const std::vector<Node*>& getNodes      () const;
/* [X] */   size_t                    getFreeNodeId () const;

            // Modificators
/* [X] */   void add    ( Node* );
/* [X] */   bool remove ( Node* );

	    void toXml ( std::ostream& ostream );

        private :
            /* -------- Attributes ------- */
            Cell*               owner_;
            std::string         name_;
            unsigned int        id_;
            Term::Type          type_;
            std::vector<Node*>  nodes_;
    };
}

#endif

