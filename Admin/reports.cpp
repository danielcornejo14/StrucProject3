#include "reports.h"
#include "ui_reports.h"

Reports::Reports(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Reports)
{
    ui->setupUi(this);
}

Reports::~Reports()
{
    delete ui;
}

void Reports::on_reportsBack_clicked()
{
    this->close();
}
