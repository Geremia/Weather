#include <QMouseEvent>
#include <QAction>
#include <QSettings>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSettings sts;
    restoreGeometry(sts.value("MainGeometry").toByteArray());
    restoreState(sts.value("MainState").toByteArray());
    ui->woeidEdit->setText(sts.value("ID").toString());

    w = new Weather(this);

    connect(ui->okButton, &QPushButton::clicked, this, &MainWindow::onOkButtonClicked);
    connect(w, &Weather::updateFinished, this, &MainWindow::onWeatherUpdateFinished);
    connect(w, &Weather::imageDownloaded, this, &MainWindow::onAttrImgDownloaded);
    w->getAttrImg();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onOkButtonClicked()
{
    w->updateData(ui->woeidEdit->text());
}

void MainWindow::onAttrImgDownloaded(const QImage &img)
{
    ui->attrLabel->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::onWeatherUpdateFinished(const QString &location, const QString &temp, const QString &wind)
{
    ui->locationLabel->setText(location);
    ui->tempLabel->setText(temp);
    ui->windLabel->setText(wind);
}

void MainWindow::closeEvent(QCloseEvent *e) //save prefs
{
    QSettings sts;
    sts.setValue("MainGeometry", saveGeometry());
    sts.setValue("MainState", saveState());
    sts.setValue("ID",ui->woeidEdit->text());
    e->accept();
}
