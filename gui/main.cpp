#include <QApplication>
#include "iChargerGUI.hpp"
#include <stdio.h>


int main(int argc, char **argv){
	if(argc != 2){
		fprintf(stderr,"Plaease give the portname of the icharger e.g. ./iCharger /dev/ttyUSB0\n");
		return -1;
	}
	char *port = argv[1];
	QApplication qapp(argc,argv);
	iCharger::GUI gui(port);

	return qapp.exec();

}
