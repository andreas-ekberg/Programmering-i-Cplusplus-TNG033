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

//Returnerar en coeff med plats x och kan �ndra den.
double& Polynomial::operator[](int x) {
	return Coeff[x];
}

//Kan retunera en coeff med plats x och kan inte �ndra den.
const double& Polynomial::operator[](int x) const{
	return Coeff[x];
}

//Byter alla x till konstanten d och r�knar ut v�rdet.
double Polynomial::operator()(double d) const {
	double temp = 0; 
	for (size_t i = 0; i < this->Coeff.size(); i++) {
		//f�rsta elementet
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
	//L�gger till hela P i den nya newPol
	for (size_t i = 0; i < P.Coeff.size(); i++) {
		//S� l�nge this �r har element som P har
		if (i < this->Coeff.size()) {
			//H�mtar koefficient fr�n this och P, sedan adderar de.
			newPol.push_back(this->operator[](i) + P[i]);
		}
		//L�gg till resterande element
		else {
			newPol.push_back(P[i]);
		}
	}
	//Ifall this �r st�rre finns det kvar v�rden
	if (this->Coeff.size() > P.Coeff.size()) {
		//L�gg till resterande v�rden som inte blivit tilllaggda.
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
		//Skriver ut f�rsta v�rdet
		if (i == 0) {
			os << Coeff[i];
			//std::cout << std::fixed << std::setprecision(2) << Coeff[i];
		}
		//Ifall den �r negativ
		else if (Coeff[i] < 0) {
			os << " - " << abs(Coeff[i]) << " * X^" << i;
			//std::cout << " - " << abs(Coeff[i]) << " * X^" << i;
		}
		//Ifall den �r posetiv
		else {
			os << " + " << Coeff[i] << " * X^" << i;
			//std::cout << " + " << Coeff[i] << " * X^" << i;
		}
		
	}
	
}