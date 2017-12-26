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
    QFont  bigFont = QFont( "URW Bookman L", 36 );

    QString cellName = "NULL";
    if (cell_) cellName = cell_->getName().c_str();

    QPainter painter(this);
    painter.setFont      ( bigFont );
    painter.setBackground( QBrush( Qt::black ) );
    painter.eraseRect    ( QRect( QPoint(0,0), size() ) );

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

    // Draw the cell
    //std::cout << "Cell name : " << cell_->getName() << std::endl;
    const vector<Instance*>& instances = cell_->getInstances();
    // for each instance
    for (size_t i = 0; i < instances.size(); i++) {
      //std::cout << "Got one instance: " << instances[i]->getName() << std::endl;
      Point         instPos = instances[i]->getPosition();
      //std::cerr << "position : " << instPos << std::endl;
      const Symbol* symbol  = instances[i]->getMasterCell()->getSymbol();
      if (not symbol) continue;
      //std::cerr << "Got symbol" << std::endl;
      const vector<Shape*>& shapes = symbol->getShapes();
      for (size_t j = 0; j < shapes.size(); j++) {
        //std::cerr << "Got a shape" << std::endl;
        BoxShape*     box       = dynamic_cast<BoxShape*>(shapes[j]);
        LineShape*    line      = dynamic_cast<LineShape*>(shapes[j]);
        ArcShape*     arc       = dynamic_cast<ArcShape*>(shapes[j]);
        EllipseShape* ellipse   = dynamic_cast<EllipseShape*>(shapes[j]);
        if (box) {      // Box drawing
          painter.setPen( QPen(Qt::darkGreen, 2) );
          QRect rect = boxToScreenRect(box->getBoundingBox().translate(instPos));
          painter.drawRect(rect);
        }
        if (line) {     // Line drawing
          //std::cout << "Got a line!" << std::endl;
          painter.setPen( QPen(Qt::darkGreen, 2) );
          QLine qline (xToScreenX(line->getX1() + instPos.getX()),
              yToScreenY(line->getY1() + instPos.getY()),
              xToScreenX(line->getX2() + instPos.getX()),
              yToScreenY(line->getY2() + instPos.getY()));
          painter.drawLine(qline);
        }
        if (arc) {      // Arc drawing
          painter.setPen( QPen(Qt::darkGreen, 2) );
          //std::cout << "Got an arc!" << std::endl;
          painter.drawArc(boxToScreenRect(arc->getBoundingBox().translate(instPos)),
              arc->getStart() * 16, arc->getSpan() * 16);
        }
        if (ellipse) {
          painter.setPen( QPen(Qt::darkGreen, 2) );
          QRect rect = boxToScreenRect(ellipse->getBoundingBox().translate(instPos));
          painter.drawEllipse(rect);
        }
        //Box   box = shapes[j]->getBoundingBox();
        //QRect rect = boxToScreenRect(box.translate(instPos));
        //painter.setPen( QPen(Qt::red, 0) );
        //painter.drawRect(rect);
      }
    }
  }

}  // Netlist namespace.
