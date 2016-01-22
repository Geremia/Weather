#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "weather.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Weather *w;

private slots:
    void onOkButtonClicked();
    void onAttrImgDownloaded(const QImage &);
    void onWeatherUpdateFinished(const QString &location, const QString &temp, const QString &wind);

protected:
    void closeEvent(QCloseEvent *);

};

#endif // MAINWINDOW_H
