
#include <QAbstractTableModel>
#include "Cell.h"

namespace Netlist {

  class CellsModel : public QAbstractTableModel {
    Q_OBJECT;

    public :
    CellsModel ( QObject* parent = NULL );
    ~CellsModel ( );

    // functions expexted by Qt
    int       rowCount    ( const QModelIndex& parent=QModelIndex() ) const;
    int       columnCount ( const QModelIndex& parent=QModelIndex() ) const;
    QVariant  data        ( const QModelIndex&, int role=Qt::DisplayRole)const;
    QVariant  headerData  ( int, Qt::Orientation,int role=Qt::DisplayRole)const;
    // custom functions
    Cell*     getCell     ( int row );

    public slots :
    void      updateDatas ( );
  };
}
