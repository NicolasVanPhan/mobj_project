
#include "Net.h"

namespace Netlist {
    // CTOR and DTOR
    Net::Net     ( Cell* cell, const std::string& name, Term::Type type)
        : owner_(cell)
          , name_(name)
          , id_(cell->newNetId())
          , type_(type)
          , nodes_(NULL) 
    {
        cell->add(this);
    }
    Net::~Net    ( )
    {
        std::vector<Node*>::iterator inode;
        for (inode = nodes_.begin(); inode != nodes_.end(); inode++)
            (*inode)->getTerm()->setNet(NULL);
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
        // As in Spice, if there's already something plugged into
        // this terminal, we don't replace it
        if (node->getTerm() != NULL)
            nodes_[getFreeNodeId()] = node;
        else
            std::cerr << "[Error] The net "
                 << node->getTerm()->getNet()->getName() 
                 << " is already connected to this node" << std::endl;
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
    }
}
