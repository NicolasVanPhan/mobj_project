
#include "CellViewer.h"
#include "Cell.h"
#include "CellWidget.h"
#include "SaveCellDialog.h"
#include "OpenCellDialog.h"
#include "InstancesWidget.h"
#include "CellsLib.h"

namespace Netlist {

  CellViewer::CellViewer ( QWidget* parent)
    : QMainWindow (parent)
      , cellWidget_ (NULL)
      , saveCellDialog_ (NULL)
  {
    /* -------- Step 1 : Setup all widgets inside the main window -------- */
    /* -------- Step 2 : Handle events in the same time -------- */
    // Main frame of the application
    cellWidget_ = new CellWidget();
    // "Save Cell" popup that appears when user saves a cell
    saveCellDialog_ = new SaveCellDialog(this);
    openCellDialog_ = new OpenCellDialog(this);
    instancesWidget_ = new InstancesWidget();
    cellsLib_ = new CellsLib();

    setCentralWidget(cellWidget_);

    // Top menu
    QMenu* fileMenu = menuBar()->addMenu("&File");

    QAction* action = new QAction("&Save As", this);
    action->setStatusTip("Save to disk (rename)");
    action->setShortcut(QKeySequence("CTRL+S"));
    action->setVisible(true);
    fileMenu->addAction(action);
    connect(action, SIGNAL(triggered()), this, SLOT(saveCell()));  // Event handling

    action = new QAction("&Open", this);
    action->setStatusTip("Open from disk");
    action->setShortcut(QKeySequence("CTRL+O"));
    action->setVisible(true);
    fileMenu->addAction(action);
    connect(action, SIGNAL(triggered()), this, SLOT(openCell()));  // Event handling

    action = new QAction("&Load Instance", this);
    action->setStatusTip("Load instance");
    action->setShortcut(QKeySequence("CTRL+L"));
    action->setVisible(true);
    fileMenu->addAction(action);
    connect(action, SIGNAL(triggered()), this, SLOT(showInstancesWidget()));
    
    action = new QAction("&Switch cell", this);
    action->setStatusTip("Switch to another loaded cell");
    action->setShortcut(QKeySequence("CTRL+C"));
    action->setVisible(true);
    fileMenu->addAction(action);
    connect(action, SIGNAL(triggered()), this, SLOT(showCellsLib()));

    action = new QAction("&Quit", this);
    action->setStatusTip("Exit the Netlist Viewer");
    action->setShortcut(QKeySequence("CTRL+Q"));
    action->setVisible(true);
    fileMenu->addAction(action);
    connect(action, SIGNAL(triggered()), this, SLOT(close()));  // Event handling
  }

  CellViewer::~CellViewer ( )
  { }

  void        CellViewer::saveCell ( )
  {
    Cell* cell = getCell();

    if ( cell == NULL ) return;

    QString cellName = cell->getName().c_str();

    if (saveCellDialog_->run(cellName)) {
      cell->setName(cellName.toStdString());
      cell->save(cellName.toStdString());
    }
  }

  void        CellViewer::openCell ( )
  {
    QString cellName;
    Cell*   newcell;

    if (openCellDialog_->run(cellName)) {
      newcell = Cell::find(cellName.toStdString());
      // If the specified cell has not already been loaded, load it 
      if (newcell == NULL)
        newcell = Cell::load(cellName.toStdString()); 
        // TODO : Add a "emit cellloaded here for sync with CellsLib"
        // If the cell has been successfully loaded (or was already loaded), set it
      if (newcell != NULL)
        setCell(newcell);
    }
  }

  void      CellViewer::showInstancesWidget ( )
  {
    instancesWidget_->setCell(getCell());
    instancesWidget_->setCellViewer(this);
    instancesWidget_->show();
  }

  void      CellViewer::showCellsLib ( )
  {
    cellsLib_->setCellViewer(this);
    cellsLib_->show(); 
  }

  void        CellViewer::setCell ( Cell* cell )
  { cellWidget_->setCell(cell); }

  Cell*       CellViewer::getCell ( ) const
  { return cellWidget_->getCell(); }

}
