///////////////////////////////////////////////////////////////////////////
/// @file EtatAbstrait.cpp
/// @author 
/// @date 2016-01-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#include "EtatAbstrait.h"
#include <math.h>
#include "Utilitaire.h"
#include <iostream>

EtatAbstrait::EtatAbstrait()
{

}

EtatAbstrait::~EtatAbstrait()
{

}

void EtatAbstrait::gererClicDroitEnfonce(const int& x, const int& y)
{

}

void EtatAbstrait::gererClicDroitRelache(const int& x, const int& y)
{

}

void EtatAbstrait::gererClicGaucheEnfonce(const int& x, const int& y)
{

}

void EtatAbstrait::gererClicGaucheRelache(const int& x, const int& y)
{

}

void EtatAbstrait::gererMouvementSouris(const int & x, const int& y)
{

}


float EtatAbstrait::calculerAngleRotation(double dx, double dy)
{
	if (dx == 0 && dy == 0)
	{
		return 0.0;
	}

	if (dy == 0 && dx < 0)
	{
		return utilitaire::PI;
	}	

	else if (dx == 0 && dy > 0)
	{			
		return utilitaire::PI / 2.0;
	}	

	else if (dx == 0 && dy < 0)
	{			
		return 3.0 * utilitaire::PI / 2.0;
	}

	float angle = atan(dy / dx);
	if (dy < 0 && dx > 0)
	{
		angle += 2 * utilitaire::PI;
	}
	else if (dy > 0 && dx < 0)
	{
		angle += utilitaire::PI;
	}
	else if (dy < 0 && dx < 0)
	{
		angle += utilitaire::PI;
	}
	return angle;
}