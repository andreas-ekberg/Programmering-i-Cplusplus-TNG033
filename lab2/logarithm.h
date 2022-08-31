/*************************
 * Class Logarithm        *
 * TNG033: Lab 2          *
 **************************/

#pragma once

#include <iostream>
#include <vector>

#include "expression.h"

class Logarithm : public Expression {
    // ADD CODE
public:
     Logarithm();

     Logarithm(const Logarithm& L);

     Logarithm(const Expression& Exp, double firstC, double secC, int base);

     ~Logarithm();

     int& set_base(int x);

     Logarithm* clone() const override;

     virtual double operator()(double d) const override;
     Logarithm& operator=(const Logarithm& L);
 protected:
     double c1, c2;
     int b;
     //Pointer för att den ska kunna vara polynom eller logaritm
     Expression* E;

     void display(std::ostream& os = std::cout) const override;
};
