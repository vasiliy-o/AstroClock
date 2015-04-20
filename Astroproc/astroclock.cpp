#include "astroclock.h"
#include "chart.h"
#include <QDialog>

AstroProc::AstroProc(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.widget, SIGNAL(data_ready(const std::list<DataElem>&)), SLOT(save_data(const std::list<DataElem>&)));
		
	QPalette Pal(palette());
	Pal.setColor(QPalette::Background, QColor(240, 240, 240));
	setPalette(Pal);
	ui.tableWidget->setAutoFillBackground(true);
	ui.tableWidget->setPalette(Pal);	
}

AstroProc::~AstroProc()
{
	
}

void AstroProc::save_data(const std::list<DataElem>& data)
{
	chart_data = data;

	ui.tableWidget->setColumnCount(3);
	ui.tableWidget->setRowCount(data.size());

	QHeaderView *verticalHeader = ui.tableWidget->verticalHeader();
	verticalHeader->sectionResizeMode(QHeaderView::Fixed);
	verticalHeader->setDefaultSectionSize(30);
	verticalHeader->setDefaultAlignment(Qt::AlignCenter);

	QPalette p = ui.tableWidget->palette();
	p.setColor(QPalette::Base, QColor(240, 240, 240));
	ui.tableWidget->setPalette(p);
	ui.tableWidget->show();

	int row = 0;

	for (auto a : data)
	{
		QTableWidgetItem * item = new QTableWidgetItem;
		QTableWidgetItem * item_1 = new QTableWidgetItem(QString::number(a.deg, 'g', 4));		
		QTableWidgetItem * item_2 = new QTableWidgetItem;
		
		item->setData(Qt::DecorationRole, a.planetpix);

		item_1->setTextAlignment(Qt::AlignCenter);
		QFont font = item_1->font();
		font.setBold(true);
		item_1->setFont(font);

		item_2->setData(Qt::DecorationRole, a.signpix);
				
		ui.tableWidget->setItem(row, 0, item);
		ui.tableWidget->setItem(row, 1, item_1);	
		ui.tableWidget->setItem(row++, 2, item_2);
	}
}

void AstroProc::draw_chart()
{

}