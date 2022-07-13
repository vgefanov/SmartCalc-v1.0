#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "./smartcalc1.h"
#ifdef __cpluplus
}
#endif

#include <QMainWindow>
#include <QMessageBox>
#include <credit.h>

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow:public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QString show_label();
    double xBegin, xEnd, yBegin, yEnd, h, X;
    int N;
    QVector<double> x, y;
    QWidget* graphWindow;
    Credit *credit;

private slots:
    void digits_numbers();
    void operations();
    void trig_log_operations();
    void on_pushButton_dot_clicked();
    void on_pushButton_clear_clicked();
    void on_pushButton_equal_clicked();
    void on_pushButton_backspace_clicked();
    void on_pushButton_graf_clicked();
    void on_radioButton_credit_clicked();
    void on_radioButton_deposit_clicked();
};
#endif // MAINWINDOW_H
