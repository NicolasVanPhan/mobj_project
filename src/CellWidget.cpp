// -*- explicit-buffer-name: "CellWidget.cpp<M1-MOBJ/8-10>" -*-

#include  <QResizeEvent>
#include  <QPainter>
#include  <QPen>
#include  <QBrush>
#include  <QFont>
#include  <QApplication>
#include  "CellWidget.h"
#include  "Term.h"
#include  "Instance.h"
#include  "Symbol.h"
#include  "Shape.h"
#include  "BoxShape.h"
#include  "LineShape.h"
#include  "ArcShape.h"
#include  "EllipseShape.h"
#include  "TermShape.h"
#include  "Cell.h"
#include  "Line.h"
#include  "Node.h"
#include  "Net.h"


namespace Netlist {

  using namespace std;


  ostream& operator<< ( ostream& o, const QRect& rect )
  {
    o << "<QRect x:" << rect.x()
      <<       " y:" << rect.y()
      <<       " w:" << rect.width()
      <<       " h:" << rect.height() << ">";
    return o;
  }


  ostream& operator<< ( ostream& o, const QPoint& p )
  { o << "<QRect x:" << p.x() << " y:" << p.y() << ">"; return o; }



  CellWidget::CellWidget ( QWidget* parent )
    : QWidget(parent)
    , cell_  (NULL)
    , viewport_ (Box(0, 0, 500, 500))
  {
    setAttribute    ( Qt::WA_OpaquePaintEvent );
    setAttribute    ( Qt::WA_NoSystemBackground );
    setAttribute    ( Qt::WA_StaticContents );
    setSizePolicy   ( QSizePolicy::Expanding, QSizePolicy::Expanding );
    setFocusPolicy  ( Qt::StrongFocus );
    setMouseTracking( true );
  }


  CellWidget::~CellWidget ()
  { }


  void  CellWidget::setCell ( Cell* cell )
  {
    cell_ = cell;
    repaint();
  }


  QSize  CellWidget::minimumSizeHint () const
  { return QSize(500,500); }


  void  CellWidget::resizeEvent ( QResizeEvent* event )
  {
    const QSize& size = event->size();

    viewport_.setX2(viewport_.getX1() + size.width());
    viewport_.setY1(viewport_.getY2() - size.height());
    repaint();
  }

  void  CellWidget::keyPressEvent ( QKeyEvent* event )
  {
    event->ignore();
    if (event->modifiers() & (Qt::ControlModifier | Qt::ShiftModifier))
      return;

    switch (event->key()) {
      case Qt::Key_Up:      goUp (); break;
      case Qt::Key_Down:    goDown (); break;
      case Qt::Key_Left:    goLeft (); break;
      case Qt::Key_Right:   goRight (); break;
    }
    event->accept();
  }

  void  CellWidget::goUp    ( ) {
    viewport_.translate( Point(0, 20) );
    repaint();
  }

  void  CellWidget::goDown    ( ) {
    viewport_.translate( Point(0, -20) );
    repaint();
  }

  void  CellWidget::goLeft    ( ) {
    viewport_.translate( Point(-20, 0) );
    repaint();
  }

  void  CellWidget::goRight    ( ) {
    viewport_.translate( Point(20, 0) );
    repaint();
  }

  void  CellWidget::paintEvent ( QPaintEvent* event )
  {
    // Set fonts
    QFont  bigFont = QFont( "URW Bookman L", 36 );
    QFont  smallFont = QFont( "URW Bookman L", 9, QFont::Bold);

    // Get cell name
    QString cellName = "NULL";
    if (cell_) cellName = cell_->getName().c_str();

    // Set Pen
    QPainter painter(this);
    painter.setFont      ( bigFont );
    painter.setBackground( QBrush( Qt::black ) );
    painter.eraseRect    ( QRect( QPoint(0,0), size() ) );

    // Draw default figure (a gray frame with the cell's name inside)
    /* int frameWidth  = 460;
    int frameHeight = 100;
    QRect nameRect ( xToScreenX(100)
                   , yToScreenY(100)
                   , frameWidth
                   , frameHeight
                   );
    painter.drawRect( nameRect );
    painter.drawText( nameRect, Qt::AlignCenter, cellName ); */

    // Draw the current cell
    drawNets(cell_, &painter);
    drawInstances(cell_, &painter);
    drawExternalTerms(&painter);
  }

  void    CellWidget::drawInstances       ( Cell* cell, QPainter* painter ) {
    const vector<Instance*>&  instances = cell->getInstances();
    Symbol*                   symbol;
    vector<Shape*>            shapes;

    // For each Instance
    for (size_t i = 0; i < instances.size(); i++) {
      // Get the shapes to draw
      symbol  = instances[i]->getMasterCell()->getSymbol();
      if (not symbol) continue;
      shapes = symbol->getShapes();
      // Then draw them
      drawShapes(instances[i], painter);
      drawInternalTerms(instances[i], painter);
    }
  }

  void    CellWidget::drawShapes   ( Instance* instance , QPainter* painter) {
    Point         instPos = instance->getPosition();
    const Symbol* symbol  = instance->getMasterCell()->getSymbol();
    if (not symbol) return;

    // Draw all the symbol's shapes (except terms)
    const vector<Shape*>& shapes = symbol->getShapes();
    for (size_t j = 0; j < shapes.size(); j++) {
      BoxShape*     box       = dynamic_cast<BoxShape*>(shapes[j]);
      LineShape*    line      = dynamic_cast<LineShape*>(shapes[j]);
      ArcShape*     arc       = dynamic_cast<ArcShape*>(shapes[j]);
      EllipseShape* ellipse   = dynamic_cast<EllipseShape*>(shapes[j]);

      if (box) {            // Box drawing
        painter->setPen( QPen(Qt::darkGreen, 2) );
        QRect rect = boxToScreenRect(box->getBoundingBox().translate(instPos));
        painter->drawRect(rect);
      }
      else if (line) {      // Line drawing
        painter->setPen( QPen(Qt::darkGreen, 2) );
        QLine qline (xToScreenX(line->getX1() + instPos.getX()),
            yToScreenY(line->getY1() + instPos.getY()),
            xToScreenX(line->getX2() + instPos.getX()),
            yToScreenY(line->getY2() + instPos.getY()));
        painter->drawLine(qline);
      }
      else if (arc) {       // Arc drawing
        painter->setPen( QPen(Qt::darkGreen, 2) );
        /* the arc's start and span are angles in degrees, however drawArc()
         * expect to have angles in 1/16th of degree, hence the *16 */
        QRect rect = boxToScreenRect(arc->getBoundingBox().translate(instPos));
        painter->drawArc(rect, arc->getStart() * 16, arc->getSpan() * 16);
      }
      else if (ellipse) {   // Ellipse drawing
        painter->setPen( QPen(Qt::darkGreen, 2) );
        QRect rect = boxToScreenRect(ellipse->getBoundingBox().translate(instPos));
        painter->drawEllipse(rect);
      }
    }
  }

  void CellWidget::drawInternalTerms ( Instance* instance, QPainter* painter ) {
    Point         instPos = instance->getPosition();
    const Symbol* symbol  = instance->getMasterCell()->getSymbol();
    QFont         smallFont = QFont( "URW Bookman L", 9, QFont::Bold);
    if (not symbol) return;
    const vector<Shape*>& shapes = symbol->getShapes();

    // For each shape of the instance's symbol
    for (size_t j = 0; j < shapes.size(); j++) {
      TermShape*    term            = dynamic_cast<TermShape*>(shapes[j]);
      int           termWidth       = 6;
      int           textBoxLength   = 100;

      // if the current shape is a term, draw it
      if (term) {
        /* Draw the term itself */
        painter->setPen( QPen(Qt::darkRed, 1) );
        painter->setBrush( QBrush(Qt::darkRed, Qt::SolidPattern) );
        QRect rect = boxToScreenRect(term->getBoundingBox().inflate(termWidth/2)
            .translate(instPos));
        painter->drawRect(rect);

        /* Draw the terminal name */
        // Set the textbox alignment
        Point textBoxAlign;
        int   textBoxShift = textBoxLength/2 + termWidth/2;
        int   textAlign;
        switch (term->getAlign()) {
          case TermShape::TopLeft :
            textBoxAlign = Point ( -textBoxShift, textBoxShift );
            textAlign = Qt::AlignBottom | Qt::AlignRight;
            break;
          case TermShape::TopRight :
            textBoxAlign = Point ( textBoxShift, textBoxShift );
            textAlign = Qt::AlignBottom | Qt::AlignLeft;
            break;
          case TermShape::BottomLeft :
            textBoxAlign = Point ( -textBoxShift, -textBoxShift );
            textAlign = Qt::AlignTop | Qt::AlignRight;
            break;
          case TermShape::BottomRight :
            textBoxAlign = Point ( textBoxShift, -textBoxShift );
            textAlign = Qt::AlignTop | Qt::AlignLeft;
            break;
          default : // align top left
            textBoxAlign = Point ( -textBoxShift, textBoxShift );
            textAlign = Qt::AlignBottom | Qt::AlignRight;
            break;
        }

        // Set the text framebox
        Box textBox = term->getBoundingBox().inflate(textBoxLength/2)
          .translate(textBoxAlign).translate(instPos);
        QRect textRect = boxToScreenRect( textBox );

        // Draw the terminal name
        painter->setFont( smallFont );
        painter->setBrush( Qt::NoBrush );
        painter->drawText( textRect, textAlign,
            term->getTerm()->getName().c_str() );
      }
    }
  }

  void    CellWidget::drawExternalTerms   ( QPainter* painter) {
    std::vector<Term*>  extTerms = cell_->getTerms();
    QFont               smallFont = QFont( "URW Bookman L", 9, QFont::Bold);
    int                 termWidth = 12;
    int                 textBoxLength = 100;

    // Foreach external terminal
    for (size_t i = 0; i < extTerms.size(); i++) {
      /* Draw the terminal */
      Term*   term = extTerms[i];
      Point   termPos = term->getNode()->getPosition();
      QPoint  points[5];

      // Construct the polygon of the external terminal
      if (term->getDirection() == Term::In) {
        points[0] = pointToScreenPoint(
            Point (termPos.getX()-termWidth/2, termPos.getY()+termWidth/2) );
        points[1] = pointToScreenPoint(
            Point (termPos.getX()            , termPos.getY()+termWidth/2) );
        points[2] = pointToScreenPoint(
            Point (termPos.getX()+termWidth/2, termPos.getY()            ) );
        points[3] = pointToScreenPoint(
            Point (termPos.getX()            , termPos.getY()-termWidth/2) );
        points[4] = pointToScreenPoint(
            Point (termPos.getX()-termWidth/2, termPos.getY()-termWidth/2) );
      }
      else { // term->getDirection() == Term::Out
        points[0] = pointToScreenPoint(
            Point (termPos.getX()+termWidth/2 , termPos.getY()-termWidth/2) );
        points[1] = pointToScreenPoint(
            Point (termPos.getX()             , termPos.getY()-termWidth/2) );
        points[2] = pointToScreenPoint(
            Point (termPos.getX()-termWidth/2 , termPos.getY()            ) );
        points[3] = pointToScreenPoint(
            Point (termPos.getX()             , termPos.getY()+termWidth/2) );
        points[4] = pointToScreenPoint(
            Point (termPos.getX()+termWidth/2 , termPos.getY()+termWidth/2) );
      }

      // Draw the terminal
      painter->setPen( QPen(Qt::darkRed, 1) );
      painter->setBrush( QBrush(Qt::darkRed, Qt::SolidPattern) );
      painter->drawPolygon(points, 5);

      /* Draw the terminal name */
      Point textBoxAlign;
      int   textBoxShift = textBoxLength/2 + termWidth/2;
      int   textAlign;

      // Set text alignment
      if (term->getDirection() == Term::In) {  // align bottom left
        textBoxAlign = Point ( -textBoxShift, -textBoxShift );
        textAlign = Qt::AlignTop | Qt::AlignRight;
      }
      else {  // align bottom right
        textBoxAlign = Point ( textBoxShift, -textBoxShift );
        textAlign = Qt::AlignTop | Qt::AlignLeft;
      }

      // Set the text framebox
      Box textBox = Box( termPos.getX(), termPos.getY(), termPos.getX(),
          termPos.getY() );
      textBox.inflate(textBoxLength/2).translate(textBoxAlign);
      QRect textRect = boxToScreenRect( textBox );

      // Draw the terminal name
      painter->setFont( smallFont );
      painter->setBrush( Qt::NoBrush );
      painter->drawText( textRect, textAlign, term->getName().c_str() );
    }
  }

  void    CellWidget::drawNets    ( Cell* cell, QPainter* painter ) {
    std::vector<Net*> nets = cell->getNets();
    int               dotLength = 3;

    // For each Net
    for (size_t i = 0; i < nets.size(); i++) {
      /* Draw the lines */
      const std::vector<Line*>& lines = nets[i]->getLines();
      // Set the pen
      painter->setPen( QPen(Qt::cyan, 1) );
      painter->setBrush( Qt::NoBrush );
      for (size_t j = 0; j < lines.size(); j++) {
        // Get the line
        Point srcPos = lines[j]->getSourcePosition();
        Point destPos = lines[j]->getTargetPosition();
        QLine qline( pointToScreenPoint(srcPos), pointToScreenPoint(destPos) );
        // Draw the line
        painter->drawLine(qline);
      }
      /* Draw the big dots */
      const std::vector<Node*> nodes = nets[i]->getNodes();
      // Set the pen
      painter->setPen( QPen(Qt::cyan, 1) );
      painter->setBrush( QBrush(Qt::cyan, Qt::SolidPattern) );
      for (size_t j = 0; j < nodes.size(); j++) {
        NodePoint* nodepoint = dynamic_cast<NodePoint*>(nodes[j]);
        if (nodepoint == NULL) continue;
        // Set the big dot
        QPoint center = pointToScreenPoint( nodepoint->getPosition() );
        // Draw the big dot
        painter->drawEllipse(center, dotLength, dotLength);
      }
    }
  }

}  // Netlist namespace.
