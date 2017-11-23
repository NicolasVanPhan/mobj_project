
# ifndef NETLIST_NET_H
# define NETLIST_NET_H

#include <string>
#include <vector>
#include <fstream>
#include <libxml/xmlreader.h>
#include "Term.h"
#include "Cell.h"
#include "Node.h"
#include "Instance.h"
#include "Indentation.h"

namespace Netlist {

  class Term;
  class Cell;
  class Node;
  class Instance;

  class Net {
    public :
      /* --------- Class Functions --------- */
      static bool             fromXml (Cell* cell, xmlTextReaderPtr reader);

      /* --------- Instance Functions --------- */
      // CTOR and DTOR
      Net     ( Cell* cell, const std::string& name, Term::Type );
      ~Net    ( );

      // Accessors
      Cell*                     getCell       () const;
      const std::string&        getName       () const;
      unsigned int              getId         () const;
      Term::Type                getType       () const;
      const std::vector<Node*>& getNodes      () const;
      size_t                    getFreeNodeId () const;

      // Modificators
      void add    ( Node* );
      bool remove ( Node* );

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

