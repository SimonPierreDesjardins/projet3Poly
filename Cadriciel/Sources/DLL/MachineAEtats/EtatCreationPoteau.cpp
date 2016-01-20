#include "EtatCreationPoteau.h"


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
	std::cout << x << " " << y << std::endl;
}

void EtatCreationPoteau::effectuerOperation()
{

}