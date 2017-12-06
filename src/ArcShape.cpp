
#include "Shapes.h"

namespace Netlist {

  ArcShape::ArcShape      ( Symbol* owner, const Box& box, int start, int span)
    :Shape(owner), box_(box), start_(start), span_(span)
  { }

  ArcShape::ArcShape      ( Symbol* owner, int x1, int y1, int x2, int y2,
      int start, int span)
    :Shape(owner), box_(x1, y1, x2, y2), start_(start), span_(span)
  { }

  ArcShape::~ArcShape      ( ) 
  { }

  Box     ArcShape::getBoundingBox () const
  { return box_; }

  void    ArcShape::toXml ( std::ostream& stream ) const
  {
    stream << indent
      << "<arc x1=\""<< box_.getX1() << "\" "
      << "y1=\"" << box_.getY1() << "\" "
      << "x2=\"" << box_.getX2() << "\" "
      << "y2=\"" << box_.getY2() << "\" "
      << "start=\"" << start_ << "\" "
      << "span=\"" << span_ << "\"/>" << std::endl;   
  }

  ArcShape*   ArcShape::fromXml (Symbol* owner, xmlTextReaderPtr reader)
  {
    ArcShape* ashape;
    const xmlChar* arcShapeTag;
    const xmlChar* nodeName;
    int            nodeType;
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
      x1 = atoi(xmlCharToString(xmlTextReaderGetAttribute( reader, (const xmlChar*)
      "x1")).c_str());
      x2 = atoi(xmlCharToString(xmlTextReaderGetAttribute( reader, (const xmlChar*)
      "x2")).c_str());
      y1 = atoi(xmlCharToString(xmlTextReaderGetAttribute( reader, (const xmlChar*)
      "y1")).c_str());
      y2 = atoi(xmlCharToString(xmlTextReaderGetAttribute( reader, (const xmlChar*)
      "y2")).c_str());
      start = atoi(xmlCharToString(xmlTextReaderGetAttribute( reader,
      (const xmlChar*)"start")).c_str());
      span = atoi(xmlCharToString(xmlTextReaderGetAttribute( reader,
      (const xmlChar*)"span")).c_str());

      ashape = new ArcShape(owner, x1, y1, x2, y2, start, span);
    }
    return ashape;
  }

}

