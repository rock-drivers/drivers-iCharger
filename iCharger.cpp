#include "iCharger.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <cstdio>
#include <math.h>
#include <vector>


namespace iCharger{

Driver::Driver():
	IODriver(512,false){

}

bool Driver::init(std::string const &port, bool const doLogging){
		this->doLogging=doLogging;
		if(doLogging){
			loggerFD = open("battery.log",O_WRONLY | O_APPEND | O_CREAT, 0755);
			if(loggerFD < 0){
				fprintf(stderr,"Cannot open logger File\n");
				return false;
			}
		}
		return openSerial(port,9600);
}

Driver::~Driver() {

}

int Driver::getReadFD() {
	return getFileDescriptor();
}




bool Driver::getData(Data &data){
    try {
	int bufsize = 512;
	uint8_t packed[bufsize];
	int len = readPacket(packed,bufsize,80,80);
	std::vector<int> values;
	char buff[len];
	int pos=0;
	if(len > 0 && doLogging){
		write(loggerFD,packed,len);
	}
	for(int i=1;i<len;i++){
		buff[pos] = packed[i];
		if(packed[i] == ';' || packed[i] == '\r'){
			buff[pos] = ' ';
			int value=0;
			sscanf(buff,"%i",&value);
			values.push_back(value);
			pos=0;
		}else{
			pos++;
		}
	}
	if(values.size() != 20){
		fprintf(stderr,"Unknown count of Values, what should i do %i?\n",values.size());
		return false;
	}

	if(values.size() == 20 && values[0] == 1){ //Alright, right count of values, Channel 1 and state is 1
		data.channel = values[0];
		data.state = values[1];
		data.timestamp = values[2];
		data.inputVoltage = values[3]/1000.0;
		data.availibleChannels = 10;	
		data.baseVoltage = values[4]/1000.0;
		data.current = values[5]/100.0;
		data.cellV[0] = values[6]/1000.0;
		data.cellV[1] = values[7]/1000.0;
		data.cellV[2] = values[8]/1000.0;
		data.cellV[3] = values[9]/1000.0;
		data.cellV[4] = values[10]/1000.0;
		data.cellV[5] = values[11]/1000.0;
		data.cellV[6] = values[12]/1000.0;
		data.cellV[7] = values[13]/1000.0;
		data.cellV[8] = values[14]/1000.0;
		data.cellV[9] = values[15]/1000.0;
		data.internalTemp = values[16]/10.0;
		data.externalTemp = values[17]/10.0;
		data.charged_mAh = values[18];
		data.checksum = values[19];
		return true;
	}else{
		fprintf(stderr,"Unknown format Size: %i, 0:%i, 1:%i\n",values.size(),values[0],values[1]);
	}

	//for(int i=0;i<values.size();i++){
	//	printf("Value %02i = %04i\n",i,values[i]);
	//}
	
	
	return false;
    } catch (timeout_error) { return false; }
}


int Driver::extractPacket(uint8_t const* buffer, size_t buffer_size) const {
		if(buffer[0] != '$') //Package start not detected yet
			return -1;

		//Semicolon needed for checksum calculation, up to the last semicloon the checksum should be calculated
		size_t lastSemicolon=0;

		for(size_t i=0;i<buffer_size;i++){ //Search for package end sign
			if(buffer[i] == ';') lastSemicolon=i;
			if(buffer[i-1] == '\r' && buffer[i] == '\n'){ //Found package end sign
				uint8_t checksum=0;
				for(size_t j=0;j<=lastSemicolon;j++){
					checksum^=buffer[j];
				}
				int check;
				sscanf((const char*)buffer+lastSemicolon+1,"%i",&check); //Acquiring checksum, parse from stream

				if(checksum == check){ //Checksum is valid
					return i+1;
				}else{
					fprintf(stderr,"Checksum invalid, should be %i, is %i\n",checksum,check);
					return -1;
				}
			}
		}
		return 0;
}

};
