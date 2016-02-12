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

VisiteurSelection::~VisiteurSelection()
{

}

void VisiteurSelection::visiter(ArbreRendu* noeud)
{
	noeud->mettreAJourQuadEnglobant();
	noeud->chercher("table")->accepterVisiteur(this);
}


void VisiteurSelection::visiter(NoeudTable* noeud)
{
	bool estSelectionne = true, estSegmentSelectionne;
	if (!estDrag_)
	{
		if (!ctrlAppuye_)
		{
			noeud->deselectionnerTout();
		}
		NoeudAbstrait* enfant;
		for (unsigned i = 0; i < noeud->obtenirNombreEnfants(); i++)
		{
			
			enfant = noeud->chercher(i);
			enfant->accepterVisiteur(this);
		}
	}
	else
	{
		std::cout << positionRelativeAvant_[0] << ", " << positionRelativeAvant_[1] << "\n" << positionRelativeApres_[0] << ", " << positionRelativeApres_[1] << std::endl;
		if (!ctrlAppuye_)
		{
			for (unsigned i = 0; i < noeud->obtenirNombreEnfants(); i++)
			{
				noeud->chercher(i)->assignerSelection(0);
			}
		}

		for (unsigned i = 0; i < noeud->obtenirNombreEnfants(); i++)
		{
			modele::Modele3D const* modeleEnfant = noeud->chercher(i)->getModele();
			utilitaire::BoiteEnglobante boite1 = utilitaire::calculerBoiteEnglobante(*modeleEnfant);
			utilitaire::BoiteEnglobante boite = boite1;

			glm::dvec3 pointBoite1, pointBoite2, pointBoite3, pointBoite4;
			glm::dvec3 p1, p2, p3, p4;
			bool estDansBoite = false;
			int angle = 0; // 0 : 0-90, 1 : 90-180, 2 : 180-270, 3 : 270-360
			double angleRot;
			switch (noeud->chercher(i)->obtenirType()[0])
			{
			case 'p':

				pointBoite1[0] = boite.coinMin[0] * (noeud->chercher(i)->obtenirFacteurMiseAEchelle());
				pointBoite1[1] = boite.coinMin[1] * (noeud->chercher(i)->obtenirFacteurMiseAEchelle());

				pointBoite2[0] = boite.coinMax[0] * (noeud->chercher(i)->obtenirFacteurMiseAEchelle());
				pointBoite2[1] = boite.coinMin[1] * (noeud->chercher(i)->obtenirFacteurMiseAEchelle());

				pointBoite3[0] = boite.coinMax[0] * (noeud->chercher(i)->obtenirFacteurMiseAEchelle());
				pointBoite3[1] = boite.coinMax[1] * (noeud->chercher(i)->obtenirFacteurMiseAEchelle());

				pointBoite4[0] = boite.coinMin[0] * (noeud->chercher(i)->obtenirFacteurMiseAEchelle());
				pointBoite4[1] = boite.coinMax[1] * (noeud->chercher(i)->obtenirFacteurMiseAEchelle());

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


				estSelectionne = estDansRectangleElastique(positionRelativeAvant_, positionRelativeApres_, pointBoite1, pointBoite2, pointBoite3, pointBoite4);

				if (ctrlAppuye_)
				{
					if (estSelectionne)
					{
						noeud->chercher(i)->inverserSelection();
						std::cout << "La selection de lobjet est inversee" << std::endl;
					}
				}
				else
				{
					if (estSelectionne)
					{
						noeud->chercher(i)->assignerSelection(1);
						std::cout << "Lobjet est selectionne" << std::endl;
					}
				}
				break;
			case 'l':
				for (unsigned j = 0; j < noeud->chercher(i)->obtenirNombreEnfants(); j++)
				{
					angleRot = noeud->chercher(i)->chercher(j)->obtenirAngleRotation();
					while (angleRot < 0)
					{
						angleRot += 360;
					}
					while (angleRot >= 360)
					{
						angleRot -= 360;
					}

					boite.coinMax[0] = boite1.coinMax[0] * noeud->chercher(i)->chercher(j)->obtenirFacteurMiseAEchelle();
					boite.coinMin[0] = boite1.coinMin[0] * noeud->chercher(i)->chercher(j)->obtenirFacteurMiseAEchelle();

					pointBoite1[0] = boite.coinMin[0];
					pointBoite1[1] = boite.coinMin[1];

					pointBoite2[0] = boite.coinMax[0];
					pointBoite2[1] = boite.coinMin[1];

					pointBoite3[0] = boite.coinMax[0];
					pointBoite3[1] = boite.coinMax[1];

					pointBoite4[0] = boite.coinMin[0];
					pointBoite4[1] = boite.coinMax[1];

					utilitaire::calculerPositionApresRotation(pointBoite1, p1, angleRot);
					utilitaire::calculerPositionApresRotation(pointBoite2, p2, angleRot);
					utilitaire::calculerPositionApresRotation(pointBoite3, p3, angleRot);
					utilitaire::calculerPositionApresRotation(pointBoite4, p4, angleRot);

					p1[0] += noeud->chercher(i)->chercher(j)->obtenirPositionRelative()[0] + noeud->chercher(i)->obtenirPositionRelative()[0];
					p1[1] += noeud->chercher(i)->chercher(j)->obtenirPositionRelative()[1] + noeud->chercher(i)->obtenirPositionRelative()[1];
					p1[2] = 0.0;

					p2[0] += noeud->chercher(i)->chercher(j)->obtenirPositionRelative()[0] + noeud->chercher(i)->obtenirPositionRelative()[0];
					p2[1] += noeud->chercher(i)->chercher(j)->obtenirPositionRelative()[1] + noeud->chercher(i)->obtenirPositionRelative()[1];
					p2[2] = 0.0;

					p3[0] += noeud->chercher(i)->chercher(j)->obtenirPositionRelative()[0] + noeud->chercher(i)->obtenirPositionRelative()[0];
					p3[1] += noeud->chercher(i)->chercher(j)->obtenirPositionRelative()[1] + noeud->chercher(i)->obtenirPositionRelative()[1];
					p3[2] = 0.0;

					p4[0] += noeud->chercher(i)->chercher(j)->obtenirPositionRelative()[0] + noeud->chercher(i)->obtenirPositionRelative()[0];
					p4[1] += noeud->chercher(i)->chercher(j)->obtenirPositionRelative()[1] + noeud->chercher(i)->obtenirPositionRelative()[1];
					p4[2] = 0.0;

					estSegmentSelectionne = estDansRectangleElastique(positionRelativeAvant_, positionRelativeApres_, p1, p2, p3, p4);
					if (!estSegmentSelectionne)
					{
						estSelectionne = false;
					}
				}
				if (ctrlAppuye_)
				{
					if (estSelectionne)
					{
						noeud->chercher(i)->inverserSelection();
						std::cout << "La selection de lobjet est inversee" << std::endl;
					}
				}
				else
				{
					if (estSelectionne)
					{
						noeud->chercher(i)->assignerSelection(1);
						std::cout << "Lobjet est selectionne" << std::endl;
					}
				}
				estSelectionne = true;
				break;
			case 'm':
				angleRot = noeud->chercher(i)->obtenirAngleRotation();

				while (angleRot < 0)
				{
					angleRot += 360;
				}

				boite1.coinMax[0] *= noeud->chercher(i)->obtenirFacteurMiseAEchelle();
				boite1.coinMin[0] *= noeud->chercher(i)->obtenirFacteurMiseAEchelle();


				pointBoite1[0] = boite1.coinMin[0];
				pointBoite1[1] = boite1.coinMin[1];

				pointBoite2[0] = boite1.coinMax[0];
				pointBoite2[1] = boite1.coinMin[1];

				pointBoite3[0] = boite1.coinMax[0];
				pointBoite3[1] = boite1.coinMax[1];

				pointBoite4[0] = boite1.coinMin[0];
				pointBoite4[1] = boite1.coinMax[1];

				utilitaire::calculerPositionApresRotation(pointBoite1, p1, angleRot);
				utilitaire::calculerPositionApresRotation(pointBoite2, p2, angleRot);
				utilitaire::calculerPositionApresRotation(pointBoite3, p3, angleRot);
				utilitaire::calculerPositionApresRotation(pointBoite4, p4, angleRot);

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

				estSelectionne = estDansRectangleElastique(positionRelativeAvant_, positionRelativeApres_, p1, p2, p3, p4);
				if (ctrlAppuye_)
				{
					if (estSelectionne)
					{
						noeud->chercher(i)->inverserSelection();
						std::cout << "La selection de lobjet est inversee" << std::endl;
					}
				}
				else
				{
					if (estSelectionne)
					{
						noeud->chercher(i)->assignerSelection(1);
						std::cout << "Lobjet est selectionne" << std::endl;
					}
				}
				break;
			default:
				std::cout << "default" << std::endl;
				break;
			}
		}
	}
}

void VisiteurSelection::visiterRectangle(NoeudTable* noeud)
{
	std::cout << "Selection par Rectangle Elastique de :" << positionRelativeAvant_[0] << ", " << positionRelativeAvant_[1] << " a " << positionRelativeApres_[0] << ", " << positionRelativeApres_[1] << std::endl;
}

void VisiteurSelection::assignerControl(bool estControl)
{
	ctrlAppuye_ = estControl;
}

bool VisiteurSelection::estDansRectangleElastique(glm::dvec3 coinRectElastMin, glm::dvec3 coinRectElastMax, glm::dvec3 p1, glm::dvec3 p2, glm::dvec3 p3, glm::dvec3 p4)
{
	glm::dvec3 rectElast1, rectElast2, rectElast3, rectElast4, points[4] = { p1, p2, p3, p4 };
	if (coinRectElastMax[0] < coinRectElastMin[0])
	{
		rectElast1[0] = coinRectElastMax[0];
		rectElast2[0] = coinRectElastMin[0];
		rectElast3[0] = coinRectElastMax[0];
		rectElast4[0] = coinRectElastMin[0];
	}
	else
	{
		rectElast1[0] = coinRectElastMin[0];
		rectElast2[0] = coinRectElastMax[0];
		rectElast3[0] = coinRectElastMin[0];
		rectElast4[0] = coinRectElastMax[0];
	}

	if (coinRectElastMax[1] < coinRectElastMin[1])
	{
		rectElast1[1] = coinRectElastMax[1];
		rectElast2[1] = coinRectElastMax[1];
		rectElast3[1] = coinRectElastMin[1];
		rectElast4[1] = coinRectElastMin[1];
	}
	else
	{
		rectElast1[1] = coinRectElastMin[1];
		rectElast2[1] = coinRectElastMin[1];
		rectElast3[1] = coinRectElastMax[1];
		rectElast4[1] = coinRectElastMax[1];
	}
	rectElast1[2] = 0;
	rectElast2[2] = 0;
	rectElast3[2] = 0;
	rectElast4[2] = 0;

	bool estDansBoite = true;

	for (unsigned i = 0; i < 4; i++)
	{
		if (points[i][0] < rectElast1[0] || points[i][0] > rectElast2[0] || points[i][1] < rectElast1[1] || points[i][1] > rectElast3[1])
		{
			estDansBoite = false;
		}
	}

	return estDansBoite;
}

void VisiteurSelection::visiter(NoeudPoteau* noeud)
{
	utilitaire::QuadEnglobant quad = noeud->obtenirQuadEnglobant();
	

	if (utilitaire::calculerPointEstDansQuad(positionRelative_, noeud->obtenirQuadEnglobant()))
	{
		if (ctrlAppuye_)
		{
			noeud->inverserSelection();
			std::cout << "La selection de lobjet est inversee" << std::endl;
		}
		else
		{
			noeud->assignerSelection(true);
			std::cout << "Lobjet est selectionne" << std::endl;
		}
	}
}

void VisiteurSelection::visiter(NoeudMur* noeud)
{	

	if (utilitaire::calculerPointEstDansQuad(positionRelative_, noeud->obtenirQuadEnglobant()))
	{
		if (ctrlAppuye_)
		{
			noeud->inverserSelection();
		}
		else 
		{
			noeud->assignerSelection(true);
		}
	}
}

void VisiteurSelection::visiter(NoeudLigne* noeud)
{
	
	for (int i = 0; i < noeud->obtenirNombreEnfants(); i++)
	{
		noeud->chercher(i)->accepterVisiteur(this);
	}
	if (noeud->selectionExiste())
	{
		noeud->selectionnerTout();
	}
}

void VisiteurSelection::visiter(NoeudDepart* noeud)
{

}

void VisiteurSelection::visiter(NoeudSegment* noeud)
{
	utilitaire::QuadEnglobant quad = noeud->obtenirQuadEnglobant();

	if (utilitaire::calculerPointEstDansQuad(positionRelative_, quad))
	{
		if (ctrlAppuye_)
		{
			noeud->inverserSelection();
		}
		else
		{
			noeud->assignerSelection(true);
		}
	}
}
