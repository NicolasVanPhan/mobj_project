
#include "Term.h"
#include "Net.h"
#include "Instance.h"

namespace Netlist {

    std::string Term::toString ( Term::Type type )
    {
        if (type == Internal)
            return "Internal";
        else if (type == External)
            return "External";
        else
            return "";
    }

    std::string Term::toString ( Term::Direction dir)
    {
        if (dir == In )
            return "In";
        else if (dir == Out)
            return "Out";
        else if (dir == Inout)
            return "Inout";
        else if (dir == Tristate)
            return "Tristate";
        else if (dir == Transcv)
            return "Transcv";
        else if (dir == Unknown)
            return "Unknown";
        else
            return "";
    }

    Term::Direction Term::toDirection( std::string str )
    {
        if (str == "In")
            return In;
        else if (str == "Out")
            return Out;
        else if (str == "Inout")
            return Inout;
        else if (str == "Tristate")
            return Tristate;
        else if (str == "Transcv")
            return Transcv;
        else
            return Unknown;
    }

    Term::Term    ( Cell* cell, const std::string& name, Direction dir)
        : owner_(cell)
        , name_(name)
        , direction_(dir)
        , type_(External)
        , net_(NULL)
        , node_(this)
    {
       // When a cell's terminals set is updated,
       // shall the cell's instances' terminals sets be updated too? 
        cell->add(this);
    } 

    Term::Term ( Instance* inst, const Term* modelTerm)
        : owner_(inst)
        , name_(modelTerm->getName())
        , direction_(modelTerm->getDirection())
        , type_(Internal)
        , net_(NULL)
        , node_(this)
    {
        inst->add(this);
    }

    Term::~Term ()
    {
        if (type_ == External)
            ((Cell*)owner_)->remove(this);
        else // type == Internal
            ((Instance*)owner_)->remove(this);
        // Possible segfault if net_ is destroyed
        // before node_
    }

    // Accessors
    Cell*              Term::getOwnerCell () const
    {
        if (type_ == External)
            return(Cell*)owner_;
        else 
            return ((Instance*)owner_)->getCell();  
    }

    // Modificators
    void        Term::setNet       ( Net* net )
    {
        // If the Term is already plugged, unplug it
        if (net_ != NULL)
          net_->remove(&node_);
        // Plug the new signal into the Term
        net->add(&node_);
    }
    void        Term::setNet       ( const std::string& name)
    {
        Net* net;

        if (type_ == External)
            net = ((Cell*)owner_)->getNet(name);
        else // type == Internal
            net = ((Instance*)owner_)->getCell()->getNet(name);
        if (net != NULL)
        {
            // If the Term is already plugged, unplug it
            if (net_ != NULL)
                net_->remove(&node_);
            // Plug the new signal into the Term
            net->add(&node_);
        }
        else
            std::cerr << "[Error] Net " << name << " doesn't exist" << std::endl;
    }
    void        Term::setPosition  ( const Point& point)
    {
        node_.setPosition(point);
    }
    void        Term::setPosition  ( int x, int y )
    {
        node_.setPosition(x,y);
    }

    void	Term::toXml ( std::ostream& ostream)
    {
        ostream << indent << "<term name=\"" << name_
                << "\" direction=\"" << toString(direction_)
                << "\"/>" << std::endl;
    }
}
