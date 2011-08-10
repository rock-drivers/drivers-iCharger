#ifndef _ICHARGERGUI_H_
#define _ICHARGERGUI_H_

#include <QWidget>
#include <QTimer>
#include <qwt_plot_curve.h>
#include <inttypes.h>
#include <QDoubleSpinBox>

class Ui_iCharger;


namespace iCharger{

class Driver;

class GUI : public QWidget{
	Q_OBJECT

public:
	/**
	  * \brief GUI Interface for iCharger do the whole handling of the device and data acquisition
	  * This Function opens the port and initializatioes an thread for data reading
	  * \param port port of the device
	  * \param partent Parent Widget, 0 otherwise (qt-default)
	  */
	GUI(const char *port,QWidget *parent=0);
	~GUI();

private:
	const char *port;
	Driver *driver;
	Ui_iCharger *ui;
	std::vector<double> currentValues;
	std::vector<double> voltageValues[10];
	std::vector<double> baseVoltageValues;
	std::vector<double> chargedValues;
	std::vector<double>    xAxis;
	QTimer timer;
	QwtPlotCurve currentCurve,baseVoltageCurve,voltageValuesCurve[10],chargedCurve;
	QDoubleSpinBox *sb[10];
	uint32_t globalTime;
	bool initialized;
	QColor lineColors[10];

public slots:
	void timerDone();

};



};



#endif
