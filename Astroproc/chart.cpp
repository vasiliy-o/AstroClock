#include "chart.h"
#include <QPainter>
#include <QSizePolicy>
#include <QTextCodec>
#include <QSvgRenderer>
#include <QDateTime>
#include <QtDebug>
#include <fstream>

//Astro::Ephemeris::SwissEphemeris *ephemeris;

using namespace Astro;

struct deg_level
{
	double degree;
	int level;
};

bool operator<(const deg_level& dl1, const deg_level& dl2)
{
	return dl1.level < dl2.level;
}

Chart::Chart(QWidget *parent)
{
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	
	Astro::Ephemeris::SwissEphemeris se("../astro/swe_files");
	Astro::Ephemeris::ephemeris = &se;

	QPalette Pal(palette());
	Pal.setColor(QPalette::Background, QColor(240, 240, 240));
	setAutoFillBackground(true);
	setPalette(Pal);

	resize(600, 600);
	init();
}

void Chart::init()
{
	sign_pixmaps.resize(12);

	sign_paths.push_back("..\\signs\\Aries.svg");		// 1
	sign_paths.push_back("..\\signs\\Taurus.svg");		// 2
	sign_paths.push_back("..\\signs\\Gemini.svg");		// 3
	sign_paths.push_back("..\\signs\\Cancer.svg");		// 4
	sign_paths.push_back("..\\signs\\Leo.svg");			// 5
	sign_paths.push_back("..\\signs\\Virgo.svg");		// 6
	sign_paths.push_back("..\\signs\\Libra.svg");		// 7
	sign_paths.push_back("..\\signs\\Scorpio.svg");		// 8
	sign_paths.push_back("..\\signs\\Sagittarius.svg"); // 9
	sign_paths.push_back("..\\signs\\Capricorn.svg");	// 10
	sign_paths.push_back("..\\signs\\Aquarius.svg");	// 11
	sign_paths.push_back("..\\signs\\Pisces.svg");		// 12

	planets_paths.resize(static_cast<int>(body::N));
	planets_paths[static_cast<int>(body::sun  )]	= "..\\planets\\Sun.svg";
	planets_paths[static_cast<int>(body::earth)]	= "..\\planets\\Earth.svg";
	planets_paths[static_cast<int>(body::moon )]	= "..\\planets\\Moon.svg";
	planets_paths[static_cast<int>(body::nnode)]	= "..\\planets\\Northnode.svg";
	planets_paths[static_cast<int>(body::snode)]	= "..\\planets\\Southnode.svg";
	planets_paths[static_cast<int>(body::mercury)]	= "..\\planets\\Mercury.svg";
	planets_paths[static_cast<int>(body::venus)]	= "..\\planets\\Venus.svg";
	planets_paths[static_cast<int>(body::mars)]		= "..\\planets\\Mars.svg";
	planets_paths[static_cast<int>(body::jupiter)]	= "..\\planets\\Jupiter.svg";
	planets_paths[static_cast<int>(body::saturn)]	= "..\\planets\\Saturn.svg";
	planets_paths[static_cast<int>(body::uranus)]	= "..\\planets\\Uranus.svg";
	planets_paths[static_cast<int>(body::neptune)]	= "..\\planets\\Neptune.svg";
	planets_paths[static_cast<int>(body::pluto)]	= "..\\planets\\Pluto.svg";

	for (int i = 0; i < Astro::bodies_N; ++i)	
		planets.push_back(static_cast<Astro::body>(i));
}

void Chart::paintEvent(QPaintEvent *)
{
	data_elems.clear();

	QPainter painter(this);

	QPen pen(Qt::black);
	pen.setWidth(1);
	painter.setPen(pen);

	int side = qMin(width(), height());
	painter.translate(width() / 2, height() / 2);
	painter.scale(side / 200.0, side / 200.0);
	painter.setRenderHints(QPainter::Antialiasing);

	draw_signs(painter);
	draw_ellipses(painter);
	draw_planets(painter);

	painter.end();

	emit data_ready(data_elems);
}

void Chart::update_chart(const QString& txt)
{	
	update();
}

void Chart::draw_signs(QPainter& p)
{
	p.save();

	// Нарисовать изображения знаков зодиака
	for (int i = 0; i < 12; ++i)
	{
		p.rotate(-18.);

		QPixmap pixmap(200, 200);
		pixmap.fill(Qt::transparent);

		QPainter painter(&pixmap);		
		painter.translate(200 / 2, 200 / 2);
		painter.rotate(15 + 30 * i);
				
		QSvgRenderer sr(sign_paths[i], this);
		sr.render(&painter, QRectF(QPointF(-50., -50.), QPointF(50, 50)));

		p.drawPixmap(QRect(QPoint(85, 0), QPoint(95, 10)), pixmap);
		
		set_orig_sign_pix(sign_paths[i], &sign_pixmaps[i]);
		
		p.rotate(-12.);
	}

	p.restore();
}

void Chart::draw_ellipses(QPainter& p)
{
	p.save();

	for (int i = 0; i < 12; ++i)
	{
		p.drawLine(85, 0, 97, 0);
		p.rotate(30.);
	}

	p.restore();

	p.drawEllipse(QRect(-97, -97, 194, 194));
	p.drawEllipse(QRect(-85, -85, 170, 170));
}

void Chart::set_orig_planet_pix(const QString& pixmap_path, QPixmap *cur_elem)
{
	QPixmap pixmap(40, 40);
	pixmap.fill(Qt::transparent);

	QSvgRenderer sr(this);
	if (sr.load(pixmap_path))
	{
		QPainter painter(&pixmap);
		sr.render(&painter, QRectF(QPointF(10, 10), QPointF(30, 30)));
		*cur_elem = pixmap;
	}
	else
	{
		qDebug() << "Pixmap load error\n";
	}
}

void Chart::set_orig_sign_pix(const QString& pixmap_path, QPixmap *cur_elem)
{
	QPixmap pixmap(30, 30);
	pixmap.fill(Qt::transparent);

	QSvgRenderer sr(this);
	if (sr.load(pixmap_path))
	{
		QPainter painter(&pixmap);
		sr.render(&painter, QRectF(QPointF(10, 10), QPointF(25, 25)));
		*cur_elem = pixmap;
	}
	else
	{
		qDebug() << "Pixmap load error\n";
	}
}

void Chart::draw_planets(QPainter& p)
{
	if (planets.size() == planets_paths.size())
	{
		vector<deg_level> deg_levels;
		max_level = 0;
		data_elems.clear();

		for (int i = 0; i < planets.size(); ++i)
		{
			p.save();

			QDateTime current = QDateTime::currentDateTime();

			double d = Ephemeris::ephemeris->pos(planets[i],
				Date(current.date().year(), current.date().month(), current.date().day()),
				Time(current.time().hour(), current.time().minute())
			);

			DataElem cur_elem;
			int sign = int(d) / 30;
			cur_elem.deg = d - (sign * 30.);
			
			list<deg_level> close;

			for (auto a : deg_levels)
			{
				if (fabs(d - a.degree) < 5.)
					close.push_back(a);
			}

			deg_level dl;
			dl.degree = d;
			dl.level = 1;

			if (!close.empty())
			{
				// при возможности наложения размещать планету ближе к центру
				close.sort();
				dl = close.back();
				if (dl.level < 4)
					dl.level += 1;
			}

			if (dl.level > max_level)
				max_level = dl.level;

			deg_levels.push_back(dl);

			p.rotate(-d);

			QPixmap pixmap(200, 200);
			pixmap.fill(Qt::transparent);

			QPainter painter(&pixmap);
			painter.translate(200 / 2, 200 / 2);
			painter.rotate(d);

			QSvgRenderer sr(planets_paths[i], this);
			sr.render(&painter, QRectF(QPointF(-50., -50.), QPointF(50, 50)));

			p.drawPixmap(QRect(QPoint(70 - 15 * dl.level, -8),
							   QPoint(70 - 15 * (dl.level - 1), 7)), pixmap);
						
			set_orig_planet_pix(planets_paths[i], &cur_elem.planetpix);
			
			if (sign >= 0 && sign < 12)
				cur_elem.signpix = sign_pixmaps[sign];

			p.restore();

			data_elems.push_back(cur_elem);
		}

		// нарисовать внутреннюю окружность
		max_level += 1;
		p.drawEllipse(QRect(QPoint(-70 + 15 * max_level, -70 + 15 * max_level),
							QPoint( 70 - 15 * max_level,  70 - 15 * max_level)));
	}
}