
#include "Shapes.h"

namespace Netlist {

  BoxShape::BoxShape      ( Symbol* owner, const Box& box )
    :Shape(owner), box_(box)
  { }

  BoxShape::BoxShape      ( Symbol* owner, int x1, int y1, int x2, int y2 )
    :Shape(owner), box_(x1, y1, x2, y2)
  { }

  BoxShape::~BoxShape      ( ) 
  { }

  Box     BoxShape::getBoundingBox () const
  { return box_; }
 
  void    BoxShape::toXml           ( std::ostream& stream ) const
  {
    stream << indent
      << "<box x1=\"" << box_.getX1() <<"\" "
      << "y1=\"" << box_.getY1() << "\" "
      << "x2=\"" << box_.getX2() << "\" "
      << "y2=\"" << box_.getY2()
      << "\" />" << std::endl;   
  }

  BoxShape*   BoxShape::fromXml (Symbol* owner, xmlTextReaderPtr reader)
  {
    BoxShape* bshape;
    const xmlChar* boxShapeTag;
    const xmlChar* nodeName;
    int   nodeType;
    int   x1;
    int   y1;
    int   x2;
    int   y2;

    // Reading the current xml line
    boxShapeTag = xmlTextReaderConstString(reader, (const xmlChar*)"box");
    nodeName = xmlTextReaderConstLocalName(reader);
    nodeType = xmlTextReaderNodeType(reader);
   
    // Checking the content
    bshape = NULL;
    if (nodeType == XML_READER_TYPE_ELEMENT and nodeName == boxShapeTag)
    {
      x1 = atoi(xmlCharToString(xmlTextReaderGetAttribute( reader,
              (const xmlChar*)"x1")).c_str());
      y1 = atoi(xmlCharToString(xmlTextReaderGetAttribute( reader,
              (const xmlChar*)"y1")).c_str());
      x2 = atoi(xmlCharToString(xmlTextReaderGetAttribute( reader,
              (const xmlChar*)"x2")).c_str());
      y2 = atoi(xmlCharToString(xmlTextReaderGetAttribute( reader,
              (const xmlChar*)"y2")).c_str());
      
      bshape = new BoxShape(owner, x1, y1, x2, y2);
    }
    return bshape;
  }
}

