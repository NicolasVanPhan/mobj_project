
#ifndef NETLIST_OPEN_CELL_DIALOG_H
#define NETLIST_OPEN_CELL_DIALOG_H

#include <QDialog>
#include <QLineEdit>

/*
 ** Type :   WIDGET
 **
 ** This widget corresponds to the pop-up "Open Cell"
 */
namespace Netlist {

  class OpenCellDialog : public QDialog {
    Q_OBJECT;

    public :
                    OpenCellDialog ( QWidget* parent = NULL );
    bool            run            ( QString& name );
    const QString   getCellName    ( ) const;
    void            setCellName    ( const QString& );

    protected :
    QLineEdit*      lineEdit_;
  };
}

#endif
