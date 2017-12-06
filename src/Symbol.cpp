
#include "Shapes.h"

namespace Netlist {

  Symbol::Symbol ( Cell* owner )
    : owner_(owner), shapes_()
  {
  }

  Symbol::Symbol ( const Symbol& symbol)
    : owner_(symbol.getCell()), shapes_(symbol.getShapes()) // for shapes, the copy CTOR is called
  {
  }

  Symbol::~Symbol ()
  {
  }


  Cell*              Symbol::getCell         () const
  { return owner_; }

  Box                Symbol::getBoundingBox  () const
  {
    Box   bbox;
    std::vector<Shape*>::const_iterator it;
    for (it = shapes_.begin(); it != shapes_.end(); it++ ) {
      bbox.merge((*it)->getBoundingBox());
    }
    return bbox;
  }

  Point              Symbol::getTermPosition ( Term* term ) const
  {
    int x;
    int y;
    const TermShape* tshape;
    tshape = getTermShape(term);
    if (tshape != NULL)
    {
      x = tshape->getX();
      y = tshape->getY();
      return Point(x,y);      
    }
  }

  const TermShape*         Symbol::getTermShape    ( Term* term) const
  {
    std::vector<Shape*>::const_iterator it;
    const TermShape*    tshape;
    for (it = shapes_.begin(); it != shapes_.end(); ++it) {
      tshape = dynamic_cast<TermShape*>(*it);
      // if the current Shape* is indeed a TermShape* and points to the given Term
      if (tshape != NULL and tshape->getTerm() == term)
        return tshape;
    }
    return NULL;
  }

  void               Symbol::add             ( Shape* shape )
  {
    shapes_.push_back(shape);
  }

  void               Symbol::remove          ( Shape* shape )
  {
    std::vector<Shape*>::iterator it;
    for (it = shapes_.begin(); it != shapes_.end(); it++) {
      if (*it == shape) {
        shapes_.erase(it);
        return ;
      }
    }
  }

  void               Symbol::toXml           ( std::ostream& stream) const
  {
    std::vector<Shape*>::const_iterator it;

    stream << indent++ << "<symbol>" << std::endl;
    for (it = shapes_.begin(); it != shapes_.end(); it++)
      (*it)->toXml(stream);
    stream << --indent << "</symbol>" << std::endl;
  }

  Symbol*           Symbol::fromXml         ( Cell* owner, xmlTextReaderPtr reader)
  {
{
    enum State { endSymbol };
    const xmlChar*    symbolTag;
    const xmlChar*    boxTag;
    const xmlChar*    lineTag;
    const xmlChar*    termTag;
    const xmlChar*    ellipseTag;
    const xmlChar*    arcTag;
    const xmlChar*    nodeName;
    int               nodeType;
    Symbol*           symbol;
    State		          state;

    symbolTag = xmlTextReaderConstString( reader, (const xmlChar*)"symbol" );
    boxTag = xmlTextReaderConstString( reader, (const xmlChar*)"box" );
    lineTag = xmlTextReaderConstString( reader, (const xmlChar*)"line" );
    termTag = xmlTextReaderConstString( reader, (const xmlChar*)"term" );
    ellipseTag = xmlTextReaderConstString( reader, (const xmlChar*)"ellipse" );
    arcTag = xmlTextReaderConstString( reader, (const xmlChar*)"arc" );
    nodeName = xmlTextReaderConstLocalName(reader);
    nodeType = xmlTextReaderNodeType(reader);

    // if (line == "<symbol>")
    if (nodeName == symbolTag && nodeType == XML_READER_TYPE_ELEMENT)
    {
      state = endSymbol;

      // Retrieving the Symbol to set
      symbol = owner->getSymbol(); 

      // Read all Node
      while (true) {
        int status = xmlTextReaderRead(reader);
        // If reached EOF or current line is incorrect, exit failure
        if (status != 1) {
          std::cerr << "[ERROR] Net::fromXml(): "
            << "Unexpected termination of the XML parser."
            << std::endl;
          break;
        }

        // Pass comments and blank lines
        switch ( xmlTextReaderNodeType(reader) ) {
          case XML_READER_TYPE_COMMENT:
          case XML_READER_TYPE_WHITESPACE:
          case XML_READER_TYPE_SIGNIFICANT_WHITESPACE:
            continue;
        }

        nodeName = xmlTextReaderConstLocalName(reader);
        nodeType = xmlTextReaderNodeType(reader);

        std::cerr << "nodeName: " << xmlCharToString(nodeName) << std::endl;
        std::cerr << "nodeType: " << nodeType << std::endl;

        switch (state) {
          case endSymbol:
            // if line == </symbol>, finish reading correctly (return true)
            if ((nodeName == symbolTag) and
                (xmlTextReaderNodeType(reader)
                 == XML_READER_TYPE_END_ELEMENT)) { 
              return symbol; // finished reading, successfully
            }
            // if line == <someshape... />
            else if ((nodeName == boxTag
                  or nodeName == lineTag
                  or nodeName == termTag
                  or nodeName == ellipseTag
                  or nodeName == arcTag)
                and (xmlTextReaderNodeType(reader) == XML_READER_TYPE_ELEMENT)) {
              if (Shape::fromXml(symbol, reader)) continue;
            }
            else
              std::cerr << "No shape tag" << std::endl;
            // if line is incorrect, break
            break;
          default:
            break;
        } // end of switch
        // if any error occured, return incorrectly (return NULL)
        std::cerr << "[ERROR] Net::fromXml(): Unknown or misplaced tag <"
          << nodeName << "<"
          << "(line: " << xmlTextReaderGetParserLineNumber(reader)
          << ")." << std::endl;
        break;
      }
    } // end of while
    return NULL; // reading ended in failure
  }
  }


  Symbol&            Symbol::operator=       ( const Symbol& )
  {
  }
}

