
#include "BoxShape.h"

namespace Netlist {

  BoxShape::BoxShape      ( Symbol* owner, const Box& box )
    :Shape(owner), box_(box)
  { }

  BoxShape::BoxShape      ( Symbol* owner, int x1, int x2, int y1, int y2 )
    :Shape(owner), box_(x1, x2, y1, y2)
  { }

  BoxShape::~BoxShape      ( ) 
  { }

  Box     Boxshape::getBoundingBox () const
  { return box_; }
 
  void    toXml           ( std::ostream& stream )
  {
    Box boxCopy = getBoundingBox ();
    
    stream <<"<box x1=\""<<boxCopy.x1_<<"\" "<<"y1=\""<<boxCopy.y1_<<"\""
    <<"x2=\""<<boxCopy.x2_<<"\" "<<"y2=\""<<boxCopy.y2_<<"\" "<<std::endl;   
  }

  BoxShape*   BoxShape::fromXml (Symbol* owner, xmlTextReaderPtr reader)
  {
    BoxShape* bshape;
    const xmlChar* boxShapeTag;
    const xmlChar* nodeName;
    const xmlChar* nodeType;
    int   x1;
    int   x2;
    int   y1;
    int   y2;

    // Reading the current xml line
    boxShapeTag = xmlTextReaderConstString(reader, (const xmlChar*)"box");
    nodeName = xmlTextReaderConstLocalName(reader);
    nodeType = xmlTextReaderNodeType(reader);
   
    // Checking the content
    bshape = NULL;
    if (nodeType == XML_READER_TYPE_ELEMENT and nodeName == boxShapeTag)
    {
      x1 = atoi(xmlCharToString(xmlTextReaderGetAttibute( reader, (const xmlChar*)
      "x1")).c_str());
      x2 = atoi(xmlCharToString(xmlTextReaderGetAttibute( reader, (const xmlChar*)
      "x2")).c_str());
      y1 = atoi(xmlCharToString(xmlTextReaderGetAttibute( reader, (const xmlChar*
      "y1")).c_str());
      y2 = atoi(xmlCharToString(xmlTextReaderGetAttibute( reader, (const xmlChar*
      "y2")).c_str());
      
      bshape = new BoxShape(owner, x1, x2, y1, y2);
    }
    return bshape;
  }
}

