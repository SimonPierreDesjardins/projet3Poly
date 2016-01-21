#include "EtatCreationPoteau.h"
#include "FacadeModele.h"
#include "ArbreRenduINF2990.h"

#include <iostream> 

EtatCreationPoteau::EtatCreationPoteau()
{
	std::cout << "Creation de poteau" << std::endl;
}




EtatCreationPoteau::~EtatCreationPoteau()
{

}

void EtatCreationPoteau::gererClicGaucheEnfonce(const int& x, const int& y)
{
	std::cout << x << " " << y << std::endl;
}

void EtatCreationPoteau::gererClicGaucheRelache(const int& x, const int& y)
{
	//std::cout << x << " " << y << std::endl;
	std::unique_ptr<VisiteurCreationPoteau> visiteur = std::make_unique<VisiteurCreationPoteau>(x, y);
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepterVisiteur(visiteur.get());
}

void EtatCreationPoteau::effectuerOperation()
{

}