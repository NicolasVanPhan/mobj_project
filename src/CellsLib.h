
#include <QWidget>
#include <QTableView>
#include <QPushButton>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "CellViewer.h"
#include "CellsModel.h"

namespace Netlist {

  class CellsLib : public QWidget {
    Q_OBJECT;

    public :
                            CellsLib        ( QWidget* parent = NULL );
            void            setCellViewer   ( CellViewer* );
            int             getSelectedRow  ( ) const;
    inline  CellsModel*     getBaseModel    ( ) const;   

    public slots :
            void            load            ( );

    private :
    CellViewer*   cellViewer_;
    CellsModel*   baseModel_;
    QTableView*   view_;
    QPushButton*   load_;
  };

  inline CellsModel*  CellsLib::getBaseModel ( ) const
  { return baseModel_; }
}
