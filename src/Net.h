
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
      static Net*             fromXml (Cell* cell, xmlTextReaderPtr reader);

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
      Node*                     getNode       ( size_t id ) const;
      size_t                    getFreeNodeId () const;
      inline const std::vector<Line*>& getLines() const;

      // Modificators
      void add    ( Node* );
      void add    ( Line* );
      bool remove ( Node* );
      bool remove ( Line* );

      void toXml ( std::ostream& ostream );

    private :
      /* -------- Attributes ------- */
      Cell*               owner_;
      std::string         name_;
      unsigned int        id_;
      Term::Type          type_;
      std::vector<Node*>  nodes_;
      std::vector<Line*>  lines_;
  };

  inline const std::vector<Line*>& Net::getLines() const
  { return lines_; }
}

#endif

