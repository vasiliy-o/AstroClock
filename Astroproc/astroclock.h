#ifndef ASTROPROC_H
#define ASTROPROC_H

#include <QtWidgets/QMainWindow>
#include <list>
#include "ui_astroproc.h"

class AstroProc : public QMainWindow
{
	Q_OBJECT

public:
	AstroProc(QWidget *parent = 0);
	~AstroProc();

public slots:
	void save_data(const std::list<DataElem>& data);


private:
	void draw_chart();
	
	Ui::AstroProcClass ui;
	std::list<DataElem> chart_data;
};

#endif // ASTROPROC_H
