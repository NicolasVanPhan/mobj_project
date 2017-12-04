
#include "TermShape.h"
#include "Box.h"
#include "Term.h"

namespace Netlist {

  TermShape::TermShape      ( Symbol* owner, int x, int y, std::string name,
      NameAlign align )
    :Shape(owner), x_(x), y_(y), term_(NULL), align_(TopLeft)
  {
    term_ = getCell()->getTerm(name);
  }

  TermShape::~TermShape     ()
  {
  }


  static std::string  alignToString             ( NameAlign )
  {
    if ( NameAlign == TopLeft )
      return "top_left";
    if ( NameAlign == TopRight )
      return "top_right";
    if ( NameAlign == BottomLeft )
      return "bottom_left";
    else
      return "bottom_right";
  }

  Box                 TermShape::getBoundingBox() const
  { return Box(x_, y_, x_, y_); }

  void                TermShape::toXml          ( std::ostream& stream) const
  {
    stream << "<term name=\"" << term_->getName() << "\" "
     << "x1=\"" << x_ << "\" " << "y1=\"" << y_ << "\" "
     << "align=\"" << alignToString(align_) << "\"/>" << std::endl;
  }
  
  static TermShape*   TermShape::fromXml(Symbol* owner, xmlTextReaderPtr reader)
  {
    TermShape* tshape;
    const xmlChar* termShapeTag;
    const xmlChar* nodeName;
    const xmlChar* nodeType;
    int   x1;
    int   y1;
    std::string termName;
    NameAlign   align;

    // Reading the current xml line
    termShapeTag = xmlTextReaderConstString(reader, (const xmlChar*)"term");
    nodeName = xmlTextReaderConstLocalName(reader);
    nodeType = xmlTextReaderNodeType(reader);
   
    // Checking the content
    tshape = NULL;
    if (nodeType == XML_READER_TYPE_ELEMENT and nodeName == termShapeTag)
    {
      x1 = atoi(xmlCharToString(xmlTextReaderGetAttibute( reader, (const xmlChar*)
      "x1")).c_str());
      x2 = atoi(xmlCharToString(xmlTextReaderGetAttibute( reader, (const xmlChar*)
      "x2")).c_str());
      termName = xmlCharToString(xmlTextReaderGetAttibute( reader,
            (const xmlChar*)"name"));
      align = stringToAlign(xmlCharToString(xmlTextReaderGetAttibute( reader,
              (const xmlChar*)"align" )));
      
      tshape = new TermShape(owner, termName, x1, x2, align);
    }
    return tshape;
  }
}

