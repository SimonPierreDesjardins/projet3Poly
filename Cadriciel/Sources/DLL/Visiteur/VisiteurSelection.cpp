///////////////////////////////////////////////////////////////////////////
/// @file VisiteurSelection.cpp
/// @authors Ulric Villeneuve et Simon-Pierre Desjardins
/// @date 2016-01-26
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#include "FacadeModele.h"
#include "Vue.h"
#include "VisiteurSelection.h"
#include "ArbreRenduINF2990.h"
#include "NoeudTypes.h"
#include "Utilitaire.h"
#include "Modele3D.h"
#include <iostream>

VisiteurSelection::VisiteurSelection()
{

}

VisiteurSelection::VisiteurSelection(const int& x, const int& y)
	: VisiteurAbstrait(x, y)
{
}


VisiteurSelection::~VisiteurSelection()
{

}

void VisiteurSelection::visiter(NoeudTable* noeud)
{
	for (int i = 0; i < noeud->obtenirNombreEnfants(); i++)
	{
		modele::Modele3D const* modeleEnfant = noeud->chercher(i)->getModele();
		utilitaire::BoiteEnglobante boite = utilitaire::calculerBoiteEnglobante(*modeleEnfant);

		boite.coinMin[1] -= 0.5;
		boite.coinMax[1] += 0.5;

		boite.coinMax[1] *= noeud->chercher(i)->obtenirFacteurDimension()/2 * 1.10;
		boite.coinMin[1] *= noeud->chercher(i)->obtenirFacteurDimension()/2 *1.10;

		/*std::cout << "Boite apres scale : " << boite.coinMin[1] << " , " << boite.coinMax[1] << std::endl;
		std::cout << "Curseur : " << positionRelative_[1] << std::endl;
		std::cout << "Limite inf: " << boite.coinMin[1] + noeud->chercher(i)->obtenirPositionRelative()[1] << std::endl;
		std::cout << "Limite sup: " << boite.coinMax[1] + noeud->chercher(i)->obtenirPositionRelative()[1] << std::endl;*/

		
		float boiteMinX = boite.coinMin[0], boiteMinY = boite.coinMin[1], boiteMaxX = boite.coinMax[0], boiteMaxY = boite.coinMax[1];
		//	boiteMinZ = boite.coinMin[2],  
		//	boiteMaxZ = boite.coinMax[2];

		glm::dvec3 origine, pointBoite1, pointBoite2, pointBoite3, pointBoite4;
		origine[0] = 0.0;
		origine[1] = 0.0;
		origine[2] = 0.0;

		pointBoite1[0] = boite.coinMin[0];
		pointBoite1[1] = boite.coinMin[1];

		pointBoite2[0] = boite.coinMax[0];
		pointBoite2[1] = boite.coinMin[1];

		pointBoite3[0] = boite.coinMax[0];
		pointBoite3[1] = boite.coinMax[1];

		pointBoite4[0] = boite.coinMin[0];
		pointBoite4[1] = boite.coinMax[1];
		

		double r1, r2, r3, r4;
		r1 = utilitaire::calculerDistanceHypothenuse(origine, pointBoite1);
		r2 = utilitaire::calculerDistanceHypothenuse(origine, pointBoite2);
		r3 = utilitaire::calculerDistanceHypothenuse(origine, pointBoite3);
		r4 = utilitaire::calculerDistanceHypothenuse(origine, pointBoite4);

		double angleRotation = noeud->chercher(i)->obtenirAngleRotation();
		pointBoite1[0] = r1*cos(angleRotation-180);
		pointBoite1[1] = r1*sin(angleRotation-180);

		pointBoite2[0] = r2*cos(angleRotation-180);
		pointBoite2[1] = r2*sin(angleRotation-180);

		pointBoite3[0] = r3*cos(angleRotation);
		pointBoite3[1] = r3*sin(angleRotation);

		pointBoite4[0] = r4*cos(angleRotation);
		pointBoite4[1] = r4*sin(angleRotation);

		pointBoite1[0] = noeud->chercher(i)->obtenirPositionRelative()[0] + pointBoite1[0];
		pointBoite1[1] = noeud->chercher(i)->obtenirPositionRelative()[1] + pointBoite1[1];
		pointBoite1[2] = 0.0;

		pointBoite2[0] = noeud->chercher(i)->obtenirPositionRelative()[0] + pointBoite2[0];
		pointBoite2[1] = noeud->chercher(i)->obtenirPositionRelative()[1] + pointBoite2[1];
		pointBoite2[2] = 0.0;

		pointBoite3[0] = noeud->chercher(i)->obtenirPositionRelative()[0] + pointBoite3[0];
		pointBoite3[1] = noeud->chercher(i)->obtenirPositionRelative()[1] + pointBoite3[1];
		pointBoite3[2] = 0.0;

		pointBoite4[0] = noeud->chercher(i)->obtenirPositionRelative()[0] + pointBoite4[0];
		pointBoite4[1] = noeud->chercher(i)->obtenirPositionRelative()[1] + pointBoite4[1];
		pointBoite4[2] = 0.0;

		//boiteMinX = r*cos(angleRotation);
		//boiteMinY = r*sin(angleRotation);

		//if (positionRelative_[0] < boite.coinMin[0] + noeud->chercher(i)->obtenirPositionRelative()[0] || positionRelative_[0] > boite.coinMax[0] + noeud->chercher(i)->obtenirPositionRelative()[0] || positionRelative_[1] < boite.coinMin[1] + noeud->chercher(i)->obtenirPositionRelative()[1] || positionRelative_[1] > boite.coinMax[1] + noeud->chercher(i)->obtenirPositionRelative()[1])
		if (positionRelative_[0] < pointBoite2[0] || positionRelative_[0] > pointBoite1[0] || positionRelative_[1] < pointBoite3[1] || positionRelative_[1] > pointBoite1[1])
		{
			noeud->chercher(i)->assignerSelection(0);
		}
		else
		{
			noeud->chercher(i)->assignerSelection(1);
			std::cout << "Lobjet est selectionne" << std::endl;
		}
	}
}