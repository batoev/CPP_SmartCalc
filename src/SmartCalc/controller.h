#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <iostream>

#include "../s21_model.h"

namespace s21 {
class Controller {
 public:
  Controller() : model_(), model_credit_() {}
  ~Controller() {}

  double Calc(const std::string str, double variable_x) {
    return model_.Calc(str, variable_x);
  }

  void SetDataModelCredit(double sum_credit, double pct, int months) {
    model_credit_.SetSumCredit(sum_credit);
    model_credit_.SetPCT(pct);
    model_credit_.SetMonths(months);
  }

  double AnnuityPMT() { return model_credit_.AnnuityPMT(); }

  double AnnuityOverpayment() { return model_credit_.AnnuityOverpayment(); }

  double AnnuityTotalCredit() { return model_credit_.AnnuityTotalCredit(); }

  double DifferentialMaxPMT() { return model_credit_.DifferentialMaxPMT(); }

  double DifferentialMinPMT() { return model_credit_.DifferentialMinPMT(); }

  double DifferentialOverpayment() {
    return model_credit_.DifferentialOverpayment();
  }

  double DifferentialTotalCredit() {
    return model_credit_.DifferentialTotalCredit();
  }

  double DifferentialPrincipalPMT() {
    return model_credit_.DifferentialPrincipalPMT();
  }

 private:
  Model model_;
  ModelCredit model_credit_;
};
}  // namespace s21

#endif  // CONTROLLER_H_