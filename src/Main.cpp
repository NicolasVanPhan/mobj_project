
#include <QApplication>
#include <QtGui>
#include "CellViewer.h"

using namespace Netlist;

int   main (int argc, char* argv[]) {
  QApplication*   qa = new QApplication(argc, argv);

  /* CellViewer* viewer = new CellViewer();
  viewer->setCell(halfadder);
  viewer->show(); */

  int rvalue = qa->exec();
  delete qa;
  return rvalue;
}
