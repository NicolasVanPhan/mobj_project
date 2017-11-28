
#ifndef     NETLIST_TERM_H
#define     NETLIST_TERM_H

#include <string>
#include <fstream>
#include <libxml/xmlreader.h>
#include <cstdlib>
#include "Node.h"
#include "Point.h"
#include "Indentation.h"
#include "XmlUtil.h"

namespace Netlist {

  // Forward declaration
  class Cell;
  class Instance;
  class Node;
  class Point;
  class Net;

  class Term {
    public :
      /* -------------- Enumerates -------------- */
      enum Type   { Internal=1, External=2 };
      enum Direction  { In=1, Out=2, Inout=3, Tristate=4, Transcv=5, Unknown=6 };

      /* ------------- Class functions ---------- */
      static std::string     toString ( Type );
      static std::string     toString ( Direction );
      static Direction       toDirection ( std::string );
      static type	     toType(std::string);
      static Term*           fromXml (Cell* cell, xmlTextReaderPtr reader);

      /* ------------- Functions ---------------- */
      // CTOR and DTOR
      Term    (Cell* cell, const std::string& name, Direction dir);
      Term    (Instance* inst, const Term* modelTerm);
      ~Term   ();

      // Accessors
      inline bool               isInternal   () const;
      inline bool               isExternal   () const;
      inline const std::string& getName      () const;
      inline Node*              getNode      ();
      inline Net*               getNet       () const;
      inline Cell*              getCell      () const;
             Cell*              getOwnerCell () const;
      inline Instance*          getInstance  () const;
      inline Direction          getDirection () const;
      inline Point              getPosition  () const;
      inline Type               getType      () const;

      // Modificators
      void        setNet       ( Net* );
      void        setNet       ( const std::string& );
      inline void setDirection ( Direction );
      void        setPosition  ( const Point& );
      void        setPosition  ( int x, int y );

      void	toXml	     ( std::ostream& ostream );

    private :
      /* ------------ Attributes ---------------- */
      void*       owner_;
      std::string name_;
      Direction   direction_;
      Type        type_;
      Net*        net_;
      Node        node_;
  };

  inline bool               Term::isInternal   () const
  { return (type_ == Internal); }

  inline bool               Term::isExternal   () const
  { return (type_ == External); }

  inline const std::string& Term::getName      () const
  { return name_; }

  inline Node*              Term::getNode      ()     
  { return &node_; }

  inline Net*               Term::getNet       () const
  { return net_; }

  inline Cell*              Term::getCell      () const
  {
    if (isExternal())
      return (Cell*)owner_;
    std::cerr << "[Warning] Your object Term is Internal" << std::endl;
    return NULL;
  }
  inline Instance*          Term::getInstance  () const
  {
    if (isInternal())
      return (Instance*)owner_;
    std::cerr << "[Warning] Your object Term is External" << std::endl;
    return NULL;
  }
  inline Term::Direction    Term::getDirection () const
  { return direction_; }

  inline Point              Term::getPosition  () const
  { return node_.getPosition(); }

  inline Term::Type         Term::getType      () const
  { return type_; }

  // In which cas could that function be used? Directions don't usually change
  inline void               Term::setDirection      (Direction dir)
  { direction_ = dir; }
}

#endif

