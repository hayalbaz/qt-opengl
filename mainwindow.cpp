#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "dvdplayerlogo.h"
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    auto *player = new DVDPlayerLogo;
    ui->openGLWidget->addItem(player);
    connect(ui->openGLWidget, &MyOpenGLWidget::advance, player, &DVDPlayerLogo::onAdvance);
}

