#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QMainWindow>
#include <QMessageBox>
#include <QTimer>
#include <QVector>
#include <QtMath>

#include "controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:

  int SmartCalc(QString currentText, double variable_x, double *result);

  int CheckingInputData(QString currentText);

  void pushButton_for_func();

  void pushButton_for_operators();

  void on_pushButton_equal_clicked();

  void on_pushButton_AC_clicked();

  void on_pushButton_backspace_clicked();

  void on_pushButton_LEFT_clicked();

  void on_pushButton_RIGHT_clicked();

  void on_pushButton_plotGraph_clicked();

  void TimerSlot();

  void on_pushButton_CreditCalc_clicked();

 private:
  Ui::MainWindow *ui;
  s21::Controller controller_;

  // для графика:
  double xMin, xMax, h, X, yMin, yMax;
  int N;
  QVector<double> x, y;
  QTimer *timer;
  int time;
};
#endif  // MAINWINDOW_H
