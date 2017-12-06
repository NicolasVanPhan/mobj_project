
#include "Term.h"
#include "Shapes.h"

namespace Netlist {

  TermShape::TermShape      ( Symbol* owner, std::string name, int x, int y,
      NameAlign align )
    :Shape(owner), x_(x), y_(y), term_(NULL), align_(align)
  {
    term_ = owner->getCell()->getTerm(name);
  }

  TermShape::~TermShape     ()
  {
  }


  std::string  TermShape::alignToString             ( NameAlign align )
  {
    if ( align == TopLeft )
      return "top_left";
    if ( align == TopRight )
      return "top_right";
    if ( align == BottomLeft )
      return "bottom_left";
    else
      return "bottom_right";
  }

  TermShape::NameAlign   TermShape::stringToAlign   ( std::string align )
  {
    if ( align == "top_left")
      return TopLeft ;
    if ( align == "top_right" )
      return TopRight;
    if ( align == "bottom_left")
      return BottomLeft ;
    if ( align == "bottom_right")
      return BottomRight ;
    else
      return BottomRight;
  }

  Box                 TermShape::getBoundingBox() const
  { return Box(x_, y_, x_, y_); }

  void                TermShape::toXml          ( std::ostream& stream) const
  {
    stream << indent
      << "<term name=\"" << term_->getName() << "\" "
      << "x1=\"" << x_ << "\" "
      << "y1=\"" << y_ << "\" "
      << "align=\"" << alignToString(align_) << "\" />" << std::endl;
  }
  
  TermShape*   TermShape::fromXml(Symbol* owner, xmlTextReaderPtr reader)
  {
    TermShape* tshape;
    const xmlChar*  termShapeTag;
    const xmlChar*  nodeName;
    int             nodeType;
    int             x1;
    int             y1;
    std::string     termName;
    NameAlign       align;

    // Reading the current xml line
    termShapeTag = xmlTextReaderConstString(reader, (const xmlChar*)"term");
    nodeName = xmlTextReaderConstLocalName(reader);
    nodeType = xmlTextReaderNodeType(reader);
   
    // Checking the content
    tshape = NULL;
    if (nodeType == XML_READER_TYPE_ELEMENT and nodeName == termShapeTag)
    {
      x1 = atoi(xmlCharToString(xmlTextReaderGetAttribute( reader, (const xmlChar*)
      "x1")).c_str());
      y1 = atoi(xmlCharToString(xmlTextReaderGetAttribute( reader, (const xmlChar*)
      "y1")).c_str());
      termName = xmlCharToString(xmlTextReaderGetAttribute( reader,
            (const xmlChar*)"name"));
      align = stringToAlign(xmlCharToString(xmlTextReaderGetAttribute( reader,
              (const xmlChar*)"align" )));
      
      tshape = new TermShape(owner, termName, x1, y1, align);
    }
    return tshape;
  }
}

