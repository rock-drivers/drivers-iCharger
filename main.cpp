#include "iCharger.h"
#include <string>
#include <stdio.h>
#include <math.h>

using namespace std;

int main(int argc, char**argv){
	if(argc<2){
		fprintf(stderr,"use \n./iCharger_test <device> \n");
		return -1;
	}


	iCharger::Driver driver;
	iCharger::Data data;

	driver.init(argv[1]);
	while(1){
		if(driver.getData(data)){
		}
	}

}
