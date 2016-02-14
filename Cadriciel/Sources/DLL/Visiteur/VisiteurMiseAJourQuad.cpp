///////////////////////////////////////////////////////////////////////////
/// @file VisiteurMiseAJourQuad.cpp
/// @author Olivier St-Amour 
/// @date 2016-02-13
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#include "VisiteurMiseAJourQuad.h"
#include "NoeudTypes.h"
#include "ArbreRendu.h"


VisiteurMiseAJourQuad::VisiteurMiseAJourQuad()
{

}


VisiteurMiseAJourQuad::~VisiteurMiseAJourQuad()
{

}


void VisiteurMiseAJourQuad::visiter(ArbreRendu* noeud)
{
	noeud->chercher("table")->accepterVisiteur(this);
}

void VisiteurMiseAJourQuad::visiter(NoeudTable* noeud)
{
	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++)
	{
		noeud->chercher(i)->accepterVisiteur(this);
	}
}

void VisiteurMiseAJourQuad::visiter(NoeudDuplication* noeud)
{
	glm::dvec3 positionVirtuelleParent = { 0.0, 0.0, 0.0 };	
	NoeudAbstrait* parent = noeud->obtenirParent();
	if (parent != nullptr)
	{
		positionVirtuelleParent = calculerPositionVirtuelle(parent->obtenirQuadEnglobantCourant());
	}
	/// Mettre à jour le quad de la duplication.
	utilitaire::QuadEnglobant quad;
	for (int i = 0; i < quad.N_COINS; i++)
	{
		quad.coins[i] = positionVirtuelleParent + noeud->obtenirPositionRelative();
	}
	noeud->assignerQuadEnglobantCourant(quad);
	/// Mettre à jour le quad des enfants.
	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++)
	{
		noeud->chercher(i)->accepterVisiteur(this);
	}
}

void VisiteurMiseAJourQuad::visiter(NoeudPoteau* noeud)
{
	glm::dvec3 positionVirtuelleParent = { 0.0, 0.0, 0.0 };	
	NoeudAbstrait* parent = noeud->obtenirParent();
	// Calculer la position virtuelle du parent.
	if (parent != nullptr)
	{
		positionVirtuelleParent = calculerPositionVirtuelle(parent->obtenirQuadEnglobantCourant());
	}
	// Calculer la position des coins du quad.
	utilitaire::QuadEnglobant quad = noeud->obtenirQuadEnglobantModele();
	for (int i = 0; i < quad.N_COINS; i++)
	{
		quad.coins[i] *= noeud->obtenirFacteurMiseAEchelle();
		quad.coins[i] += (positionVirtuelleParent + noeud->obtenirPositionRelative());
	}
	noeud->assignerQuadEnglobantCourant(quad);
}

void VisiteurMiseAJourQuad::visiter(NoeudMur* noeud)
{
	glm::dvec3 positionVirtuelleParent = { 0.0, 0.0, 0.0 };	
	NoeudAbstrait* parent = noeud->obtenirParent();
	// Calculer la position virtuelle du parent.
	if (parent != nullptr)
	{
		positionVirtuelleParent = calculerPositionVirtuelle(parent->obtenirQuadEnglobantCourant());
	}
	// Calculer la position des coins du quad.
	utilitaire::QuadEnglobant quad = noeud->obtenirQuadEnglobantModele();
	glm::dvec3 tmp;
	for (int i = 0; i < quad.N_COINS; i++)
	{
		quad.coins[i].x *= noeud->obtenirFacteurMiseAEchelle();
		tmp = quad.coins[i];
		utilitaire::calculerPositionApresRotation(tmp, quad.coins[i], noeud->obtenirAngleRotation());
		quad.coins[i] += (positionVirtuelleParent + noeud->obtenirPositionRelative());
	}
	noeud->assignerQuadEnglobantCourant(quad);
}

void VisiteurMiseAJourQuad::visiter(NoeudLigne* noeud)
{
	glm::dvec3 positionVirtuelleParent = { 0.0, 0.0, 0.0 };	
	NoeudAbstrait* parent = noeud->obtenirParent();
	if (parent != nullptr)
	{
		positionVirtuelleParent = calculerPositionVirtuelle(parent->obtenirQuadEnglobantCourant());
	}
	/// Mettre à jour le quad de la duplication.
	utilitaire::QuadEnglobant quad;
	for (int i = 0; i < quad.N_COINS; i++)
	{
		quad.coins[i] = positionVirtuelleParent + noeud->obtenirPositionRelative();
	}
	noeud->assignerQuadEnglobantCourant(quad);
	/// Mettre à jour le quad des enfants.
	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++)
	{
		noeud->chercher(i)->accepterVisiteur(this);
	}
}

void VisiteurMiseAJourQuad::visiter(NoeudSegment* noeud)
{
	glm::dvec3 positionVirtuelleParent = { 0.0, 0.0, 0.0 };	
	NoeudAbstrait* parent = noeud->obtenirParent();
	// Calculer la position virtuelle du parent.
	if (parent != nullptr)
	{
		positionVirtuelleParent = calculerPositionVirtuelle(parent->obtenirQuadEnglobantCourant());
	}
	// Calculer la position des coins du quad.
	utilitaire::QuadEnglobant quad = noeud->obtenirQuadEnglobantModele();
	glm::dvec3 tmp;
	for (int i = 0; i < quad.N_COINS; i++)
	{
		quad.coins[i].x *= noeud->obtenirFacteurMiseAEchelle();
		tmp = quad.coins[i];
		utilitaire::calculerPositionApresRotation(tmp, quad.coins[i], noeud->obtenirAngleRotation());
		quad.coins[i] += (positionVirtuelleParent + noeud->obtenirPositionRelative());
	}
	noeud->assignerQuadEnglobantCourant(quad);
}


void VisiteurMiseAJourQuad::visiter(NoeudJonction* noeud)
{
	glm::dvec3 positionVirtuelleParent = { 0.0, 0.0, 0.0 };	
	NoeudAbstrait* parent = noeud->obtenirParent();
	// Calculer la position virtuelle du parent.
	if (parent != nullptr)
	{
		positionVirtuelleParent = calculerPositionVirtuelle(parent->obtenirQuadEnglobantCourant());
	}
	// Calculer la position des coins du quad.
	utilitaire::QuadEnglobant quad = noeud->obtenirQuadEnglobantModele();
	glm::dvec3 tmp;
	for (int i = 0; i < quad.N_COINS; i++)
	{
		quad.coins[i] += (positionVirtuelleParent + noeud->obtenirPositionRelative());
	}
	noeud->assignerQuadEnglobantCourant(quad);
}

void VisiteurMiseAJourQuad::visiter(NoeudDepart* noeud)
{
	glm::dvec3 positionVirtuelleParent = { 0.0, 0.0, 0.0 };	
	NoeudAbstrait* parent = noeud->obtenirParent();
	// Calculer la position virtuelle du parent.
	if (parent != nullptr)
	{
		positionVirtuelleParent = calculerPositionVirtuelle(parent->obtenirQuadEnglobantCourant());
	}
	// Calculer la position des coins du quad.
	utilitaire::QuadEnglobant quad = noeud->obtenirQuadEnglobantModele();
	glm::dvec3 tmp;
	for (int i = 0; i < quad.N_COINS; i++)
	{
		tmp = quad.coins[i];
		utilitaire::calculerPositionApresRotation(tmp, quad.coins[i], noeud->obtenirAngleRotation());
		quad.coins[i] += positionVirtuelleParent + noeud->obtenirPositionRelative();
	}
	noeud->assignerQuadEnglobantCourant(quad);
}
///TODO: A mettre dans utilitaire.
glm::dvec3 VisiteurMiseAJourQuad::calculerPositionVirtuelle(const utilitaire::QuadEnglobant& quad)
{
	glm::dvec3 positionVirtuelle = { 0.0, 0.0, 0.0 };
	for (int i = 0; i < quad.N_COINS; i++)
	{
		positionVirtuelle += quad.coins[i];
	}
	return positionVirtuelle /= quad.N_COINS;
}