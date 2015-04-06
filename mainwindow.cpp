#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_batdau_clicked()
{

    ui->widget->resetP();
    ui->widget->repaint();
    ui->widget->mode=1;

}

void MainWindow::on_danh_clicked()
{   
    ui->widget->hddanh = true;
}


void MainWindow::on_thoat_clicked()
{

    ui->widget->mode=3;
}
