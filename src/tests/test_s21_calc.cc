#include <gtest/gtest.h>

#include "../s21_model.h"

#define S21_EPS 1e-7

TEST(SortingStation, s21_sorting_station_01) {
  std::string str = "2 / (3 + 2) * 5";
  s21::Model model(str, 0);
  int control_type[7] = {s21::MUL, s21::NUM, s21::DIV, s21::SUM,
                         s21::NUM, s21::NUM, s21::NUM};
  int control_result[7] = {0, 5, 0, 0, 2, 3, 2};
  model.SortingStation();
  for (int i = 6; i >= 0; i--) {
    int type = -111;
    double result = -111;
    model.ListTokenPopBack(&type, &result);
    EXPECT_EQ(control_type[i], type);
    EXPECT_EQ(control_result[i], result);
  }
}

TEST(SortingStation, s21_sorting_station_02) {
  std::string str = "2 / (3 + 2) * 5";
  s21::Model model(str, 0);
  int control_type[7] = {s21::NUM, s21::NUM, s21::NUM, s21::SUM,
                         s21::DIV, s21::NUM, s21::MUL};
  int control_result[7] = {2, 3, 2, 0, 0, 5, 0};

  model.SortingStation();
  for (int i = 0; i < 7; i++) {
    int type = -111;
    double result = -111;
    model.ListTokenPopBack(&type, &result);
    EXPECT_EQ(control_type[i], type);
    EXPECT_EQ(control_result[i], result);
  }
}

TEST(SortingStation, s21_sorting_station_03) {
  std::string str = "-2 / (-3 + 2) * 5";
  s21::Model model(str, 0);
  int control_type[9] = {s21::NUM, s21::UMIN, s21::NUM, s21::UMIN, s21::NUM,
                         s21::SUM, s21::DIV,  s21::NUM, s21::MUL};
  int control_result[9] = {2, 0, 3, 0, 2, 0, 0, 5, 0};

  model.SortingStation();
  for (int i = 0; i < 9; i++) {
    int type = -111;
    double result = -111;
    model.ListTokenPopBack(&type, &result);
    EXPECT_EQ(control_type[i], type);
    EXPECT_EQ(control_result[i], result);
  }
}

TEST(SortingStation, s21_sorting_station_04) {
  std::string str = "-3 + 2 * 5";
  s21::Model model(str, 0);
  int control_type[6] = {s21::NUM, s21::UMIN, s21::NUM,
                         s21::NUM, s21::MUL,  s21::SUM};
  int control_result[6] = {3, 0, 2, 5, 0, 0};

  model.SortingStation();
  for (int i = 0; i < 6; i++) {
    int type = -111;
    double result = -111;
    model.ListTokenPopBack(&type, &result);
    EXPECT_EQ(control_type[i], type);
    EXPECT_EQ(control_result[i], result);
  }
}

TEST(SortingStation, s21_sorting_station_05) {
  std::string str = "1 + 2";
  s21::Model model(str, 0);
  int control_type[3] = {s21::NUM, s21::NUM, s21::SUM};
  int control_result[3] = {1, 2, 0};

  model.SortingStation();
  for (int i = 0; i < 3; i++) {
    int type = -111;
    double result = -111;
    model.ListTokenPopBack(&type, &result);
    EXPECT_EQ(control_type[i], type);
    EXPECT_EQ(control_result[i], result);
  }
}

TEST(SortingStation, s21_sorting_station_06) {
  std::string str = "asin(1) + acos(2/5)";
  s21::Model model(str, 0);
  int control_type[7] = {s21::NUM, s21::ASIN, s21::NUM, s21::NUM,
                         s21::DIV, s21::ACOS, s21::SUM};
  int control_result[7] = {1, 0, 2, 5, 0, 0, 0};

  model.SortingStation();
  for (int i = 0; i < 7; i++) {
    int type = -111;
    double result = -111;
    model.ListTokenPopBack(&type, &result);
    EXPECT_EQ(control_type[i], type);
    EXPECT_EQ(control_result[i], result);
  }
}

TEST(SortingStation, s21_sorting_station_07) {
  std::string str = "-5^(-4+3)";
  s21::Model model(str, 0);
  int control_type[7] = {s21::NUM, s21::NUM, s21::UMIN, s21::NUM,
                         s21::SUM, s21::DEG, s21::UMIN};
  int control_result[7] = {5, 4, 0, 3, 0, 0, 0};

  model.SortingStation();
  for (int i = 0; i < 7; i++) {
    int type = -111;
    double result = -111;
    model.ListTokenPopBack(&type, &result);
    EXPECT_EQ(control_type[i], type);
    EXPECT_EQ(control_result[i], result);
  }
}

TEST(SortingStation, s21_sorting_station_08) {
  std::string str = "-5^(-4+3))";
  s21::Model model(str, 0);
  EXPECT_THROW(model.SortingStation(), std::invalid_argument);
}

TEST(SortingStation, s21_sorting_station_09) {
  std::string str = "-5^(-4$+3)";
  s21::Model model(str, 0);
  EXPECT_THROW(model.SortingStation(), std::invalid_argument);
}

TEST(SortingStation, s21_ListTokenRemove) {
  std::string str = "5+3^3-sin(x)+99";
  s21::Model model(str, 0);
  model.SortingStation();
  model.ListTokenRemove();
  int type = -111;
  double result = -111;
  EXPECT_EQ(model.ListTokenPopBack(&type, &result), 1);
}

TEST(SortingStation, s21_Parser) {
  std::string str = "5+3";
  s21::Model model(str, 0);
  std::string token = "5";
  EXPECT_EQ(model.ParserToken(token), 1);
  EXPECT_EQ(model.ParserToken("zorro"), 0);
  EXPECT_EQ(model.ParserToken("z"), 0);
}

TEST(S21Calc, Calc01) {
  std::string str = "(3 + 2) * 5";
  double variable_x = 0, result_y = 0, true_y = 25;
  s21::Model model;
  result_y = model.Calc(str, variable_x);
  EXPECT_NEAR(result_y, true_y, S21_EPS);
}

TEST(S21Calc, Calc02) {
  std::string str = "(3 + 2) * 5";
  double variable_x = 0, result_y = 0, true_y = 25;
  s21::Model model(str, 0);
  result_y = model.Calc(str, variable_x);
  EXPECT_NEAR(result_y, true_y, S21_EPS);
}

TEST(S21Calc, Calc03) {
  std::string str = "2 / (3 + 2) * 5";
  double variable_x = 0, result_y = 0, true_y = 2;
  s21::Model model(str, 0);
  result_y = model.Calc(str, variable_x);
  EXPECT_NEAR(result_y, true_y, S21_EPS);
}

TEST(S21Calc, Calc04) {
  std::string str = "2 / x";
  double variable_x = 0, result_y = 0, true_y = INFINITY;
  s21::Model model(str, 0);
  result_y = model.Calc(str, variable_x);
  EXPECT_TRUE(std::isinf(result_y));
  EXPECT_EQ(result_y, true_y);
}

TEST(S21Calc, Calc05) {
  std::string str = "x^2 + x - 3.14";
  double variable_x = 2, result_y = 0, true_y = 2.86;
  s21::Model model(str, 0);
  result_y = model.Calc(str, variable_x);
  EXPECT_NEAR(result_y, true_y, S21_EPS);
}

TEST(S21Calc, Calc06) {
  std::string str = "-2 / (3 + 2) * 5";
  double variable_x = 0, result_y = 0, true_y = -2;
  s21::Model model(str, 0);
  result_y = model.Calc(str, variable_x);
  EXPECT_NEAR(result_y, true_y, S21_EPS);
}

TEST(S21Calc, Calc07) {
  std::string str = "cos(sin(tan(0.5)))";
  double variable_x = 0, result_y = 0, true_y = 0.86805190005;
  s21::Model model(str, 0);
  result_y = model.Calc(str, variable_x);
  EXPECT_NEAR(result_y, true_y, S21_EPS);
}

TEST(S21Calc, Calc08) {
  std::string str = "log(ln(10))";
  double variable_x = 0, result_y = 0, true_y = 0.36221568869;
  s21::Model model(str, 0);
  result_y = model.Calc(str, variable_x);
  EXPECT_NEAR(result_y, true_y, S21_EPS);
}

TEST(S21Calc, Calc09) {
  std::string str = "-5^(-5+3) + asin(1) - acos(0/5) + atan(-3.14/2)";
  double variable_x = 2, result_y = 0, true_y = -1.04365507798;
  s21::Model model(str, 0);
  result_y = model.Calc(str, variable_x);
  EXPECT_NEAR(result_y, true_y, S21_EPS);
}

TEST(S21Calc, Calc10) {
  std::string str = "sqrt(x) + x^sqrt(-x+5) + log(1.240588) * 5 - ln(3)";
  double variable_x = 2, result_y = 0, true_y = 4.10573623915;
  s21::Model model(str, 0);
  result_y = model.Calc(str, variable_x);
  EXPECT_NEAR(result_y, true_y, S21_EPS);
}

TEST(S21Calc, Calc11) {
  std::string str = "10 mod 3";
  double variable_x = 2, result_y = 0, true_y = 1;
  s21::Model model(str, 0);
  result_y = model.Calc(str, variable_x);
  EXPECT_NEAR(result_y, true_y, S21_EPS);
}

TEST(S21Calc, Calc12) {
  std::string str = "acos(1/5)";
  double variable_x = 2, result_y = 0, true_y = 1.369438406;
  s21::Model model(str, 0);
  result_y = model.Calc(str, variable_x);
  EXPECT_NEAR(result_y, true_y, S21_EPS);
}

TEST(S21Calc, Calc13) {
  std::string str = "asin(1)";
  double variable_x = 2, result_y = 0, true_y = 1.57079632679;
  s21::Model model(str, 0);
  result_y = model.Calc(str, variable_x);
  EXPECT_NEAR(result_y, true_y, S21_EPS);
}

TEST(S21Calc, Calc14) {
  std::string str = "asin(1) + acos(1/5)";
  double variable_x = 0, result_y = 0, true_y = 2.9402347328;
  s21::Model model(str, 0);
  result_y = model.Calc(str, variable_x);
  EXPECT_NEAR(result_y, true_y, S21_EPS);
}

TEST(S21Calc, Calc15) {
  std::string str = "-(3.14 + 5)";
  double variable_x = 0, result_y = 0, true_y = -8.14;
  s21::Model model(str, 0);
  result_y = model.Calc(str, variable_x);
  EXPECT_NEAR(result_y, true_y, S21_EPS);
}

TEST(S21Calc, Calc16) {
  std::string str = "(-3.14 + 5) * 2";
  double variable_x = 0, result_y = 0, true_y = 3.72;
  s21::Model model(str, 0);
  result_y = model.Calc(str, variable_x);
  EXPECT_NEAR(result_y, true_y, S21_EPS);
}

TEST(S21Calc, Calc17) {
  std::string str = "-2^2";
  double variable_x = 0, result_y = 0, true_y = -4;
  s21::Model model(str, 0);
  result_y = model.Calc(str, variable_x);
  EXPECT_NEAR(result_y, true_y, S21_EPS);
}

TEST(S21Calc, Calc18) {
  std::string str = "8 / 2 * (2 + 2)";
  double variable_x = 0, result_y = 0, true_y = 16;
  s21::Model model(str, 0);
  result_y = model.Calc(str, variable_x);
  EXPECT_NEAR(result_y, true_y, S21_EPS);
}

TEST(S21Calc, Calc19) {
  std::string str = "18 / 3.14 / x";
  double variable_x = 2, result_y = 0, true_y = 2.866242038216561;
  s21::Model model(str, 0);
  result_y = model.Calc(str, variable_x);
  EXPECT_NEAR(result_y, true_y, S21_EPS);
}

TEST(S21Calc, Calc20) {
  std::string str = "5^2 + 5 * pi / 180";
  double variable_x = 0, result_y = 0, true_y = 25.0872664626;
  s21::Model model(str, 0);
  result_y = model.Calc(str, variable_x);
  EXPECT_NEAR(result_y, true_y, S21_EPS);
}

TEST(S21Calc, Calc21) {
  std::string str = "-5^(-1)";
  double variable_x = 0, result_y = 0, true_y = -0.2;
  s21::Model model(str, 0);
  result_y = model.Calc(str, variable_x);
  EXPECT_NEAR(result_y, true_y, S21_EPS);
}

TEST(S21Calc, Calc22) {
  std::string str = "-5^(-4+3)";
  double variable_x = 0, result_y = 0, true_y = -0.2;
  s21::Model model(str, 0);
  result_y = model.Calc(str, variable_x);
  EXPECT_NEAR(result_y, true_y, S21_EPS);
}

TEST(S21Calc, Calc23) {
  std::string str = "-5^(-4$+3)";
  double variable_x = 0;
  s21::Model model(str, 0);
  EXPECT_THROW(model.Calc(str, variable_x), std::invalid_argument);
}

TEST(S21Calc, Calc24) {
  std::string str = "(3 + 2) * 5)";
  double variable_x = 0;
  s21::Model model(str, 0);
  EXPECT_THROW(model.Calc(str, variable_x), std::invalid_argument);
}

TEST(S21Calc, Calc25) {
  std::string str = "(3 + 2( * 5)";
  double variable_x = 0;
  s21::Model model(str, 0);
  EXPECT_THROW(model.Calc(str, variable_x), std::invalid_argument);
}

TEST(S21Calc, Calc26) {
  std::string str = "(3 + 2 * 5";
  double variable_x = 0;
  s21::Model model(str, 0);
  EXPECT_THROW(model.Calc(str, variable_x), std::invalid_argument);
}

TEST(S21Calc, Calc27) {
  std::string str = "6/2*(1+2)";
  double variable_x = 0, result_y = 0, true_y = 9;
  s21::Model model(str, 0);
  result_y = model.Calc(str, variable_x);
  EXPECT_NEAR(result_y, true_y, S21_EPS);
}

TEST(S21Calc, Calc28) {
  std::string str = "2^2^3";
  double variable_x = 0, result_y = 0, true_y = 256;
  s21::Model model(str, 0);
  result_y = model.Calc(str, variable_x);
  EXPECT_NEAR(result_y, true_y, S21_EPS);
}

TEST(S21Calc, Calc29) {
  std::string str = "/1";
  double variable_x = 0;
  s21::Model model(str, 0);
  EXPECT_THROW(model.Calc(str, variable_x), std::invalid_argument);
}

TEST(S21Calc, Calc30) {
  std::string str = "mod1";
  double variable_x = 0;
  s21::Model model(str, 0);
  EXPECT_THROW(model.Calc(str, variable_x), std::invalid_argument);
}

TEST(S21Calc, Calc31) {
  std::string str = "+1-3";
  double variable_x = 0, result_y = 0, true_y = -2;
  s21::Model model(str, 0);
  result_y = model.Calc(str, variable_x);
  EXPECT_NEAR(result_y, true_y, S21_EPS);
}

TEST(S21Calc, Calc32) {
  std::string str = "sQrT(5 - 1)";
  double variable_x = 0, result_y = 0, true_y = 2;
  s21::Model model(str, 0);
  result_y = model.Calc(str, variable_x);
  EXPECT_NEAR(result_y, true_y, S21_EPS);
}

TEST(S21Calc, Calc33) {
  std::string str = "+1-3%";
  double variable_x = 0;
  s21::Model model(str, 0);
  EXPECT_THROW(model.Calc(str, variable_x), std::invalid_argument);
}

TEST(S21Calc, Calc34) {
  std::string str = "6/2*(1+2)";
  double variable_x = 0, result_y = 0, true_y = 9;
  s21::Model model(str, variable_x);
  result_y = model.Calc();
  EXPECT_NEAR(result_y, true_y, S21_EPS);
}

TEST(S21Calc, Calc35) {
  std::string str = "sQrT(5 - 1)";
  double variable_x = 0, result_y = 0, true_y = 2;
  s21::Model model(str, variable_x);
  result_y = model.Calc();
  EXPECT_NEAR(result_y, true_y, S21_EPS);
}

TEST(S21Calc, simple_square) {
  std::string str = "3x^2 - 4x + 5";
  double variable_x = 3, result_y = 0, true_y = 20;
  s21::Model model(str, 0);
  result_y = model.Calc(str, variable_x);
  EXPECT_NEAR(result_y, true_y, S21_EPS);
}

TEST(S21Calc, Math) {
  std::string str = "5*2-4^2-cos(pi)+#";
  double variable_x = 0;
  s21::Model model(str, 0);
  EXPECT_THROW(model.Calc(str, variable_x), std::invalid_argument);
}

TEST(S21Calc, Geters) {
  std::string str = "x+50";
  double variable_x = 46, result_y = 0, true_y = 96;
  s21::Model model(str, variable_x);
  EXPECT_EQ(model.GetInfixStr(), str);
  EXPECT_EQ(model.GetVariableX(), variable_x);
  result_y = model.Calc();
  EXPECT_EQ(result_y, true_y);
  EXPECT_EQ(model.GetResult(), true_y);
}

TEST(S21Calc, Seters) {
  std::string str = "Bulat";
  double variable_x = 0, result_y = 0, true_y = 10;
  s21::Model model(str, variable_x);
  model.SetInfixStr("5+x");
  model.SetVariableX(5);
  result_y = model.Calc();
  EXPECT_NEAR(result_y, true_y, S21_EPS);
}

TEST(S21_CreditCalc, AnnuityCreditCalc1) {
  s21::ModelCredit model(100000, 12, 12);
  EXPECT_NEAR(model.AnnuityPMT(), 8884.88, S21_EPS);
  EXPECT_NEAR(model.AnnuityOverpayment(), 6618.56, S21_EPS);
  EXPECT_NEAR(model.AnnuityTotalCredit(), 106618.56, S21_EPS);
}

TEST(S21_CreditCalc, AnnuityCreditCalc2) {
  s21::ModelCredit model(100000, 15, 5 * 12);
  EXPECT_NEAR(model.AnnuityPMT(), 2378.99, S21_EPS);
  EXPECT_NEAR(model.AnnuityOverpayment(), 42739.40, S21_EPS);
  EXPECT_NEAR(model.AnnuityTotalCredit(), 142739.40, S21_EPS);
}

TEST(S21_CreditCalc, AnnuityCreditCalc3) {
  s21::ModelCredit model(1, 15, 5 * 12);
  EXPECT_NEAR(model.AnnuityPMT(), 0.02, S21_EPS);
  EXPECT_NEAR(model.AnnuityOverpayment(), 0.20, S21_EPS);
  EXPECT_NEAR(model.AnnuityTotalCredit(), 1.20, S21_EPS);
}

TEST(S21_CreditCalc, AnnuityCreditCalc4) {
  s21::ModelCredit model(100000, 13, 1);
  EXPECT_NEAR(model.AnnuityPMT(), 101083.33, S21_EPS);
  EXPECT_NEAR(model.AnnuityOverpayment(), 1083.33, S21_EPS);
  EXPECT_NEAR(model.AnnuityTotalCredit(), 101083.33, S21_EPS);
}

TEST(S21_CreditCalc, AnnuityCreditCalc5) {
  s21::ModelCredit model(100000, 0.01, 12);
  EXPECT_NEAR(model.AnnuityPMT(), 8333.78, S21_EPS);
  EXPECT_NEAR(model.AnnuityOverpayment(), 5.36, S21_EPS);
  EXPECT_NEAR(model.AnnuityTotalCredit(), 100005.36, S21_EPS);
}

TEST(S21_CreditCalc, AnnuityCreditCalc6) {
  s21::ModelCredit model(300000, 15, 20);
  EXPECT_NEAR(model.AnnuityPMT(), 17046.12, S21_EPS);
  EXPECT_NEAR(model.AnnuityOverpayment(), 40922.40, S21_EPS);
  EXPECT_NEAR(model.AnnuityTotalCredit(), 340922.40, S21_EPS);
}

TEST(S21_CreditCalc, AnnuityCreditCalc7) {
  s21::ModelCredit model;
  model.SetSumCredit(300000);
  model.SetPCT(15);
  model.SetMonths(20);
  EXPECT_NEAR(model.AnnuityPMT(), 17046.12, S21_EPS);
  EXPECT_NEAR(model.AnnuityOverpayment(), 40922.40, S21_EPS);
  EXPECT_NEAR(model.AnnuityTotalCredit(), 340922.40, S21_EPS);
}

TEST(S21_CreditCalc, Seters_and_Geters) {
  s21::ModelCredit model;
  model.SetSumCredit(300000);
  model.SetPCT(15);
  model.SetMonths(20);
  EXPECT_NEAR(model.GetSumCredit(), 300000, S21_EPS);
  EXPECT_NEAR(model.GetPCT(), 0.15, S21_EPS);
  EXPECT_NEAR(model.SetMonths(), 20, S21_EPS);
}

TEST(S21_CreditCalc, SumCreditZero) {
  s21::ModelCredit model(0, 15, 5 * 12);
  EXPECT_THROW(model.AnnuityPMT(), std::invalid_argument);
  EXPECT_THROW(model.AnnuityOverpayment(), std::invalid_argument);
  EXPECT_THROW(model.AnnuityTotalCredit(), std::invalid_argument);
}

TEST(S21_CreditCalc, PCT_zero) {
  s21::ModelCredit model(100000, 0, 5 * 12);
  EXPECT_THROW(model.AnnuityPMT(), std::invalid_argument);
  EXPECT_THROW(model.AnnuityOverpayment(), std::invalid_argument);
  EXPECT_THROW(model.AnnuityTotalCredit(), std::invalid_argument);
}

TEST(S21_CreditCalc, Months_zero) {
  s21::ModelCredit model(100000, 10, 0);
  EXPECT_THROW(model.AnnuityPMT(), std::invalid_argument);
  EXPECT_THROW(model.AnnuityOverpayment(), std::invalid_argument);
  EXPECT_THROW(model.AnnuityTotalCredit(), std::invalid_argument);
}

TEST(S21_CreditCalc, DifferentialCreditCalc1) {
  s21::ModelCredit model(100000, 12, 12);  // сумма, ставка и срок кредита
  EXPECT_NEAR(model.DifferentialMaxPMT(), 9333.33, S21_EPS);
  EXPECT_NEAR(model.DifferentialMinPMT(), 8416.67, S21_EPS);
  EXPECT_NEAR(model.DifferentialOverpayment(), 6500.00, S21_EPS);
  EXPECT_NEAR(model.DifferentialTotalCredit(), 106500.00, S21_EPS);
}

TEST(S21_CreditCalc, DifferentialCreditCalc2) {
  s21::ModelCredit model(100000, 15, 5 * 12);
  EXPECT_NEAR(model.DifferentialMaxPMT(), 2916.67, S21_EPS);
  EXPECT_NEAR(model.DifferentialMinPMT(), 1687.50, S21_EPS);
  EXPECT_NEAR(model.DifferentialOverpayment(), 38125.00, S21_EPS);
  EXPECT_NEAR(model.DifferentialTotalCredit(), 138125.00, S21_EPS);
}

TEST(S21_CreditCalc, DifferentialCreditCalc3) {
  s21::ModelCredit model(1, 15, 5 * 12);
  EXPECT_NEAR(model.DifferentialMaxPMT(), 0.03, S21_EPS);
  EXPECT_NEAR(model.DifferentialMinPMT(), 0.02, S21_EPS);
  EXPECT_NEAR(model.DifferentialOverpayment(), 0.38, S21_EPS);
  EXPECT_NEAR(model.DifferentialTotalCredit(), 1.38, S21_EPS);
}

TEST(S21_CreditCalc, DifferentialCreditCalc4) {
  s21::ModelCredit model(100000, 13, 1);
  EXPECT_NEAR(model.DifferentialMaxPMT(), 101083.33, S21_EPS);
  EXPECT_NEAR(model.DifferentialMinPMT(), 101083.33, S21_EPS);
  EXPECT_NEAR(model.DifferentialOverpayment(), 1083.33, S21_EPS);
  EXPECT_NEAR(model.DifferentialTotalCredit(), 101083.33, S21_EPS);
}

TEST(S21_CreditCalc, DifferentialCreditCalc5) {
  s21::ModelCredit model(100000, 0.01, 12);
  EXPECT_NEAR(model.DifferentialMaxPMT(), 8334.17, S21_EPS);
  EXPECT_NEAR(model.DifferentialMinPMT(), 8333.40, S21_EPS);
  EXPECT_NEAR(model.DifferentialOverpayment(), 5.42, S21_EPS);
  EXPECT_NEAR(model.DifferentialTotalCredit(), 100005.42, S21_EPS);
}

TEST(S21_CreditCalc, DifferentialSumCreditZero) {
  s21::ModelCredit model(0, 15, 5 * 12);
  EXPECT_THROW(model.DifferentialMaxPMT(), std::invalid_argument);
  EXPECT_THROW(model.DifferentialMinPMT(), std::invalid_argument);
  EXPECT_THROW(model.DifferentialOverpayment(), std::invalid_argument);
  EXPECT_THROW(model.DifferentialTotalCredit(), std::invalid_argument);
}

TEST(S21_CreditCalc, DifferentialPCT_zero) {
  s21::ModelCredit model(100000, 0, 5 * 12);
  EXPECT_THROW(model.DifferentialMaxPMT(), std::invalid_argument);
  EXPECT_THROW(model.DifferentialMinPMT(), std::invalid_argument);
  EXPECT_THROW(model.DifferentialOverpayment(), std::invalid_argument);
  EXPECT_THROW(model.DifferentialTotalCredit(), std::invalid_argument);
}

TEST(S21_CreditCalc, DifferentialMonths_zero) {
  s21::ModelCredit model(100000, 10, 0);
  EXPECT_THROW(model.DifferentialMaxPMT(), std::invalid_argument);
  EXPECT_THROW(model.DifferentialMinPMT(), std::invalid_argument);
  EXPECT_THROW(model.DifferentialOverpayment(), std::invalid_argument);
  EXPECT_THROW(model.DifferentialTotalCredit(), std::invalid_argument);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}