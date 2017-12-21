                            
#include "CellsLib.h"

namespace Netlist {

  CellsLib::CellsLib        ( QWidget* parent )
    :QWidget(parent)
     , cellViewer_  (NULL)
     , baseModel_   (new CellsModel(this))
     , view_        (new QTableView())
     , load_        (new QPushButton())
  {
    // define behaviour on button clicks
    setAttribute ( Qt::WA_QuitOnClose, false );
    setAttribute ( Qt::WA_DeleteOnClose, false );
    setContextMenuPolicy ( Qt::ActionsContextMenu );

    // set table characteristics
    view_->setShowGrid(false);
    view_->setAlternatingRowColors(true);
    view_->setSelectionBehavior(QAbstractItemView::SelectRows);
    view_->setSelectionMode(QAbstractItemView::SingleSelection);
    view_->setSortingEnabled(true);
    view_->setModel(baseModel_);

    // set table headers characteristics
    QHeaderView* hheader = view_->horizontalHeader();
    hheader->setDefaultAlignment(Qt::AlignHCenter);
    hheader->setMinimumSectionSize(300);
    hheader->setStretchLastSection(true);
    QHeaderView* vheader = view_->verticalHeader();
    vheader->setVisible(false);

    // layout
    QHBoxLayout* hlayout = new QHBoxLayout();
    hlayout->addStretch();
    hlayout->addWidget(load_);
    hlayout->addStretch();

    QVBoxLayout* vlayout = new QVBoxLayout();
    vlayout->addWidget(view_);
    vlayout->addLayout(hlayout);
    setLayout(vlayout);

    // load button
    load_->setText("Load");
    connect(load_, SIGNAL(clicked()), this, SLOT(load()));

  }

  void            CellsLib::setCellViewer   ( CellViewer* viewer)
  { cellViewer_ = viewer; }

  int             CellsLib::getSelectedRow  ( ) const
  {
    QModelIndexList selecteds = view_->selectionModel()->selection().indexes();
    if (selecteds.empty()) return -1;
    return selecteds.first().row();
  }

  void            CellsLib::load            ( )
  {
    int row = getSelectedRow();

    if (row < 0) return;
    cellViewer_->setCell(baseModel_->getCell(row));
  }
}
