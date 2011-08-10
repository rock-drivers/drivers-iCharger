#include "iChargerGUI.hpp"
#include "../iCharger.h"
#include "ui_iCharger.h"
#include <QPen>

namespace iCharger{

GUI::GUI(const char *port, QWidget *parent):
	port(port),
	QWidget(parent)
{
	driver = new Driver();
	driver->init(port,true);
	ui = new Ui_iCharger();
	ui->setupUi(this);
	show();
	timer.setInterval(500);
	timer.setSingleShot(false);
	connect(&timer,SIGNAL(timeout()),this,SLOT(timerDone()));
	timer.start();
	currentCurve.setPen(QPen(QColor(255,0,0)));
	baseVoltageCurve.setPen(QPen(QColor(255,0,0)));
	chargedCurve.setPen(QPen(QColor(255,0,0)));
	
	currentCurve.attach(ui->current);
	baseVoltageCurve.attach(ui->voltage_all);
	chargedCurve.attach(ui->charged);

	globalTime=0;
	initialized=false;
	lineColors[0]	= QColor(0,0,128);
	lineColors[1]	= QColor(0,0,255);
	lineColors[2]	= QColor(0,128,0);
	lineColors[3]	= QColor(0,128,128);
	lineColors[4]	= QColor(0,128,255);
	lineColors[5]	= QColor(0,255,0);
	lineColors[6]	= QColor(0,255,128);
	lineColors[7]	= QColor(0,255,255);
	lineColors[8]	= QColor(128,0,0);
	lineColors[9]	= QColor(128,0,128);
}

GUI::~GUI(){
	delete driver;
	delete ui;
}

void GUI::timerDone(){
	globalTime++;
	Data data;
	if(driver->getData(data)){

		if(!initialized){
			ui->cellVoltages->setLayout(new QGridLayout());
			for(int i=0;i<data.availibleChannels;i++){
				QGridLayout *layout = (QGridLayout*) ui->cellVoltages->layout();
				voltageValuesCurve[i].setPen(QPen(lineColors[i]));
				voltageValuesCurve[i].attach(ui->voltage_cell);
				QLabel *label = new QLabel();
				layout->addWidget(label,i/5,(i%5)*2);
				label->setText(QString("Cell V %1 ").arg(i));
				sb[i] = new QDoubleSpinBox();
				layout->addWidget(sb[i],i/5,((i%5)*2)+1);
        		sb[i]->setReadOnly(true);
		        sb[i]->setButtonSymbols(QAbstractSpinBox::NoButtons);
				initialized=true;
			}
		}
		for(int i=0;i<data.availibleChannels;i++){
			voltageValues[i].push_back(data.cellV[i]);
			voltageValuesCurve[i].setRawData(xAxis.data(),voltageValues[i].data(),xAxis.size());
			sb[i]->setValue(data.cellV[i]);
		}
		ui->channel->setValue(data.channel);
		ui->state->setText(QString("%1").arg((char*)data.getStateDescription()));
		ui->timestamp->setValue(data.timestamp);
		ui->inputV->setValue(data.inputVoltage);
		ui->batteryV->setValue(data.baseVoltage);
		ui->current_2->setValue(data.current);

		ui->intTemp->setValue(data.internalTemp);
		ui->battTemp->setValue(data.externalTemp);
		ui->charged_2->setValue(data.charged_mAh);

		xAxis.push_back(globalTime/2.0);
		currentValues.push_back(data.current);
		baseVoltageValues.push_back(data.baseVoltage);
		chargedValues.push_back(data.charged_mAh);
		currentCurve.setRawData(xAxis.data(),currentValues.data(),xAxis.size());
		baseVoltageCurve.setRawData(xAxis.data(),baseVoltageValues.data(),xAxis.size());
		chargedCurve.setRawData(xAxis.data(),chargedValues.data(),xAxis.size());
//
		ui->current->replot();
		ui->voltage_all->replot();
		ui->voltage_cell->replot();
		ui->charged->replot();

	}

}

}
