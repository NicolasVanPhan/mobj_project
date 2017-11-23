
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

  bool             Net::fromXml (Cell* cell, xmlTextReaderPtr reader)
  {
    return 1;
  }
}
