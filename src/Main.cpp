
#include <QApplication>
#include <QtGui>
#include <string>
#include <string>
#include <sstream>
#include <iostream>
#include <memory>
using namespace std;

#include "CellViewer.h"
#include "Term.h"
#include "Net.h"
#include "Instance.h"
#include "Cell.h"
using namespace Netlist;


int main ( int argc, char* argv[] )
{
  QApplication* qa = new QApplication(argc, argv);

  cout << "Chargement des modeles..." << endl;
  Cell::load( "vdd" );
  Cell::load( "gnd" );
  Cell::load( "TransistorN" );
  Cell::load( "TransistorP" );
  Cell::load( "and2" );
  Cell::load( "or2" );
  Cell* xor2      = Cell::load( "xor2" );
  Cell* halfadder = Cell::load( "halfadder" );

  CellViewer* viewer = new CellViewer();
  viewer->setCell(halfadder);
  viewer->show();

  int rvalue = qa->exec();
  delete qa;
  return rvalue;
}
