
#include "InstancesWidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

namespace Netlist {

  InstancesWidget::InstancesWidget ( QWidget* parent )
    : QWidget (parent)
      , cellViewer_ (NULL)
      , baseModel_  (new InstancesModel(this))
      , view_       (new QTableView())
      , load_       (new QPushButton())
  {
    // define behaviour on button clicks
    setAttribute ( Qt::WA_QuitOnClose, false );
    setAttribute ( Qt::WA_DeleteOnClose, false );
    setContextMenuPolicy ( Qt::ActionsContextMenu );

    // set tables characteristics
    view_->setShowGrid(false);
    view_->setAlternatingRowColors(true);
    view_->setSelectionBehavior(QAbstractItemView::SelectRows);
    view_->setSelectionMode(QAbstractItemView::SingleSelection);
    view_->setSortingEnabled(true);
    view_->setModel(baseModel_);

    // table headers
    QHeaderView* horizontalHeader = view_->horizontalHeader();
    horizontalHeader->setDefaultAlignment(Qt::AlignHCenter);
    horizontalHeader->setMinimumSectionSize(300);
    horizontalHeader->setStretchLastSection(true);
    QHeaderView* verticalHeader = view_->verticalHeader();
    verticalHeader->setVisible(false);

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

  void    InstancesWidget::setCellViewer ( CellViewer* viewer )
  { cellViewer_ = viewer; }

  int     InstancesWidget::getSelectedRow ( ) const
  {
    QModelIndexList selecteds = view_->selectionModel()->selection().indexes();

    if (selecteds.empty()) return -1;
    return selecteds.first().row();
  }

  void    InstancesWidget::load ( )
  {
    int row = getSelectedRow();

    if (row < 0) return;
    cellViewer_->setCell(baseModel_->getModel(row));
  }
}
