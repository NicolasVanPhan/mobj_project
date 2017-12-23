
#ifndef NETLIST_SAVE_CELL_DIALOG_H
#define NETLIST_SAVE_CELL_DIALOG_H

#include <QDialog>
#include <QLineEdit>

/*
 ** Type :   WIDGET
 **
 ** This widget corresponds to the pop-up "Save Cell"
 */
namespace Netlist {

  class SaveCellDialog : public QDialog {
    Q_OBJECT;

    public :
                    SaveCellDialog ( QWidget* parent = NULL );
    bool            run            ( QString& name );
    const QString   getCellName    ( ) const;
    void            setCellName    ( const QString& );

    protected :
    QLineEdit*      lineEdit_;
  };
}

#endif
