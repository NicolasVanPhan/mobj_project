
#include <QWidget>
#include <QTableView>
#include <QPushButton>
#include <QHeaderView>
#include "CellViewer.h"
#include "InstancesModel.h"

namespace Netlist {

  class Cell;

  class InstancesWidget : public QWidget {
    Q_OBJECT;

    public :
                InstancesWidget   ( QWidget* parent=NULL );
    void        setCellViewer     ( CellViewer* viewer );
    int         getSelectedRow    ( ) const;
    inline void setCell           ( Cell* cell );

    public slots :
      void      load              ( );

    private :
    CellViewer*       cellViewer_;  // Main Window
    InstancesModel*   baseModel_;   // Associated Model
    QTableView*       view_;
    QPushButton*      load_;
  };

  inline void InstancesWidget::setCell ( Cell* cell )
  {
    baseModel_->setCell(cell);
  }
}
