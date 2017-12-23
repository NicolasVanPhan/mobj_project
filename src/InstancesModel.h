
#include <QAbstractTableModel>

namespace Netlist {

  class Cell;

  class InstancesModel : public QAbstractTableModel {
    Q_OBJECT;

    public :
              InstancesModel  ( QObject* parent=NULL );
              ~InstancesModel ( );
    // functions expected by Qt :
    int       rowCount        ( const QModelIndex& parent=QModelIndex() ) const;
    int       columnCount     ( const QModelIndex& parent=QModelIndex() ) const;
    QVariant  data            ( const QModelIndex& index,
                                int role=Qt::DisplayRole ) const;
    QVariant  headerData      ( int section, Qt::Orientation orientation,
                                int role=Qt::DisplayRole ) const;
    // custom functions :
    void      setCell         ( Cell* );
    Cell*     getModel        ( int row );

    private :
    Cell*   cell_;
  };
}
