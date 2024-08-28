#include "s21_model.h"

s21::Model::Model() : infix_str_(""), variable_x_(0), result_(0) {}

s21::Model::Model(std::string infix_str, double variable_x)
    : infix_str_(infix_str), variable_x_(variable_x) {}

s21::Model::~Model() {}

double s21::Model::Calc() {
  StackTempRemove();
  ListTokenRemove();
  int error = 0;
  SortingStation();
  double result = -1;
  int type = -1;
  while (!list_token_type_.empty() && !error) {
    error = ListTokenPopBack(&type, &result);
    if (type == NUM) {
      StackTempPush(NUM, result);
    } else {
      error = Math(type, &result);
    }
  }
  double result_y = 0;
  if (!stack_temp_type_.empty() && !error) {
    error = StackPop(&type, &result_y);
    SetResult(result_y);
  }
  if (error == ERROR) {
    StackTempRemove();
    ListTokenRemove();
    SetResult(0);
    throw std::invalid_argument("Некорректный формат ввода");
  }
  return result_y;
}

double s21::Model::Calc(std::string infix_str, double variable_x) {
  infix_str_ = infix_str;
  variable_x_ = variable_x;
  return Calc();
}

int s21::Model::Math(int type, double *result) {
  int error = OK;
  if (stack_temp_type_.size()) {
    int type_a = -1;
    double number_a = -1, number_b = -1;
    StackPop(&type_a, &number_a);
    if (type <= SUB) {
      error = StackPop(&type_a, &number_b);
    }
    if (type == DEG) {
      *result = pow(number_b, number_a);
    } else if (type == MUL) {
      *result = number_a * number_b;
    } else if (type == DIV) {
      *result = number_b / number_a;
    } else if (type == MOD) {
      *result = number_b - floor(number_b / number_a) * number_a;
    } else if (type == SUM) {
      *result = number_a + number_b;
    } else if (type == SUB) {
      *result = number_b - number_a;
    } else if (type == UPLS) {
      *result = number_a;
    } else if (type == UMIN) {
      *result = -number_a;
    } else if (type == ACOS) {
      *result = acos(number_a);
    } else if (type == ASIN) {
      *result = asin(number_a);
    } else if (type == ATAN) {
      *result = atan(number_a);
    } else if (type == COS) {
      *result = cos(number_a);
    } else if (type == SIN) {
      *result = sin(number_a);
    } else if (type == TAN) {
      *result = tan(number_a);
    } else if (type == SQRT) {
      *result = sqrt(number_a);
    } else if (type == LN) {
      *result = log(number_a);
    } else if (type == LOG) {
      *result = log10(number_a);
    } else {
      error = ERROR;  // LCOV_EXCL_LINE
    }
    if (error == OK) {
      StackTempPush(NUM, *result);
    }
  }
  return error;
}

void s21::Model::SortingStation() {
  DeadSpace();
  int error = OK;
  bool unary_sign = true;
  bool x_after_numbers = false;
  while (infix_str_.length()) {
    if (ParserToken("(")) {
      StackTempPush(OPN, 0);
      error++;
      unary_sign = true;
      x_after_numbers = false;
    } else if (ParserToken(")")) {
      ClosedParenthesis();
      error--;
      unary_sign = false;
      x_after_numbers = false;
    } else if (ParserToken("^")) {
      Operators(DEG);
      unary_sign = true;
      x_after_numbers = false;
    } else if (ParserToken("*")) {
      Operators(MUL);
      unary_sign = true;
      x_after_numbers = false;
    } else if (ParserToken("/")) {
      Operators(DIV);
      unary_sign = true;
      x_after_numbers = false;
    } else if (ParserToken("+")) {
      if (unary_sign) {
        Operators(UPLS);
      } else {
        Operators(SUM);
        unary_sign = true;
      }
      x_after_numbers = false;
    } else if (ParserToken("-")) {
      if (unary_sign) {
        Operators(UMIN);
        unary_sign = false;
      } else {
        Operators(SUB);
      }
      x_after_numbers = false;
    } else if (ParserToken("mod")) {
      Operators(MOD);
      unary_sign = true;
      x_after_numbers = false;
    } else if (ParserToken("x")) {
      if (x_after_numbers) {
        Operators(MUL);
        unary_sign = true;
        x_after_numbers = false;
      }
      ListTokenPushFront(NUM, variable_x_);
      unary_sign = false;
    } else if (ParserToken("pi")) {
      ListTokenPushFront(NUM, S21_M_PI);
      unary_sign = false;
      x_after_numbers = false;
    } else if (ParserToken("asin")) {
      StackTempPush(ASIN, 0);
      unary_sign = true;
      x_after_numbers = false;
    } else if (ParserToken("acos")) {
      StackTempPush(ACOS, 0);
      unary_sign = true;
      x_after_numbers = false;
    } else if (ParserToken("atan")) {
      StackTempPush(ATAN, 0);
      unary_sign = true;
      x_after_numbers = false;
    } else if (ParserToken("sin")) {
      StackTempPush(SIN, 0);
      unary_sign = true;
      x_after_numbers = false;
    } else if (ParserToken("cos")) {
      StackTempPush(COS, 0);
      unary_sign = true;
      x_after_numbers = false;
    } else if (ParserToken("tan")) {
      StackTempPush(TAN, 0);
      unary_sign = true;
      x_after_numbers = false;
    } else if (ParserToken("sqrt")) {
      StackTempPush(SQRT, 0);
      unary_sign = true;
      x_after_numbers = false;
    } else if (ParserToken("ln")) {
      StackTempPush(LN, 0);
      unary_sign = true;
      x_after_numbers = false;
    } else if (ParserToken("log")) {
      StackTempPush(LOG, 0);
      unary_sign = true;
      x_after_numbers = false;
    } else {
      std::string str = GetInfixStr();
      std::regex re("[-+]?[0-9]*\\.?[0-9]+([eE][-+]?[0-9]+)?");
      std::smatch match;
      if (std::regex_search(str, match, re)) {
        std::string str_num = match.str();
        double dbl_num = std::stod(str_num);
        if (ParserToken(str_num)) {
          ListTokenPushFront(NUM, dbl_num);
          unary_sign = false;
          x_after_numbers = true;
        } else {
          error = ERROR;
          break;
        }
      } else {
        error = ERROR;
        break;
      }
    }
  }
  if (error != OK) {
    error = ERROR;
    StackTempRemove();
    throw std::invalid_argument("Некорректный формат ввода");
  }
  while (error == OK && !stack_temp_type_.empty()) {
    StackMove();
  }
}

int s21::Model::ParserToken(const std::string &str_token) {
  int control = 1;
  std::size_t n = infix_str_.size();
  std::size_t k = str_token.size();

  if (infix_str_.compare(0, k, str_token) == 0 && n >= k) {
    infix_str_.erase(0, k);
  } else {
    control = 0;
  }
  return control;
}

void s21::Model::DeadSpace() {
  size_t n = infix_str_.length();
  size_t k = 0;

  for (size_t i = 0; i < n; i++) {
    if (infix_str_[i] != ' ') {
      infix_str_[k] = infix_str_[i];
      k++;
    }
  }

  infix_str_.resize(k);  // Пересчитать длину строки
  infix_str_[k] = '\0';  // Установить завершающий нуль-символ в конце строки
  ToLowerCase();
}

void s21::Model::ToLowerCase() {
  std::string result = infix_str_;  // Копируем строку
  std::transform(result.begin(), result.end(), result.begin(),
                 [](unsigned char c) { return std::tolower(c); });
  infix_str_ = result;
}

void s21::Model::ClosedParenthesis() {
  int error = 0;
  if (!stack_temp_type_.empty()) {
    int type_02 = 0;
    double result_02 = 0;
    error = StackRead(&type_02, &result_02);
    while (error == 0 && type_02 != OPN) {
      StackMove();
      error = StackRead(&type_02, &result_02);
    }
    if (error == 0 && type_02 == OPN) {
      error = StackPop(&type_02, &result_02);
    }
    error = StackRead(&type_02, &result_02);
    if (error == 0 && type_02 > SUB) {
      StackMove();
    }
  }
}

void s21::Model::ListTokenPushFront(int type, double value) {
  list_token_type_.push_front(type);
  list_token_value_.push_front(value);
}

void s21::Model::StackTempPush(int type, double value) {
  stack_temp_type_.push(type);
  stack_temp_value_.push(value);
}

void s21::Model::StackMove() {
  list_token_type_.push_front(stack_temp_type_.top());
  list_token_value_.push_front(stack_temp_value_.top());
  stack_temp_type_.pop();
  stack_temp_value_.pop();
}

int s21::Model::StackRead(int *type, double *value) {
  if (stack_temp_type_.empty() || stack_temp_value_.empty()) {
    return 1;
  }
  *type = stack_temp_type_.top();
  *value = stack_temp_value_.top();
  return 0;
}

int s21::Model::StackPop(int *type, double *value) {
  if (stack_temp_type_.empty() || stack_temp_value_.empty()) {
    return 1;
  }
  *type = stack_temp_type_.top();
  *value = stack_temp_value_.top();
  stack_temp_type_.pop();
  stack_temp_value_.pop();
  return 0;
}

void s21::Model::Operators(int type_01) {
  int priority_01 = Priority(type_01);  // приоритет лексемы-оператор(01);
  int priority_02 = 0;
  int type_02 = -1;
  double result_02 = -1;
  int error = StackRead(&type_02, &result_02);
  // где type_02 - это лексема-оператор(02) на вершине временного стека;
  priority_02 = Priority(type_02);
  while (error == 0 && ((priority_02 > priority_01) ||
                        (priority_02 == priority_01 && type_01 != DEG))) {
    StackMove();
    error = StackRead(&type_02, &result_02);
    priority_02 = Priority(type_02);
  }
  StackTempPush(type_01, 0);
}

int s21::Model::Priority(int type) {
  int control = 0;
  if (type == DEG) {
    control = 3;
  } else if (type == MUL || type == DIV || type == UMIN) {
    control = 2;
  } else if (type == SUM || type == SUB || type == MOD) {
    control = 1;
  }
  return control;
}

void s21::Model::StackTempRemove() {
  while (!stack_temp_type_.empty()) {
    stack_temp_type_.pop();
    stack_temp_value_.pop();
  }
}

void s21::Model::ListTokenRemove() {
  while (!list_token_type_.empty()) {
    list_token_type_.pop_front();
    list_token_value_.pop_front();
  }
}

int s21::Model::ListTokenPopBack(int *type, double *value) {
  if (list_token_type_.empty() || list_token_value_.empty()) {
    return 1;
  }
  *type = list_token_type_.back();
  *value = list_token_value_.back();
  list_token_type_.pop_back();
  list_token_value_.pop_back();
  return 0;
}

// Сеттеры
void s21::Model::SetResult(double result) { result_ = result; }
void s21::Model::SetInfixStr(std::string str) { infix_str_ = str; }
void s21::Model::SetVariableX(double variable_x) { variable_x_ = variable_x; }

// Геттеры
std::string s21::Model::GetInfixStr() { return infix_str_; }
double s21::Model::GetResult() { return result_; }
double s21::Model::GetVariableX() { return variable_x_; }

s21::ModelCredit::ModelCredit()
    : sum_credit_(100000), pct_(15 / 100), months_(12) {}

s21::ModelCredit::ModelCredit(double sum_credit, double pct, int months)
    : sum_credit_(sum_credit), pct_(pct / 100), months_(months) {
  // AnnuityRatio();
}
s21::ModelCredit::~ModelCredit() {}

void s21::ModelCredit::AnnuityRatio() {
  annuity_ratio_ = (pct_ / 12 * pow((1 + pct_ / 12), months_)) /
                   (pow((1 + pct_ / 12), months_) - 1);
}
double s21::ModelCredit::AnnuityPMT() {
  if (months_ < 1) {
    throw std::invalid_argument(
        "Количество месяцев должно быть больше или равен 1!");
  }
  if (pct_ <= 0) {
    throw std::invalid_argument("Процент должен быть больше 0!");
  }
  if (sum_credit_ < 1) {
    throw std::invalid_argument(
        "Сумма кредита должна быть больше или равно 1!");
  }
  AnnuityRatio();
  return round(annuity_ratio_ * sum_credit_ * 100) / 100;
}

double s21::ModelCredit::AnnuityOverpayment() {
  return AnnuityPMT() * months_ - sum_credit_;
}

double s21::ModelCredit::AnnuityTotalCredit() {
  return sum_credit_ + AnnuityOverpayment();
}

double s21::ModelCredit::DifferentialMaxPMT() {
  return round((DifferentialPrincipalPMT() + sum_credit_ * pct_ / 12) * 100) /
         100;
}

double s21::ModelCredit::DifferentialMinPMT() {
  double temp = 0;
  for (int i = 1; i <= months_; i++) {
    temp = (sum_credit_ - DifferentialPrincipalPMT() * (i - 1)) * pct_ / 12;
  }
  return round((DifferentialPrincipalPMT() + temp) * 100) / 100;
}

double s21::ModelCredit::DifferentialOverpayment() {
  if (months_ < 1) {
    throw std::invalid_argument(
        "Количество месяцев должно быть больше или равен 1!");
  }
  if (pct_ <= 0) {
    throw std::invalid_argument("Процент должен быть больше 0!");
  }
  if (sum_credit_ < 1) {
    throw std::invalid_argument(
        "Сумма кредита должна быть больше или равно 1!");
  }
  double temp = 0;
  for (int i = 1; i <= months_; i++) {
    temp += (sum_credit_ - DifferentialPrincipalPMT() * (i - 1)) * pct_ / 12;
  }
  return round(temp * 100) / 100;
}

double s21::ModelCredit::DifferentialTotalCredit() {
  return sum_credit_ + DifferentialOverpayment();
}

double s21::ModelCredit::DifferentialPrincipalPMT() {
  if (months_ < 1) {
    throw std::invalid_argument(
        "Количество месяцев должно быть больше или равен 1!");
  }
  if (pct_ <= 0) {
    throw std::invalid_argument("Процент должен быть больше 0!");
  }
  if (sum_credit_ < 1) {
    throw std::invalid_argument(
        "Сумма кредита должна быть больше или равно 1!");
  }
  return sum_credit_ / months_;
}

// Сеттеры
void s21::ModelCredit::SetSumCredit(double sum_credit) {
  sum_credit_ = sum_credit;
}
void s21::ModelCredit::SetPCT(double pct) { pct_ = pct / 100; }
void s21::ModelCredit::SetMonths(int months) { months_ = months; }

// Геттеры
double s21::ModelCredit::GetSumCredit() { return sum_credit_; }
double s21::ModelCredit::GetPCT() { return pct_; }
int s21::ModelCredit::SetMonths() { return months_; }