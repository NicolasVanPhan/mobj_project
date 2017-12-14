
#include "InstancesWidget.h"

namespace Netlist {

  InstancesWidget::InstancesWidget ( QWidget* parent )
    : QWidget (parent)
      , cellViewer_ (NULL)
      , baseModel_  (new InstancesModel(this))
      , view_       (new QTableView(this))
      , load_       (new QPushButton(this))
  {
    // define behaviour on button clicks
    setAttribute ( Qt::WA_QuitOnClose, false );
    setAttribute ( Qt::WA_DeleteOnClose, false );
    setContextMenuPolicy ( Qt::ActionsContextMenu );

    // set tables characteristics
    view_->setShowGrid(false);
    view_->setAlternatingRowColors(true);
    view_->setSelectionBehaviour(QAbstractItemView::SelectRows);
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

    // load button
    load_->setText("Load");
    connect(load_, SIGNAL(clicked()), this, SLOT(load()));
  }

  InstancesWidget::getSelectedRow ( ) const
  {
    QModelIndexList selecteds = view_->selectionModel()->selection().indexes();
  }
}
