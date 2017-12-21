
#include "CellsModel.h"
#include <QAbstractItemModel>

namespace Netlist {

  CellsModel::CellsModel ( QObject* parent )
    : QAbstractTableModel(parent)
  {
  }

  CellsModel::~CellsModel ( )
  {
  }


  // functions expexted by Qt
  int       CellsModel::rowCount        ( const QModelIndex& parent ) const
  { return Cell::getAllCells().size(); }

  int       CellsModel::columnCount     ( const QModelIndex& parent ) const
  { return 1; }

  QVariant  CellsModel::data            ( const QModelIndex& index, int role ) const
  {
    // if asked for somethign else than the payload
    if (role != Qt::DisplayRole)        return QVariant();

    // if index is invalid
    int row = index.row();
    if (row < 0 or row >= rowCount())   return QVariant(); 

    return Cell::getAllCells()[row]->getName().c_str();
  }

  QVariant  CellsModel::headerData      ( int section, Qt::Orientation orientation, int role ) const
  {
    if (orientation != Qt::Horizontal)  return QVariant();
    if (role != Qt::DisplayRole)        return QVariant(); 
    return "Cell";
  }


  // custom functions
  Cell*     CellsModel::getCell         ( int row )
  {
    if (row < 0 or row >= rowCount())   return NULL; 
    return Cell::getAllCells()[row];
  }

  void      CellsModel::updateDatas     ( )
  {
    std::cerr << "update data..." << std::endl;
    emit layoutAboutToBeChanged();
    emit layoutChanged();
  }

}
