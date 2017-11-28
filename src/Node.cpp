// -*- explicit-buffer-name: "Node.cpp<M1-MOBJ/4-5>" -*-

#include  <limits>
#include  "Node.h"
#include  "Term.h"
#include  "Net.h"
#include  "Instance.h"
#include  "Cell.h"

namespace Netlist {

  using namespace std;


  const size_t  Node::noid = numeric_limits<size_t>::max();


  Node::Node ( Term* term, size_t id  )
    : id_      (id)
    , term_    (term)
    , position_()
  { }


  Node::~Node ()
  {
    if (getNet()) getNet()->remove( this );
  }


  inline Net* Node::getNet () const { return term_->getNet(); }


// Node::toXml() à écrire ici.
  void    Node::toXml       ( std::ostream& ostream )
  {
      ostream << indent << "<node term=\"" << term_->getName();
      if (term_->getType() == Term::Internal)
          ostream << "\" instance=\"" << term_->getInstance()->getName();
      ostream << "\" id=\"" << id_
              << "\"/>" << std::endl;
  }

  bool         Node::fromXml(Net* net, xmlTextReaderPtr reader)
  {
      Term*     	term;
      const xmlChar*	nodeTag;
      const xmlChar*	nodeName;
      int		nodeType;

      std::string termName;
      std::string instanceName;
      int	  id;

      nodeTag = xmlTextReaderConstString( reader, (const xmlChar*)"node" );
      nodeName = xmlTextReaderConstLocalName(reader);
      nodeType = xmlTextReaderNodeType(reader);

      if(nodeName == nodeTag && nodeType == XML_READER_TYPE_ELEMENT)
      {
         instanceName = xmlCharToString(xmlTextReaderGetAttribute(reader,
			(const xmlChar*)"instance"));
         termName = xmlCharToString(xmlTextReaderGetAttribute(reader,
			(const xmlChar*)"term"));
         id = atoi(xmlCharToString(xmlTextReaderGetAttribute(reader,
			(const xmlChar*)"id")).c_str());
         if (instanceName.empty()) //connection to a terminal cell
         {
             term = net->getCell()->getTerm(termName);
             term->setNet(net);
         }
         else //connection to a terminal instance
         {
             term = net->getCell()->getInstance(instanceName)->getTerm(termName);
             term->setNet(net);
         }
	 term->getNode()->setId(id);
         return true;
      }
      return false;
  }

}  // Netlist namespace.
