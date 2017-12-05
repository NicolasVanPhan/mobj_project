
#include "Shapes.h"

namespace Netlist {

  EllipseShape::EllipseShape      ( Symbol* owner, const Box& box )
    :Shape(owner), box_(box)
  { }

  EllipseShape::EllipseShape      ( Symbol* owner, int x1, int x2, int y1, int y2 )
    :Shape(owner), box_(x1, x2, y1, y2)
  { }

  EllipseShape::~EllipseShape      ( ) 
  { }

  Box     EllipseShape::getBoundingBox () const
  { return box_; }

  void    EllipseShape::toXml ( std::ostream& stream ) const
  {
    stream <<"<ellipse x1=\""<< box_.getX1() <<"\" "<<"y1=\""<< box_.getY1() <<"\""
    <<"x2=\""<< box_.getX2() <<"\" "<<"y2=\""<< box_.getY2() <<"\" "<<std::endl;   
  }

  EllipseShape*   EllipseShape::fromXml (Symbol* owner, xmlTextReaderPtr reader)
  {
    EllipseShape* eshape;
    const xmlChar* ellipseShapeTag;
    const xmlChar* nodeName;
    int            nodeType;
    int   x1;
    int   x2;
    int   y1;
    int   y2;

    // Reading the current xml line
    ellipseShapeTag = xmlTextReaderConstString(reader, (const xmlChar*)"ellipse");
    nodeName = xmlTextReaderConstLocalName(reader);
    nodeType = xmlTextReaderNodeType(reader);
   
    // Checking the content
    eshape = NULL;
    if (nodeType == XML_READER_TYPE_ELEMENT and nodeName == ellipseShapeTag)
    {
      x1 = atoi(xmlCharToString(xmlTextReaderGetAttribute( reader, (const xmlChar*)
      "x1")).c_str());
      x2 = atoi(xmlCharToString(xmlTextReaderGetAttribute( reader, (const xmlChar*)
      "x2")).c_str());
      y1 = atoi(xmlCharToString(xmlTextReaderGetAttribute( reader, (const xmlChar*)
      "y1")).c_str());
      y2 = atoi(xmlCharToString(xmlTextReaderGetAttribute( reader, (const xmlChar*)
      "y2")).c_str());
      
      eshape = new EllipseShape(owner, x1, x2, y1, y2);
    }
    return eshape;
  }

}

