
#include "Instance.h"

namespace Netlist {

  Instance::Instance    ( Cell* owner, Cell* model, const std::string& name )
    :owner_(owner)
     ,masterCell_(model)
     ,name_(name)
     ,position_()     
  {
    Term*     term;

    // Duplicate terminals
    std::vector<Term*> src = model->getTerms();   // source vector
    std::vector<Term*>::iterator p; 
    for (p = src.begin(); p != src.end(); p++)
    {
      term = new Term(this, *p);
      terms_.push_back(term);
    }

    // Tell the owner cell it has one more instance
    owner->add(this);
  }

  Instance::~Instance   ()
  {
    /* There's no need to take into account the fact that terminals
     * might be plugged because this destructor calls the Term's destructors
     * that take care of it */

    // Tell the owner cell it has one less instance
    owner_->remove(this);

  }

  // Accessors
  const std::string&        Instance::getName       () const
  {return name_;}

  Cell*                     Instance::getMasterCell () const
  {return masterCell_;}

  Cell*                     Instance::getCell       () const
  {return owner_;}

  const std::vector<Term*>& Instance::getTerms      () const
  {return terms_;}

  Term*   Instance::getTerm(const std::string& nameTerm) const
  {
    std::vector<Term*>::const_iterator p;
    for (p = terms_.begin(); p != terms_.end(); p++)
    {
      if ((*p)->getName() == nameTerm)
	return *p;
    }
    return NULL;
  }

  Point                     Instance::getPosition   () const
  {return position_;}

  // Modificators
  bool  Instance::connect       ( const std::string& name, Net* net)
  {
    // Check if the Term exists
    if (getTerm(name) == NULL)
      return false;

    // Tell the Term that it's connected to a new Net
    getTerm(name)->setNet(net);

    // Tell the Net that it's connected to a new Term
    net->add(getTerm(name)->getNode());

    return true;
  }

  void  Instance::setPosition   ( const Point& point )
  {
    position_ = point;
  }

  void  Instance::setPosition   ( int x, int y )
  {
    position_.setX(x);
    position_.setY(y);
  }

  // In what situation could those be used ?
  void  Instance::add( Term* term )
  {
    if (getTerm(term->getName()) == NULL)
      terms_.push_back(term);
  }

  void  Instance::remove( Term* term )
  {
    std::vector<Term*>::iterator p;
    p = terms_.begin();
    while (p != terms_.end() && ((*p)->getName() != term->getName()))
      p++;
    if (p != terms_.end())
      *p = NULL;
  }

  void  Instance::toXml( std::ostream& ostream)
  {
      ostream << indent << "<instance name=\"" << name_
              << "\" mastercell=\"" << masterCell_->getName()
              << "\" x=\"" << position_.getX()
              << "\" y=\"" << position_.getY()
              << "\"/>" << std::endl;
  }
}
