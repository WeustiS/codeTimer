#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>
#include <QDateTime>
#include <QRandomGenerator>
#include <chrono>
#include <thread>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),this, SLOT(mySlot()));
    timer->start(1000);
     ui->label_alarm->setText("Freedom");
     ui->label_cd->setText("--");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mySlot()
{
    if(hour.toString("hhmm").toInt()<100){
        ui->label_cd->setText(hour.toString("mm"));
    }
    else{
        ui->label_alarm->setText("Freedom");
        ui->label_cd->setText("--");

        time = QTime::fromString("00", "hh");
        hour.stop();
    }
    QTime hour = QTime::fromString("00", "hh");
    hour.stop();
    QTime time = QTime::currentTime();
    ui->label_dt->setText(time.toString("hh:mm AP"));

    QDateTime date = QDateTime::currentDateTime();

    QRandomGenerator rng(date.toString("ddMMyy").toInt());
    double msAfter = rng.generateDouble() * 14400000;

    QTime fiveoClock = QTime::fromString("17", "hh");
    QTime alarmTime = fiveoClock.addMSecs(msAfter);

    if(time.toString("hh:mm AP") == alarmTime.toString("hh:mm AP")){
        ui->label_alarm->setText("It's time to code");
        hour.start();
        ui->label_cd->setText(hour.toString("mm"));
    }
}


