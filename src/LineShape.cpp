
#include "LineShape.h"

namespace Netlist {

  LineShape::LineShape        ( Symbol* owner, int x1, int y1, int x2, int y2)
    :Shape(owner),
    x1_(x1),
    y1_(y1),
    x2_(x2),
    y2_(y2),
  {
  }

  LineShape::~LineShape        ( )
  { }

  Box     LineShape::getBoundingBox () const
  {
    return Box(std::min(x1, x2), std::min(y1, y2), std::max(x1, x2), std::max(y1, y2));
  }

  void    toXml               ( std::ostream& stream) const
  {
     stream <<"<line x1=\""<<x1_<<"\" "<<"y1=\""<<y1_<<"\""
    <<"x2=\""<<x2_<<"\" "<<"y2=\""<<y2_<<"\" "<<std::endl;   

  }

  LineShape*   LineShape::fromXml (Symbol* owner, xmlTextReaderPtr reader)
  {
    LineShape* lshape;
    const xmlChar* lineShapeTag;
    const xmlChar* nodeName;
    const xmlChar* nodeType;
    int   x1;
    int   x2;
    int   y1;
    int   y2;

    // Reading the current xml line
    lineShapeTag = xmlTextReaderConstString(reader, (const xmlChar*)"line");
    nodeName = xmlTextReaderConstLocalName(reader);
    nodeType = xmlTextReaderNodeType(reader);
   
    // Checking the content
    lshape = NULL;
    if (nodeType == XML_READER_TYPE_ELEMENT and nodeName == lineShapeTag)
    {
      x1 = atoi(xmlCharToString(xmlTextReaderGetAttibute( reader, (const xmlChar*)
      "x1")).c_str());
      x2 = atoi(xmlCharToString(xmlTextReaderGetAttibute( reader, (const xmlChar*)
      "x2")).c_str());
      y1 = atoi(xmlCharToString(xmlTextReaderGetAttibute( reader, (const xmlChar*
      "y1")).c_str());
      y2 = atoi(xmlCharToString(xmlTextReaderGetAttibute( reader, (const xmlChar*
      "y2")).c_str());
      
      lshape = new LineShape(owner, x1, x2, y1, y2);
    }
    return lshape;
  }

}

