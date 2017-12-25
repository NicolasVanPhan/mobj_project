// -*- explicit-buffer-name: "CellWidget.h<M1-MOBJ/8-10>" -*-

#ifndef NETLIST_CELL_WIDGET_H
#define NETLIST_CELL_WIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QRect>
#include <QPoint>
class QPainter;
#include "Box.h"


namespace Netlist {

  class Cell;
  class NodeTerm;


  class CellWidget : public QWidget {
      Q_OBJECT;
    public:
                      CellWidget         ( QWidget* parent=NULL );
      virtual        ~CellWidget         ();
              void    setCell            ( Cell* );
      inline  Cell*   getCell            () const;
      inline  int     xToScreenX         ( int x ) const;
      inline  int     yToScreenY         ( int y ) const;
      inline  int     screenXToX         ( int x ) const;
      inline  int     screenYToY         ( int y ) const;
      inline  QRect   boxToScreenRect    ( const Box& ) const;
      inline  QPoint  pointToScreenPoint ( const Point& ) const;
      inline  Box     screenRectToBox    ( const QRect& ) const;
      inline  Point   screenPointToPoint ( const QPoint& ) const;
      virtual QSize   minimumSizeHint    () const;
      virtual void    resizeEvent        ( QResizeEvent* );
      virtual void    keyPressEvent      ( QKeyEvent* );
              void    goUp               ( );
              void    goDown             ( );
              void    goLeft             ( );
              void    goRight            ( );
    protected:
      virtual void    paintEvent         ( QPaintEvent* );
    private:
      Cell* cell_;
      Box   viewport_;
  };


  inline Cell* CellWidget::getCell () const { return cell_; }

  inline int   CellWidget::xToScreenX ( int x ) const
  { return x - viewport_.getX1(); }

  inline int   CellWidget::yToScreenY ( int y ) const
  { return viewport_.getY2() - y; }

  inline int   CellWidget::screenXToX ( int x ) const
  { return x + viewport_.getX1(); }

  inline int   CellWidget::screenYToY ( int y ) const
  { return viewport_.getY2() - y; }

  inline  QRect   CellWidget::boxToScreenRect    ( const Box& box) const
  {
    int x = xToScreenX(box.getX1());
    int y = yToScreenY(box.getY1());
    return QRect (x, y, box.getWidth(), box.getHeight());
  }

  inline  Box     CellWidget::screenRectToBox    ( const QRect& qrect) const
  {
    int x1 = screenXToX(qrect.x());
    int y1 = screenYToY(qrect.y());
    return Box (x1, y1, x1 + qrect.width(), y1 + qrect.height());
  }

  inline  QPoint  CellWidget::pointToScreenPoint ( const Point& point) const
  {
    int x = xToScreenX(point.getX());
    int y = yToScreenY(point.getY());
    return QPoint (x, y);
  }

  inline  Point   CellWidget::screenPointToPoint ( const QPoint& qpoint) const
  {
    int x = screenXToX(qpoint.x());
    int y = screenYToY(qpoint.y());
    return Point (x, y);
  }
}  // Netlist namespace.

#endif  // NETLIST_CELL_WIDGET_H
