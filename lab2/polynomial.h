/*************************
 * Class Polynomial       *
 * TNG033: Lab 2          *
 **************************/

#pragma once

#include <iostream>
#include <iomanip>
#include <vector>

#include "expression.h"

class Polynomial : public Expression {
    // ADD CODE
public:

    //Conversion constructor (gör double till polynom)
    Polynomial(double x);
    //Constructor med vector
    explicit Polynomial(const std::vector<double>& V);
    //Copy constructor
    Polynomial(const Polynomial& P);

    //Display funktionen
    

    Polynomial* clone() const override;

    //Operators
    virtual double operator()(double d) const override;
    double& operator[](int x);
    const double& operator[](int x) const;

    Polynomial& operator+=(const Polynomial& P);
    //Friend för att nå andra member funcitons
    friend Polynomial operator+(Polynomial lhs, const Polynomial P) ;
protected: 
    void display(std::ostream& os = std::cout) const override;
    //vector med alla coeff
    std::vector<double> Coeff;
private:
  
};
