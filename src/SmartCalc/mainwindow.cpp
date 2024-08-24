#include "mainwindow.h"

#include <iostream>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), controller_() {
  ui->setupUi(this);

  connect(ui->pushButton_number_0, SIGNAL(clicked()), this,
          SLOT(pushButton_for_func()));
  connect(ui->pushButton_number_1, SIGNAL(clicked()), this,
          SLOT(pushButton_for_func()));
  connect(ui->pushButton_number_2, SIGNAL(clicked()), this,
          SLOT(pushButton_for_func()));
  connect(ui->pushButton_number_3, SIGNAL(clicked()), this,
          SLOT(pushButton_for_func()));
  connect(ui->pushButton_number_4, SIGNAL(clicked()), this,
          SLOT(pushButton_for_func()));
  connect(ui->pushButton_number_5, SIGNAL(clicked()), this,
          SLOT(pushButton_for_func()));
  connect(ui->pushButton_number_6, SIGNAL(clicked()), this,
          SLOT(pushButton_for_func()));
  connect(ui->pushButton_number_7, SIGNAL(clicked()), this,
          SLOT(pushButton_for_func()));
  connect(ui->pushButton_number_8, SIGNAL(clicked()), this,
          SLOT(pushButton_for_func()));
  connect(ui->pushButton_number_9, SIGNAL(clicked()), this,
          SLOT(pushButton_for_func()));
  connect(ui->pushButton_variable_X, SIGNAL(clicked()), this,
          SLOT(pushButton_for_func()));
  connect(ui->pushButton_OPN, SIGNAL(clicked()), this,
          SLOT(pushButton_for_func()));
  connect(ui->pushButton_CLS, SIGNAL(clicked()), this,
          SLOT(pushButton_for_func()));
  connect(ui->pushButton_point, SIGNAL(clicked()), this,
          SLOT(pushButton_for_operators()));
  connect(ui->pushButton_COS, SIGNAL(clicked()), this,
          SLOT(pushButton_for_func()));
  connect(ui->pushButton_SIN, SIGNAL(clicked()), this,
          SLOT(pushButton_for_func()));
  connect(ui->pushButton_TAN, SIGNAL(clicked()), this,
          SLOT(pushButton_for_func()));
  connect(ui->pushButton_ACOS, SIGNAL(clicked()), this,
          SLOT(pushButton_for_func()));
  connect(ui->pushButton_ASIN, SIGNAL(clicked()), this,
          SLOT(pushButton_for_func()));
  connect(ui->pushButton_ATAN, SIGNAL(clicked()), this,
          SLOT(pushButton_for_func()));
  connect(ui->pushButton_LOG, SIGNAL(clicked()), this,
          SLOT(pushButton_for_func()));
  connect(ui->pushButton_LN, SIGNAL(clicked()), this,
          SLOT(pushButton_for_func()));
  connect(ui->pushButton_SQRT, SIGNAL(clicked()), this,
          SLOT(pushButton_for_func()));
  connect(ui->pushButton_DEG, SIGNAL(clicked()), this,
          SLOT(pushButton_for_operators()));
  connect(ui->pushButton_MUL, SIGNAL(clicked()), this,
          SLOT(pushButton_for_operators()));
  connect(ui->pushButton_DEV, SIGNAL(clicked()), this,
          SLOT(pushButton_for_operators()));
  connect(ui->pushButton_SUM, SIGNAL(clicked()), this,
          SLOT(pushButton_for_operators()));
  connect(ui->pushButton_SUB, SIGNAL(clicked()), this,
          SLOT(pushButton_for_operators()));
  connect(ui->pushButton_MOD, SIGNAL(clicked()), this,
          SLOT(pushButton_for_operators()));

  ui->widget->xAxis->setLabel("x");
  ui->widget->yAxis->setLabel("y");
  ui->widget->xAxis->setRange(-10, 10);
  ui->widget->yAxis->setRange(-10, 10);
}

MainWindow::~MainWindow() { delete ui; }

int MainWindow::SmartCalc(QString currentText, double variable_x,
                          double *result) {
  int error = 0;
  try {
  *result = controller_.Calc(currentText.toStdString(), variable_x);
  } catch (const std::exception &e) {
      error = 1;
  }
  return error;
}

int MainWindow::CheckingInputData(QString currentText) {
  int error = 0;
  if (currentText.length() == 0) {
    ui->statusbar->showMessage(
        "В темном месте мы находим себя, и лишь знания освещают наш путь!");
    error = 1;
  } else if (currentText.length() > 255) {
    ui->lineEdit_input->setText("ERROR");
    ui->statusbar->showMessage("Допускается ввод до 255 символов");
    error = 1;
  }
  return error;
}

void MainWindow::pushButton_for_func() {
  QString currentText = ui->lineEdit_input->text();
  QPushButton *button = (QPushButton *)sender();
  QString buttonText = button->text();
  if (currentText == "ERROR" || currentText == "NAN" || currentText == "INF" ||
      currentText == "0") {
    ui->lineEdit_input->setText(buttonText);
  } else {
    if (buttonText.length() >= 2 && buttonText != "mod") {
      buttonText = buttonText + "(";
    }
    int cursorPosition = ui->lineEdit_input->cursorPosition();
    currentText.insert(cursorPosition, buttonText);
    ui->lineEdit_input->setText(currentText);
  }
}

void MainWindow::pushButton_for_operators() {
  QString currentText = ui->lineEdit_input->text();
  QPushButton *button = (QPushButton *)sender();
  QString buttonText = button->text();
  if (currentText == "ERROR" || currentText == "NAN" || currentText == "INF" ||
      currentText == "") {
    ui->lineEdit_input->setText("");
    if (buttonText == "-") {
      ui->lineEdit_input->setText(buttonText);
    }
  } else {
    int cursorPosition = ui->lineEdit_input->cursorPosition();
    currentText.insert(cursorPosition, buttonText);
    ui->lineEdit_input->setText(currentText);
  }
}

void MainWindow::on_pushButton_equal_clicked() {
  QString currentText = ui->lineEdit_input->text();
  if (CheckingInputData(currentText)) {
    return;
  }

  double result = 0;
  double variable_x = ui->doubleSpinBox_variable_x->value();
  int error = SmartCalc(currentText, variable_x, &result);

  if (error) {
    // ui->lineEdit_input->setText("ERROR");
    ui->label->setText("ERROR");
    ui->statusbar->showMessage(
        "Внесите исправление! \"Терпение необходимо во всем, что вы "
        "делаете!\"(c)Магистр Йода");  //статусбар
  } else if (isnan(result)) {
    // ui->lineEdit_input->setText("NAN");
    ui->label->setText("NAN");
    ui->statusbar->showMessage(
        "Результат не определен. \"Хватит предсказывать последствия своих "
        "действий!\"(c)Магистр Йода");  //статусбар
  } else if (isinf(result)) {
    // ui->lineEdit_input->setText("INF");
    ui->label->setText("INF");
    ui->statusbar->showMessage(
        "Деление на ноль невозможно! \"Сконцентрируйся и оставайся "
        "внимательным!\"(c)Магистр Йода");  //статусбар
  } else {
    QString resultString = QString::number(result, 'g', 15);
    ui->label->setText(currentText + " =");
    ui->lineEdit_input->setText(resultString);
    ui->statusbar->showMessage("Верно!!!");  //статусбар
  }
}

void MainWindow::on_pushButton_AC_clicked() { ui->lineEdit_input->clear(); }

void MainWindow::on_pushButton_backspace_clicked() {
  QString currentText = ui->lineEdit_input->text();
  currentText.remove(currentText.size() - 1, 1);
  ui->lineEdit_input->setText(currentText);
}

void MainWindow::on_pushButton_LEFT_clicked() {
  int currentCursorPosition = ui->lineEdit_input->cursorPosition();
  if (currentCursorPosition > 0) {
    ui->lineEdit_input->setCursorPosition(currentCursorPosition - 1);
  }
}

void MainWindow::on_pushButton_RIGHT_clicked() {
  int currentCursorPosition = ui->lineEdit_input->cursorPosition();
  ui->lineEdit_input->setCursorPosition(currentCursorPosition + 1);
}

void MainWindow::on_pushButton_plotGraph_clicked() {
  QString currentText = ui->lineEdit_input->text();
  if (CheckingInputData(currentText)) {
    return;
  }

  xMin = ui->doubleSpinBox_xMin->value();
  xMax = ui->doubleSpinBox_xMax->value();
  yMin = ui->doubleSpinBox_yMin->value();
  yMax = ui->doubleSpinBox_yMax->value();

  N = 300;
  h = (xMax - xMin) / (N - 2);

  if (ui->radioButton_renderingGraph->isChecked()) {
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(TimerSlot()));
    timer->start(20);
    X = xMin;
  } else {
    for (X = xMin; X <= xMax; X += h) {
      x.push_back(X);
      double result = 0;
      int error = SmartCalc(currentText, X, &result);
      if (result > yMax || result < yMin || isnan(result) || isinf(result) ||
          error) {
        y.push_back(qQNaN());
      } else {
        y.push_back(result);
      }
    }
  }

  // create graph and assign data to it:
  ui->widget->clearGraphs();
  ui->widget->addGraph();
  ui->widget->graph(0)->addData(x, y);  // or setData(x, y) ?
  ui->widget->replot();
  x.clear();
  y.clear();

  // set axes ranges, so we see all data:
  ui->widget->yAxis->setLabel("y(x) = " + currentText);
  ui->widget->xAxis->setRange(xMin, xMax);
  ui->widget->yAxis->setRange(yMin, yMax);
}

void MainWindow::TimerSlot() {
  QString currentText = ui->lineEdit_input->text();
  if (time <= 20 * N) {
    if (X <= xMax) {
      x.push_back(X);
      double result = 0;
      int error = SmartCalc(currentText, X, &result);
      if (result > yMax || result < yMin || isnan(result) || isinf(result) ||
          error) {
        y.push_back(qQNaN());
      } else {
        y.push_back(result);
      }
      X += h;
    }
    time += 20;
  } else {
    time = 0;
    timer->stop();
  }
  ui->widget->addGraph();
  ui->widget->graph(0)->addData(x, y);
  ui->widget->replot();
  x.clear();
  y.clear();
}

void MainWindow::on_pushButton_CreditCalc_clicked() {
  double sumCredit = ui->doubleSpinBox_sumCredit->value();
  double pct = ui->doubleSpinBox_pct->value();
  int months = ui->spinBox_months->value();
  controller_.SetDataModelCredit(sumCredit, pct, months);
  if (ui->radioButton_Annuity->isChecked()) {
    double pmt = controller_.AnnuityPMT();  //Аннуитетный платеж
    double overpayment = controller_.AnnuityOverpayment();  //Начисленные проценты
    double dio = controller_.AnnuityTotalCredit();  //Долг + проценты
    QString pmtString = QString::number(pmt, 'f', 2);
    QString overpaymentString = QString::number(overpayment, 'f', 2);
    QString dioString = QString::number(dio, 'f', 2);
    ui->label_10->setText("Ежемесячный платеж*: " + pmtString + " руб");
    ui->label_11->setText("Долг + проценты: " + dioString + " руб");
    ui->label_12->setText("Начисленные проценты: " + overpaymentString + " руб");
    ui->label_14->setText("");
    ui->statusbar->showMessage("*Аннуитетный платеж");
  } else if (ui->radioButton_Diff->isChecked()) {
    double overpayment = controller_.DifferentialOverpayment();  //Начисленные проценты
    double dio = controller_.DifferentialTotalCredit();  //Долг + проценты
    QString dioString = QString::number(dio, 'f', 2);
    QString overpaymentString = QString::number(overpayment, 'f', 2);
    QString diffPayString_1 = QString::number(controller_.DifferentialMaxPMT(), 'f', 2);
    QString diffPayString_n = QString::number(controller_.DifferentialMinPMT(), 'f', 2);
    ui->label_10->setText("Дифференциальный платеж*  = " + diffPayString_1 +
                          " руб");
    ui->label_11->setText("Долг + проценты: " + dioString + " руб");
    ui->label_12->setText("Начисленные проценты: " + overpaymentString + " руб");
    ui->label_14->setText("Дифференциальный платеж** = " + diffPayString_n +
                          " руб");
    ui->statusbar->showMessage(
        "*максимальный и **минимальные месячные платежи!");
  } else {
    ui->statusbar->showMessage("Необходимо выбрать тип платежа!");
  }
}
