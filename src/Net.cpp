
#include "Net.h"

namespace Netlist {

  // CTOR and DTOR
  Net::Net     ( Cell* cell, const std::string& name, Term::Type type)
    : owner_(cell)
      , name_(name)
      , id_(cell->newNetId())
      , type_(type)
      , nodes_()
  {
    cell->add(this);
  }

  Net::~Net    ( )
  {
    std::vector<Node*>::iterator inode;
    // Unplug Terms connected to this Net
    for (inode = nodes_.begin(); inode != nodes_.end(); inode++)
      (*inode)->getTerm()->setNet(NULL);
    // Empty the nodes_ table
    while (!nodes_.empty())
      nodes_.pop_back();
    // Tell the owner it doesn't own this Net anymore
    owner_->remove(this);
  }

  // Accessors
  Cell*                               Net::getCell       () const
  {
    return owner_;
  }

  const std::string&                  Net::getName       () const
  {
    return name_;
  }

  unsigned int                        Net::getId         () const
  {
    return id_;
  }

  Term::Type                          Net::getType       () const
  {
    return type_;
  }

  const std::vector<Node*>&           Net::getNodes      () const
  {
    return nodes_;
  }

  size_t                              Net::getFreeNodeId () const
  {
    size_t  i;

    i = 0;
    while (i < nodes_.size() && nodes_[i] != NULL)
      i++;
    return i;
  }

  // Modificators
  void                                Net::add    ( Node* node )
  {
    size_t  free_id;

    // As in Spice, one can plug a net into a terminal only if
    // it's plugged to nothing
    free_id = getFreeNodeId();
    if (node->getTerm()->getNet() == NULL)
    {
      if (free_id == nodes_.size())
        nodes_.push_back(node);
      else
        nodes_[free_id] = node;
    }
    else
    {
      std::cerr << "[Error] The net "
        << node->getTerm()->getNet()->getName()
        << " is already connected to this node" << std::endl;
    }
  }

  bool                                Net::remove ( Node* node)
  {
    size_t i;

    for (i = 0;i < nodes_.size();i++)
    {
      if (nodes_[i] == node)
      {
        nodes_[i] = NULL;
        node->getTerm()->setNet(NULL);
        return true;
      }
    }
    return false;
  }

  void Net::toXml ( std::ostream& ostream )
  {
    ostream << indent++ << "<net name=\"" << name_
      << "\" type=\"" << Term::toString(type_)
      << "\">" << std::endl;
    for (std::vector<Node*>::iterator p = nodes_.begin(); p != nodes_.end(); p++)
      (*p)->toXml(ostream);
    ostream << --indent << "</net>" << std::endl;
  }

  Net*             Net::fromXml (Cell* cell, xmlTextReaderPtr reader)
  {
    enum State { endNet };
    const xmlChar*    netTag;
    const xmlChar*    nodeName;
    int               nodeType;
    std::string       netName;
    Term::Type        netType;
    Net*              net;
    State		state;

    netTag = xmlTextReaderConstString( reader, (const xmlChar*)"net" );
    nodeName = xmlTextReaderConstLocalName(reader);
    nodeType = xmlTextReaderNodeType(reader);

    // if (line == "<net>")
    if (nodeName == netTag && nodeType == XML_READER_TYPE_ELEMENT)
    {
      state = endNet;

      // Creation of the new Net
      netName = xmlCharToString(xmlTextReaderGetAttribute(reader,
            (const xmlChar*)"name"));
      netType = Term::toType(xmlCharToString(
            xmlTextReaderGetAttribute(reader,
              (const xmlChar*)"type")));
      net = new Net(cell, netName, netType);

      std::cerr << "test" << std::endl;

      // Read all Node
      while (true) {
        int status = xmlTextReaderRead(reader);
        // If reached EOF or current line is incorrect, exit failure
        if (status != 1) {
          std::cerr << "[ERROR] Net::fromXml(): "
            << "Unexpected termination of the XML parser."
            << std::endl;
          break;
        }

        switch ( xmlTextReaderNodeType(reader) ) {
          case XML_READER_TYPE_COMMENT:
          case XML_READER_TYPE_WHITESPACE:
          case XML_READER_TYPE_SIGNIFICANT_WHITESPACE:
            continue;
        }

        nodeName = xmlTextReaderConstLocalName(reader);
        nodeType = xmlTextReaderNodeType(reader);

        std::cerr << "nodeName: " << xmlCharToString(nodeName) << std::endl;
        std::cerr << "nodeType: " << nodeType << std::endl;

        switch (state) {
          case endNet:
            // if line == </net>, finish reading correctly (return true)
            if ((nodeName == netTag) and
                (xmlTextReaderNodeType(reader)
                 == XML_READER_TYPE_END_ELEMENT)) { // if (line == </net>) 
              return net; // finished reading the file, successfully
            }
            // if line == <node />, add Node to the Net
            // if line is incorrect, break
            else {
              if (Node::fromXml(net, reader)) continue;
              else
                std::cerr << "Ouille" << std::endl;
            }
            break;
          default:
            break;
        } // end of switch
        // if any error occured, return incorrectly (return false)
        std::cerr << "[ERROR] Net::fromXml(): Unknown or misplaced tag <"
          << nodeName << "<"
          << "(line: " << xmlTextReaderGetParserLineNumber(reader)
          << ")." << std::endl;
        break;
      }
    } // end of while
    return NULL; // reading ended in failure
  }

  void  Net::add ( Line* line )
  { if (line) lines_.push_back( line ); }

  bool  Net::remove ( Line* line )
  {
    if (line) {
      for ( vector<Line*>::iterator il = lines_.begin(); il != lines_.end() ; ++il ) {
        if (*il == line) {
          lines_.erase( il );
          return true;
        }
      }
    }
    return false;
  }
}
