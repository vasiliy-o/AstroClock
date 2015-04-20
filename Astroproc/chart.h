#ifndef CHART_H
#define CHART_H
#include <QtWidgets/QWidget>
#include <QString>
#include "../astro/astro.h"
#include <vector>
#include <list>

struct DataElem {

	QPixmap signpix;
	QPixmap planetpix;
	double deg;
};

class Chart : public QWidget
{
	Q_OBJECT

public:
	Chart(QWidget *parent = NULL);
	void update_chart(const QString& txt);

signals:
	void data_ready(const std::list<DataElem>& data_elems);

protected:
	virtual void paintEvent(QPaintEvent *);
		
private:	
	void init();
	void draw_planet(Astro::body b, QPainter& p, const QRect& r);
	void draw_signs(QPainter& p);
	void draw_planets(QPainter& p);
	void draw_ellipses(QPainter& p);
	void draw_houses(QPainter& p);
	
	void set_orig_planet_pix(const QString& pixmap_path, QPixmap *cur_elem);
	void set_orig_sign_pix(const QString& pixmap_path, QPixmap *cur_elem);

	std::vector<double> start_degs;
	std::vector<Astro::body> planets;
	std::vector<QString> planet_names;
	std::vector<QString> planets_paths;
	std::vector<QString> sign_names;
	std::vector<QString> sign_paths;
	std::vector<QPixmap> sign_pixmaps;	

	std::list<DataElem> data_elems;

	int max_level;
};

#endif // CHART_H
