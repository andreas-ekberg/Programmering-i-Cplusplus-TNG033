/*********************************************************
 * Class Polynomial member functions implementation       *
 * TNG033: Lab 2                                          *
 **********************************************************/

#include "polynomial.h"

 // ADD implementation of the member functions for class Polynomial

//Polynomial constructor med en double
Polynomial::Polynomial(double x){	
	Coeff.push_back(x);
}

//Polynomial constructor med en vector 
Polynomial::Polynomial(const std::vector<double>& V) {
	for (double D : V) {
		Coeff.push_back(D);
	}
}

//Polynomial constructor med en Polynomial (deep copy contructor)
Polynomial::Polynomial(const Polynomial& P) {
	for (size_t i = 0; i < P.Coeff.size(); i++) {
		this->Coeff.push_back(P.Coeff[i]);
	}
}

//Clone function 
Polynomial* Polynomial::clone() const {

	return new Polynomial{ *this };
}

//Returnerar en coeff med plats x och kan ändra den.
double& Polynomial::operator[](int x) {
	return Coeff[x];
}

//Kan retunera en coeff med plats x och kan inte ändra den.
const double& Polynomial::operator[](int x) const{
	return Coeff[x];
}

//Byter alla x till konstanten d och räknar ut värdet.
double Polynomial::operator()(double d) const {
	double temp = 0; 
	for (size_t i = 0; i < this->Coeff.size(); i++) {
		//första elementet
		if (i == 0) {
			temp = this->Coeff[i];
		}
		//resterande funktion
		else {
			temp += (this->Coeff[i] * pow(d, i));
		}
	}
	return temp;

}

Polynomial& Polynomial::operator+=(const Polynomial& P) {
	std::vector<double> newPol;
	//Lägger till hela P i den nya newPol
	for (size_t i = 0; i < P.Coeff.size(); i++) {
		//Så länge this är har element som P har
		if (i < this->Coeff.size()) {
			//Hämtar koefficient från this och P, sedan adderar de.
			newPol.push_back(this->operator[](i) + P[i]);
		}
		//Lägg till resterande element
		else {
			newPol.push_back(P[i]);
		}
	}
	//Ifall this är större finns det kvar värden
	if (this->Coeff.size() > P.Coeff.size()) {
		//Lägg till resterande värden som inte blivit tilllaggda.
		for (size_t i = P.Coeff.size(); i < this->Coeff.size(); i++) {
			newPol.push_back(this->operator[](i));
		}
	}
	Polynomial temp{ newPol };
	*this = temp;
	return *this;
}

//Plus operator och man bara skickar in en polynom
Polynomial operator+(Polynomial Q,const Polynomial P){
	Q += P;
	return Q;
}


void Polynomial::display(std::ostream& os) const {
	
	os << std::fixed << std::setprecision(2);
	for (size_t i = 0; i < Coeff.size(); i++) {
		//Skriver ut första värdet
		if (i == 0) {
			os << Coeff[i];
			//std::cout << std::fixed << std::setprecision(2) << Coeff[i];
		}
		//Ifall den är negativ
		else if (Coeff[i] < 0) {
			os << " - " << abs(Coeff[i]) << " * X^" << i;
			//std::cout << " - " << abs(Coeff[i]) << " * X^" << i;
		}
		//Ifall den är posetiv
		else {
			os << " + " << Coeff[i] << " * X^" << i;
			//std::cout << " + " << Coeff[i] << " * X^" << i;
		}
		
	}
	
}