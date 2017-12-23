
#include "InstancesModel.h"
#include "Cell.h"
#include "Instance.h"

namespace Netlist {

  InstancesModel::InstancesModel    ( QObject* parent )
    : QAbstractTableModel(parent)
      , cell_(NULL)
  { }

  InstancesModel::~InstancesModel   ( )
  { }

  int       InstancesModel::rowCount    ( const QModelIndex& parent ) const
  { return (cell_) ? cell_->getInstances().size() : 0; }

  int       InstancesModel::columnCount ( const QModelIndex& parent ) const
  { return 2; } // two columns : Instance and its Mastercell

  QVariant  InstancesModel::data        ( const QModelIndex& index,
                                          int role ) const
  {
    // error handling
    if (not cell_ or not index.isValid()) return QVariant();

    // if the data required is the payload
    if (role == Qt::DisplayRole) {
      int row = index.row();
      switch (index.column()) {
        // Instance
        case 0 : return cell_->getInstances()[row]->getName().c_str();
        // MasterCell
        case 1 : return cell_->getInstances()[row]->getMasterCell()->
                 getName().c_str();
      }
    }
    // if the data required is metadata
    return QVariant();
  }

  QVariant  InstancesModel::headerData  ( int section,
                                          Qt::Orientation orientation,
                                          int role ) const
  {
    // Error handling
    // there's no vertical header here
    if (orientation == Qt::Vertical ) return QVariant();
    // this functions only returns payload, not metadata
    if (role != Qt::DisplayRole )     return QVariant();

    switch (section) {
      // Instance column
      case 0: return "Instance";
              // MasterCell column
      case 1: return "MasterCell";
    }
    // if column number is invalid
    return QVariant();
  }

  void      InstancesModel::setCell     ( Cell* cell )
  {
    emit layoutAboutToBeChanged(); // prevent the view from refreshing
    cell_ = cell;
    emit layoutChanged(); // update the *whole* view
  }

  Cell*     InstancesModel::getModel    ( int row )
  {
    // if the InstanceModel is "empty", no cell associated
    if (not cell_) return NULL;
    // if index is not within range
    if (row < 0 or row >= (int)cell_->getInstances().size()) return NULL;
    // otherwise, everything's okay
    return cell_->getInstances()[row]->getMasterCell();
  }
}
