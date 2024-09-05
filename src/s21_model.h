#ifndef S21_MODEL_H_
#define S21_MODEL_H_

#include <cmath>
#include <iostream>
#include <list>
#include <regex>
#include <sstream>
#include <stack>
#include <string>

namespace s21 {

class Model {
 public:
  /// @brief Конструктор по умолчанию
  Model();

  /// @brief Конструктор
  /// @param infix_str инфиксная строка
  /// @param variable_x переменная x
  Model(std::string infix_str, double variable_x);
  ~Model();

  enum STATUS { OK, ERROR };
  double Calc();
  double Calc(std::string infix_str, double variable_x);
  int Math(int type, double *result);
  void SortingStation();
  int ParserToken(const std::string &str_token);
  void DeadSpace();
  void ToLowerCase();
  void ClosedParenthesis();
  void ListTokenPushFront(int type, double value);
  void ListTokenPushBack(int type, double value);
  void StackTempPush(int type, double value);
  void StackMove();
  int StackRead(int *type, double *value);
  int StackPop(int *type, double *value);
  void Operators(int type_01);
  int Priority(int type);
  void StackTempRemove();
  void ListTokenRemove();
  int ListTokenPopBack(int *type, double *value);

  // Сеттеры
  void SetResult(double result);
  void SetInfixStr(std::string str);
  void SetVariableX(double variable_x);

  // Геттеры
  std::string GetInfixStr();
  double GetResult();
  double GetVariableX();

 private:
  std::string infix_str_;
  double variable_x_;
  double result_;
  std::list<int> list_token_type_;
  std::list<double> list_token_value_;
  std::stack<int> stack_temp_type_;
  std::stack<double> stack_temp_value_;
  const double pi_ = 3.14159265358979323846;
};

class ModelCredit {
 public:
  ModelCredit();

  /// @brief Конструктор по умолчанию
  /// @param sum_credit сумма кредита
  /// @param pct Процентная ставка, %
  /// @param months Срок кредита в месяцах
  ModelCredit(double sum_credit, double pct, int months);
  ~ModelCredit();
  void AnnuityRatio();  // коэффициент аннуитета
  double AnnuityPMT();  // Ежемесячный платеж
  double AnnuityOverpayment();  // Начисленные проценты (переплата)
  double AnnuityTotalCredit();  // Долг + проценты
  double DifferentialMaxPMT();  // Максимальный ежемесячный платеж
  double DifferentialMinPMT();  // Минимальный ежемесячный платеж
  double DifferentialOverpayment();  // Начисленные проценты (переплата)
  double DifferentialTotalCredit();  // Долг + проценты
  double DifferentialPrincipalPMT();  // Платеж по основному долгу

  // Сеттеры
  void SetSumCredit(double sum_credit);
  void SetPCT(double pct);
  void SetMonths(int months);

  // Геттеры
  double GetSumCredit();
  double GetPCT();
  int SetMonths();

 private:
  double sum_credit_;     // сумма кредита
  double pct_;            // процентная ставка
  int months_;            // срок в месяцах
  double annuity_ratio_;  // коэффициент аннуитета
};

typedef enum {
  NUM,
  VAR,
  OPN,
  CLS,
  DEG,
  MUL,
  DIV,
  MOD,
  SUM,
  SUB,
  UPLS,
  UMIN,
  ACOS,
  ASIN,
  ATAN,
  COS,
  SIN,
  TAN,
  SQRT,
  LN,
  LOG
} DataType;

}  // namespace s21

#endif  // SRC_S21_MODEL_H_