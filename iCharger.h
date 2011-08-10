#ifndef _ICHARGER_H_
#define _ICHARGER_H_ 

#include <iodrivers_base.hh>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

namespace iCharger{

class Data{
public:
		int channel;
		int state;
		int timestamp;
		double inputVoltage;
		double baseVoltage;
		double current;
		int availibleChannels;
		double cellV[10];
		double internalTemp;
		double externalTemp;
		int charged_mAh;
		int checksum;

		const char* getStateDescription(){
			if(state == 1) return "Charging";
			if(state == 2) return "Discharging";
			if(state == 3) return "Monitoring";
			if(state == 4) return "Waiting";
			if(state == 5) return "Motor Test";
			if(state == 6) return "Finished";
			if(state == 7) return "Error";
			if(state == 8) return "lixx tickeling";
			if(state == 9) return "Nixx tickeling";
			if(state == 10) return "foam cutting";
			if(state == 11) return "information";
			if(state == 12) return "ex-discharging";
			return "Unknown";
		}
};


/**
  * Driver for the iCharger Battery Charger
  */
class Driver: public IODriver 
{

public:

	Driver();
	~Driver();
	int getReadFD();
	
	/**
	  * \brief Initialization
	  * This Function initializatze the Driver and trys to open the port
	  * Optional Logging can be activated, for logging details see sourcecode for now
	  * \param port Unix portname of the device
	  * \param doLogging Activate Textual Logging (e.g. used for gnuplot)
	  * \return true if port could opened sucsessfully
	  */
	bool init(std::string const &port,bool const doLogging=false);

	/**
	  * \brief Getting the Data
	  * This Function should be called periodicly to acquire the Data, tha Data will returned throught the parameter delta
	  * \param delta The Readed Values
	  * \return true if data are sucsessfully readed
	  */
	bool getData(Data &delta);

private:
	static const int MAX_PACKET_SIZE = 256;
	virtual int extractPacket(uint8_t const* buffer, size_t buffer_size) const;
	bool doLogging;
	int loggerFD;

};

};
#endif
