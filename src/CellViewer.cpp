
#include "CellViewer.h"
#include "Cell.h"
#include "CellWidget.h"
#include "SaveCellDialog.h"

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

    setCentralWidget(cellWidget_);

    // Top menu
    QMenu* fileMenu = menuBar()->addMenu("&File");

    QAction* action = new QAction("&Save As", this);
    action->setStatusTip("Save to disk (rename)");
    action->setShortcut(QKeySequence("CTRL+S"));
    action->setVisible(true);
    fileMenu->addAction(action);
    connect(action, SIGNAL(triggered()), this, SLOT(saveCell()));  // Event handling

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

  void        CellViewer::setCell ( Cell* cell )
  { cellWidget_->setCell(cell); }

  Cell*       CellViewer::getCell ( ) const
  { return cellWidget_->getCell(); }

}
