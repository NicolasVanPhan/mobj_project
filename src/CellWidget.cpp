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
    int frameWidth  = 460;
    int frameHeight = 100;
    QRect nameRect ( xToScreenX(100)
                   , yToScreenY(100)
                   , frameWidth
                   , frameHeight
                   );
    painter.drawRect( nameRect );
    painter.drawText( nameRect, Qt::AlignCenter, cellName );

    // Draw the viewport
    painter.setPen( QPen(Qt::red, 0) );
    QRect viewRect = boxToScreenRect(viewport_);
    viewRect.adjust(0, 0, -1, -1);
    painter.drawRect( viewRect );

    // Draw the whole cell
    drawInstances(cell_, &painter);
    drawExternalTerms(&painter);
  }

  void    CellWidget::drawInstances       ( Cell* cell, QPainter* painter ) {
    const vector<Instance*>&  instances = cell->getInstances();
    Symbol*                   symbol;
    vector<Shape*>            shapes;

    // For each Instance
    for (size_t i = 0; i < instances.size(); i++) {
      symbol  = instances[i]->getMasterCell()->getSymbol();
      if (not symbol) continue;
      shapes = symbol->getShapes();

      drawShapes(instances[i], painter);
      drawInternalTerms(instances[i], painter);
    }
  }

  void    CellWidget::drawShapes          ( Instance* instance , QPainter* painter) {
    Point         instPos = instance->getPosition();
    const Symbol* symbol  = instance->getMasterCell()->getSymbol();
    if (not symbol) return;

    // Draw Symbol (except terms)
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
        painter->drawArc(boxToScreenRect(arc->getBoundingBox().translate(instPos)),
            arc->getStart() * 16, arc->getSpan() * 16);
      }
      else if (ellipse) {   // Ellipse drawing
        painter->setPen( QPen(Qt::darkGreen, 2) );
        QRect rect = boxToScreenRect(ellipse->getBoundingBox().translate(instPos));
        painter->drawEllipse(rect);
      }
    }
  }

  void    CellWidget::drawInternalTerms   ( Instance* instance, QPainter* painter ) {
    Point         instPos = instance->getPosition();
    const Symbol* symbol  = instance->getMasterCell()->getSymbol();
    QFont         smallFont = QFont( "URW Bookman L", 9, QFont::Bold);
    if (not symbol) return;
    const vector<Shape*>& shapes = symbol->getShapes();

    for (size_t j = 0; j < shapes.size(); j++) {
      TermShape*    term            = dynamic_cast<TermShape*>(shapes[j]);
      int           termWidth       = 3;
      int           textBoxLength   = 50;
      if (term) {
        /* Draw the term itself */
        painter->setPen( QPen(Qt::darkRed, 1) );
        painter->setBrush( QBrush(Qt::darkRed, Qt::SolidPattern) );
        QRect rect = boxToScreenRect(term->getBoundingBox().inflate(termWidth).translate(instPos));
        painter->drawRect(rect);

        /* Draw the terminal name */
        Point textBoxAlign;
        int   textBoxShift = textBoxLength + termWidth;
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
        Box textBox = term->getBoundingBox().inflate(textBoxLength).translate(textBoxAlign).translate(instPos);
        QRect textRect = boxToScreenRect( textBox );

        // Draw the terminal name
        painter->setFont( smallFont );
        painter->setBrush( Qt::NoBrush );
        painter->drawText( textRect, textAlign, term->getTerm()->getName().c_str() );
      }
    }
  }

  void    CellWidget::drawExternalTerms   ( QPainter* painter) {
    std::vector<Term*>  extTerms = cell_->getTerms();
    QFont               smallFont = QFont( "URW Bookman L", 9, QFont::Bold);
    int                 termWidth = 6;
    int                 textBoxLength = 50;

    // Foreach external terminal
    for (size_t i = 0; i < extTerms.size(); i++) {
      /* Draw the terminal */
      Term*   term = extTerms[i];
      Point   termPos = term->getNode()->getPosition();
      QPoint  points[5];

      // Construct the polygon of the external polygon
      if (term->getDirection() == Term::In) {
        points[0] = pointToScreenPoint( Point (termPos.getX() - termWidth   , termPos.getY() + termWidth) );
        points[1] = pointToScreenPoint( Point (termPos.getX()               , termPos.getY() + termWidth) );
        points[2] = pointToScreenPoint( Point (termPos.getX() + termWidth   , termPos.getY()            ) );
        points[3] = pointToScreenPoint( Point (termPos.getX()               , termPos.getY() - termWidth) );
        points[4] = pointToScreenPoint( Point (termPos.getX() - termWidth   , termPos.getY() - termWidth) );
      }
      else { // External
        points[0] = pointToScreenPoint( Point (termPos.getX() + termWidth   , termPos.getY() - termWidth) );
        points[1] = pointToScreenPoint( Point (termPos.getX()               , termPos.getY() - termWidth) );
        points[2] = pointToScreenPoint( Point (termPos.getX() - termWidth   , termPos.getY()            ) );
        points[3] = pointToScreenPoint( Point (termPos.getX()               , termPos.getY() + termWidth) );
        points[4] = pointToScreenPoint( Point (termPos.getX() + termWidth   , termPos.getY() + termWidth) );
      }

      // Draw the terminal
      painter->setPen( QPen(Qt::darkRed, 1) );
      painter->setBrush( QBrush(Qt::darkRed, Qt::SolidPattern) );
      painter->drawPolygon(points, 5);

      /* Draw the terminal name */
      Point textBoxAlign;
      int   textBoxShift = textBoxLength + termWidth;
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
      Box textBox = Box( termPos.getX(), termPos.getY(), termPos.getX(), termPos.getY() );
      textBox.inflate(textBoxLength).translate(textBoxAlign);
      QRect textRect = boxToScreenRect( textBox );

      // Draw the terminal name
      painter->setFont( smallFont );
      painter->setBrush( Qt::NoBrush );
      painter->drawText( textRect, textAlign, term->getName().c_str() );
    }
  }

}  // Netlist namespace.
