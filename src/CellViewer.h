
#ifndef NETLIST_CELL_VIEWER_H
#define NETLIST_CELL_VIEWER_H

#include <QMainWindow>
#include <QLineEdit>
#include <QMenuBar>
#include <QAction>
#include <QMenu>

/*
 ** Type :    QMainWindow -> WIDGET
 **
 ** This widget corresponds to the main window of the application
 */
namespace Netlist {

  class Cell;
  class CellWidget;
  class SaveCellDialog;
  class OpenCellDialog;
  class InstancesWidget;
  class CellsLib;

  class CellViewer : public QMainWindow {
    Q_OBJECT;

    public :
    CellViewer    ( QWidget* parent = NULL );
    virtual         ~CellViewer   ( );
    void            setCell       ( Cell* );
    Cell*           getCell       ( ) const;

    public slots :
      void            saveCell            ( );
      void            openCell            ( );
      void            showInstancesWidget ( );
      void            showCellsLib        ( );

    private :
    CellWidget*       cellWidget_;
    SaveCellDialog*   saveCellDialog_;
    OpenCellDialog*   openCellDialog_;
    InstancesWidget*  instancesWidget_;
    CellsLib*         cellsLib_;
  };
}

#endif

