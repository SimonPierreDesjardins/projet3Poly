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

		glm::dvec3 pointBoite1, pointBoite2, pointBoite3, pointBoite4;
		glm::dvec3 p1, p2, p3, p4;
		double droite12A, droite12K, droite23A, droite23K, droite34A, droite34K, droite41A, droite41K;
		bool estDansBoite = false;
		int angle = 0; // 0 : 0-90, 1 : 90-180, 2 : 180-270, 3 : 270-360
		switch (noeud->chercher(i)->obtenirType()[0])
		{
		case 'p' :

			pointBoite1[0] = boite.coinMin[0];
			pointBoite1[1] = boite.coinMin[1];

			pointBoite2[0] = boite.coinMax[0];
			pointBoite2[1] = boite.coinMin[1];

			pointBoite3[0] = boite.coinMax[0];
			pointBoite3[1] = boite.coinMax[1];

			pointBoite4[0] = boite.coinMin[0];
			pointBoite4[1] = boite.coinMax[1];

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

			if (positionRelative_[0] < pointBoite2[0] && positionRelative_[0] > pointBoite1[0] && positionRelative_[1] < pointBoite3[1] && positionRelative_[1] > pointBoite1[1])
			{
				noeud->chercher(i)->assignerSelection(1);
				std::cout << "Lobjet est selectionne" << std::endl;
			}
			else
			{
				noeud->chercher(i)->assignerSelection(0);
				std::cout << "Lobjet nest pas selectionne" << std::endl;
			}
			break;
		case 'l':
			//boite.coinMin[1] -= 0.5;
			//boite.coinMax[1] += 0.5;

			boite.coinMax[0] *= noeud->chercher(i)->chercher(0)->obtenirFacteurMiseAEchelle();
			boite.coinMin[0] *= noeud->chercher(i)->chercher(0)->obtenirFacteurMiseAEchelle();

			/*std::cout << "Boite apres scale : " << boite.coinMin[1] << " , " << boite.coinMax[1] << std::endl;
			std::cout << "Curseur : " << positionRelative_[1] << std::endl;
			std::cout << "Limite inf: " << boite.coinMin[1] + noeud->chercher(i)->obtenirPositionRelative()[1] << std::endl;
			std::cout << "Limite sup: " << boite.coinMax[1] + noeud->chercher(i)->obtenirPositionRelative()[1] << std::endl;*/


			//	boiteMinZ = boite.coinMin[2],  
			//	boiteMaxZ = boite.coinMax[2];

			/*origine[0] = 0.0;
			origine[1] = 0.0;
			origine[2] = 0.0;*/

			pointBoite1[0] = boite.coinMin[0];
			pointBoite1[1] = boite.coinMin[1];

			pointBoite2[0] = boite.coinMax[0];
			pointBoite2[1] = boite.coinMin[1];

			pointBoite3[0] = boite.coinMax[0];
			pointBoite3[1] = boite.coinMax[1];

			pointBoite4[0] = boite.coinMin[0];
			pointBoite4[1] = boite.coinMax[1];

			utilitaire::calculerPositionApresRotation(pointBoite1, p1, (noeud->chercher(i)->chercher(0)->obtenirAngleRotation()));
			utilitaire::calculerPositionApresRotation(pointBoite2, p2, (noeud->chercher(i)->chercher(0)->obtenirAngleRotation()));
			utilitaire::calculerPositionApresRotation(pointBoite3, p3, (noeud->chercher(i)->chercher(0)->obtenirAngleRotation()));
			utilitaire::calculerPositionApresRotation(pointBoite4, p4, (noeud->chercher(i)->chercher(0)->obtenirAngleRotation()));

			/*double r1, r2, r3, r4;
			r1 = utilitaire::calculerDistanceHypothenuse(origine, pointBoite1);
			r2 = utilitaire::calculerDistanceHypothenuse(origine, pointBoite2);
			r3 = utilitaire::calculerDistanceHypothenuse(origine, pointBoite3);
			r4 = utilitaire::calculerDistanceHypothenuse(origine, pointBoite4);

			double angleRotation = noeud->chercher(i)->obtenirAngleRotation();
			pointBoite1[0] = r1*cos(angleRotation-180);
			pointBoite1[1] = r1*sin(angleRotation-180);

			pointBoite2[0] = r2*cos(angleRotation-180);				mesh::Couleur couleur = mesh.obtenirCouleurs();
				glColor4f(couleur[0], couleur[1], couleur[2], couleur[3]);
			pointBoite2[1] = r2*sin(angleRotation-180);

			pointBoite3[0] = r3*cos(angleRotation);
			pointBoite3[1] = r3*sin(angleRotation);

			pointBoite4[0] = r4*cos(angleRotation);
			pointBoite4[1] = r4*sin(angleRotation);*/

			p1[0] += noeud->chercher(i)->obtenirPositionRelative()[0];
			p1[1] += noeud->chercher(i)->obtenirPositionRelative()[1];
			p1[2] = 0.0;

			p2[0] += noeud->chercher(i)->obtenirPositionRelative()[0];
			p2[1] += noeud->chercher(i)->obtenirPositionRelative()[1];
			p2[2] = 0.0;

			p3[0] += noeud->chercher(i)->obtenirPositionRelative()[0];
			p3[1] += noeud->chercher(i)->obtenirPositionRelative()[1];
			p3[2] = 0.0;

			p4[0] += noeud->chercher(i)->obtenirPositionRelative()[0];
			p4[1] += noeud->chercher(i)->obtenirPositionRelative()[1];
			p4[2] = 0.0;

			std::cout << "Position Boite " << i << " :" << std::endl;
			std::cout << "p1: " << p1[0] << ", " << p1[1] << std::endl;
			std::cout << "p2: " << p2[0] << ", " << p2[1] << std::endl;
			std::cout << "p3: " << p3[0] << ", " << p3[1] << std::endl;
			std::cout << "p4: " << p4[0] << ", " << p4[1] << std::endl;
		

			droite12A = (p1[1] - p2[1]) / (p1[0] - p2[0]);
			droite12K = p1[1] - (droite12A * p1[0]);
			droite23A = (p2[1] - p3[1]) / (p2[0] - p3[0]);
			droite23K = p2[1] - (droite23A * p2[0]);
			droite34A = (p3[1] - p4[1]) / (p3[0] - p4[0]);
			droite34K = p3[1] - (droite34A * p3[0]);
			droite41A = (p4[1] - p1[1]) / (p4[0] - p1[0]);
			droite41K = p4[1] - (droite41A * p4[0]);

			if (noeud->chercher(i)->chercher(0)->obtenirAngleRotation() < 90 && noeud->chercher(i)->chercher(0)->obtenirAngleRotation() > 0)
			{
				angle = 0;
			}
			else if (noeud->chercher(i)->chercher(0)->obtenirAngleRotation() < 180 && noeud->chercher(i)->chercher(0)->obtenirAngleRotation() > 90)
			{
				angle = 1;
			}
			else if (noeud->chercher(i)->chercher(0)->obtenirAngleRotation() < 270 && noeud->chercher(i)->chercher(0)->obtenirAngleRotation() > 180)
			{
				angle = 2;
			}
			else if (noeud->chercher(i)->chercher(0)->obtenirAngleRotation() < 360 && noeud->chercher(i)->chercher(0)->obtenirAngleRotation() > 270)
			{
				angle = 3;
			}

			switch (angle)
			{
			case 0:
				if ((positionRelative_[0] * droite12A + droite12K) < positionRelative_[1] && (positionRelative_[0] * droite23A + droite23K) > positionRelative_[1] && (positionRelative_[0] * droite34A + droite34K) > positionRelative_[1] && (positionRelative_[0] * droite41A + droite41K) < positionRelative_[1])
				{
					estDansBoite = true;
				}
				break;
			case 1:
				if ((positionRelative_[0] * droite12A + droite12K) > positionRelative_[1] && (positionRelative_[0] * droite23A + droite23K) > positionRelative_[1] && (positionRelative_[0] * droite34A + droite34K) < positionRelative_[1] && (positionRelative_[0] * droite41A + droite41K) < positionRelative_[1])
				{
					estDansBoite = true;
				}
				break;
			case 2:
				if ((positionRelative_[0] * droite12A + droite12K) > positionRelative_[1] && (positionRelative_[0] * droite23A + droite23K) < positionRelative_[1] && (positionRelative_[0] * droite34A + droite34K) < positionRelative_[1] && (positionRelative_[0] * droite41A + droite41K) > positionRelative_[1])
				{
					estDansBoite = true;
				}
				break;
			case 3:
				if ((positionRelative_[0] * droite12A + droite12K) < positionRelative_[1] && (positionRelative_[0] * droite23A + droite23K) < positionRelative_[1] && (positionRelative_[0] * droite34A + droite34K) > positionRelative_[1] && (positionRelative_[0] * droite41A + droite41K) > positionRelative_[1])
				{
					estDansBoite = true;
				}
				break;
			default:
				break;
			}


			if (estDansBoite)
			{
				noeud->chercher(i)->assignerSelection(1);
				std::cout << "Lobjet est selectionne" << std::endl;
			}
			else
			{
				noeud->chercher(i)->assignerSelection(0);
				std::cout << "Lobjet nest pas selectionne" << std::endl;
			}
			break;
		case 'm':
			boite.coinMin[1] -= 0.5;
			boite.coinMax[1] += 0.5;

			boite.coinMax[1] *= noeud->chercher(i)->obtenirFacteurMiseAEchelle() / 2 * 1.10;
			boite.coinMin[1] *= noeud->chercher(i)->obtenirFacteurMiseAEchelle() / 2 * 1.10;

			/*std::cout << "Boite apres scale : " << boite.coinMin[1] << " , " << boite.coinMax[1] << std::endl;
			std::cout << "Curseur : " << positionRelative_[1] << std::endl;
			std::cout << "Limite inf: " << boite.coinMin[1] + noeud->chercher(i)->obtenirPositionRelative()[1] << std::endl;
			std::cout << "Limite sup: " << boite.coinMax[1] + noeud->chercher(i)->obtenirPositionRelative()[1] << std::endl;*/


			//	boiteMinZ = boite.coinMin[2],  
			//	boiteMaxZ = boite.coinMax[2];

			/*origine[0] = 0.0;
			origine[1] = 0.0;
			origine[2] = 0.0;*/

			pointBoite1[0] = boite.coinMin[0];
			pointBoite1[1] = boite.coinMin[1];

			pointBoite2[0] = boite.coinMax[0];
			pointBoite2[1] = boite.coinMin[1];

			pointBoite3[0] = boite.coinMax[0];
			pointBoite3[1] = boite.coinMax[1];

			pointBoite4[0] = boite.coinMin[0];
			pointBoite4[1] = boite.coinMax[1];

			utilitaire::calculerPositionApresRotation(pointBoite1, pointBoite1, noeud->chercher(i)->obtenirAngleRotation());
			utilitaire::calculerPositionApresRotation(pointBoite2, pointBoite2, noeud->chercher(i)->obtenirAngleRotation());
			utilitaire::calculerPositionApresRotation(pointBoite3, pointBoite3, noeud->chercher(i)->obtenirAngleRotation());
			utilitaire::calculerPositionApresRotation(pointBoite4, pointBoite4, noeud->chercher(i)->obtenirAngleRotation());

			/*double r1, r2, r3, r4;
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
			pointBoite4[1] = r4*sin(angleRotation);*/

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

			//if (positionRelative_[0] < boite.coinMin[0] + noeud->chercher(i)->obtenirPositionRelative()[0] || positionRelative_[0] > boite.coinMax[0] + noeud->chercher(i)->obtenirPositionRelative()[0] || positionRelative_[1] < boite.coinMin[1] + noeud->chercher(i)->obtenirPositionRelative()[1] || positionRelative_[1] > boite.coinMax[1] + noeud->chercher(i)->obtenirPositionRelative()[1])
			if (positionRelative_[0] < pointBoite2[0] && positionRelative_[0] > pointBoite1[0] && positionRelative_[1] < pointBoite3[1] && positionRelative_[1] > pointBoite1[1])
			{
				noeud->chercher(i)->assignerSelection(1);
				std::cout << "Lobjet est selectionne" << std::endl;
			}
			else
			{
				noeud->chercher(i)->assignerSelection(0);
				std::cout << "Lobjet nest pas selectionne" << std::endl;
			}
			break;
		default:
			std::cout << "default" << std::endl;
			break;
		}
	}
}