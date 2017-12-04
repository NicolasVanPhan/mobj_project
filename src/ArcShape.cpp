
#include "ArcShape.h"

namespace Netlist {

  ArcShape::ArcShape      ( Symbol* owner, const Box& box )
    :Shape(owner), box_(box), start_(start), span_(span)
  { }

  ArcShape::ArcShape      ( Symbol* owner, int x1, int x2, int y1, int y2 )
    :Shape(owner), box_(x1, x2, y1, y2), start_(start), span_(span)
  { }

  ArcShape::~ArcShape      ( ) 
  { }

  Box     Arcshape::getBoundingBox () const
  { return box_; }

  void    toXml ( std::ostream& stream )
  {
    Box boxCopy = getBoundingBox ();
    
    stream <<"<arc x1=\""<<boxCopy.x1_<<"\" "<<"y1=\""<<boxCopy.y1_<<"\""
    <<"x2=\""<<boxCopy.x2_<<"\" "<<"y2=\""<<boxCopy.y2_<<"\" "
    <<"start=\""<<start_<<"\" "<<"span=\""<<span_<<"\"/>"<<std::endl;   
  }

  ArcShape*   ArcShape::fromXml (Symbol* owner, xmlTextReaderPtr reader)
  {
    ArcShape* ashape;
    const xmlChar* arcShapeTag;
    const xmlChar* nodeName;
    const xmlChar* nodeType;
    int   x1;
    int   x2;
    int   y1;
    int   y2;
    int   start;
    int   span;

    // Reading the current xml line
    arcShapeTag = xmlTextReaderConstString(reader, (const xmlChar*)"arc");
    nodeName = xmlTextReaderConstLocalName(reader);
    nodeType = xmlTextReaderNodeType(reader);
   
    // Checking the content
    ashape = NULL;
    if (nodeType == XML_READER_TYPE_ELEMENT and nodeName == arcShapeTag)
    {
      x1 = atoi(xmlCharToString(xmlTextReaderGetAttibute( reader, (const xmlChar*)
      "x1")).c_str());
      x2 = atoi(xmlCharToString(xmlTextReaderGetAttibute( reader, (const xmlChar*)
      "x2")).c_str());
      y1 = atoi(xmlCharToString(xmlTextReaderGetAttibute( reader, (const xmlChar*)
      "y1")).c_str());
      y2 = atoi(xmlCharToString(xmlTextReaderGetAttibute( reader, (const xmlChar*)
      "y2")).c_str());
      start = atoi(xmlCharToString(xmlTextReaderGetAttibute( reader,
      (const xmlChar*)"start")).c_str());
      span = atoi(xmlCharToString(xmlTextReaderGetAttibute( reader,
      (const xmlChar*)"span")).c_str());

      ashape = new ArcShape(owner, x1, x2, y1, y2, start, span);
    }
    return ashape;
  }

}

