#include <QApplication>
#include "iChargerGUI.hpp"


int main(int argc, char **argv){
	QApplication qapp(argc,argv);
	iCharger::GUI gui;

	return qapp.exec();

}
