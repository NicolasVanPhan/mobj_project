
#include "EllipseShape.h"

namespace Netlist {

  EllipseShape::EllipseShape      ( Symbol* owner, const Box& box )
    :Shape(owner), box_(box)
  { }

  EllipseShape::EllipseShape      ( Symbol* owner, int x1, int x2, int y1, int y2 )
    :Shape(owner), box_(x1, x2, y1, y2)
  { }

  EllipseShape::~EllipseShape      ( ) 
  { }

  Box     Ellipseshape::getBoundingBox () const
  { return box_; }

  void    toXml ( std::ostream& stream )
  {
    Box boxCopy = getBoundingBox ();
    
    stream <<"<ellipse x1=\""<<boxCopy.x1_<<"\" "<<"y1=\""<<boxCopy.y1_<<"\""
    <<"x2=\""<<boxCopy.x2_<<"\" "<<"y2=\""<<boxCopy.y2_<<"\" "<<std::endl;   
  }

  EllipseShape*   EllipseShape::fromXml (Symbol* owner, xmlTextReaderPtr reader)
  {
    EllipseShape* eshape;
    const xmlChar* ellipseShapeTag;
    const xmlChar* nodeName;
    const xmlChar* nodeType;
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
      x1 = atoi(xmlCharToString(xmlTextReaderGetAttibute( reader, (const xmlChar*)
      "x1")).c_str());
      x2 = atoi(xmlCharToString(xmlTextReaderGetAttibute( reader, (const xmlChar*)
      "x2")).c_str());
      y1 = atoi(xmlCharToString(xmlTextReaderGetAttibute( reader, (const xmlChar*
      "y1")).c_str());
      y2 = atoi(xmlCharToString(xmlTextReaderGetAttibute( reader, (const xmlChar*
      "y2")).c_str());
      
      eshape = new EllipseShape(owner, x1, x2, y1, y2);
    }
    return eshape;
  }

}

