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
#include "FacadeModele.h"
#include <iostream>


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurMiseAJourQuad::VisiteurMiseAJourQuad()
///
/// Constructeur
///
/// @param[in] Aucun
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurMiseAJourQuad::VisiteurMiseAJourQuad()
{
	arbre_ = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
	table_ = arbre_->chercher(0);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurMiseAJourQuad::~VisiteurMiseAJourQuad()
///
/// Destructeur
///
/// @param[in] Aucun
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurMiseAJourQuad::~VisiteurMiseAJourQuad()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurMiseAJourQuad::visiter(ArbreRendu* noeud)
///
/// Fonction servant � donner l'acc�s au noeud Table.
///
/// @param[in] noeud : l'arbre rendu contenant le noeud Table, entre autres.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurMiseAJourQuad::visiter(ArbreRendu* noeud)
{
	table_->accepterVisiteur(this);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurMiseAJourQuad::visiter(NoeudTable* noeud)
///
/// Fonction servant � donner l'acc�s aux enfants du noeud Table.
///
/// @param[in] noeud : Le noeud Table contenant les enfants auxquels on veut avoir acc�s.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurMiseAJourQuad::visiter(NoeudTable* noeud)
{
	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++) {
		noeud->chercher(i)->accepterVisiteur(this);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurMiseAJourQuad::visiter(NoeudDuplication* noeud)
///
/// Fonction qui met � jour le quadrilat�re contenant les noeuds que l'on duplique.
///
/// @param[in] noeud : Le noeud Duplication contenant les noeuds que l'on veut dupliquer.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurMiseAJourQuad::visiter(NoeudDuplication* noeud)
{
	glm::dvec3 positionVirtuelleParent = { 0.0, 0.0, 0.0 };	
	NoeudAbstrait* parent = noeud->obtenirParent();
	if (parent != nullptr) {
		positionVirtuelleParent = calculerPositionVirtuelle(parent->obtenirQuadEnglobantCourant());
	}

	/// Mettre � jour le quad de la duplication.
	utilitaire::QuadEnglobant quad;
	for (int i = 0; i < quad.N_COINS; i++) {
		quad.coins[i] = positionVirtuelleParent + noeud->obtenirPositionRelative();
	}

	noeud->assignerQuadEnglobantCourant(quad);
	/// Mettre � jour le quad des enfants.
	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++) {
		noeud->chercher(i)->accepterVisiteur(this);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurMiseAJourQuad::visiter(NoeudPoteau* noeud)
///
/// Fonction qui met � jour le quadrilat�re du poteau pass� en param�tre.
///
/// @param[in] noeud : Le noeud Poteau que l'on veut mettre � jour.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurMiseAJourQuad::visiter(NoeudPoteau* noeud)
{
	glm::dvec3 positionVirtuelleParent = { 0.0, 0.0, 0.0 };	
	NoeudAbstrait* parent = noeud->obtenirParent();
	// Calculer la position virtuelle du parent.
	if (parent != nullptr) {
		positionVirtuelleParent = calculerPositionVirtuelle(parent->obtenirQuadEnglobantCourant());
	}
	// Calculer la position des coins du quad.
	utilitaire::QuadEnglobant quad = noeud->obtenirQuadEnglobantModele();

	for (int i = 0; i < quad.N_COINS; i++) {
		quad.coins[i] *= noeud->obtenirFacteurMiseAEchelle();
		quad.coins[i] += (positionVirtuelleParent + noeud->obtenirPositionRelative());
	}
	noeud->assignerQuadEnglobantCourant(quad);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurMiseAJourQuad::visiter(NoeudMur* noeud)
///
/// Fonction qui met � jour le quadrilat�re du mur pass� en param�tre.
///
/// @param[in] noeud : Le noeud Mur que l'on veut mettre � jour.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurMiseAJourQuad::visiter(NoeudMur* noeud)
{
	glm::dvec3 positionVirtuelleParent = { 0.0, 0.0, 0.0 };	
	NoeudAbstrait* parent = noeud->obtenirParent();
	// Calculer la position virtuelle du parent.
	if (parent != nullptr) {
		positionVirtuelleParent = calculerPositionVirtuelle(parent->obtenirQuadEnglobantCourant());
	}

	utilitaire::QuadEnglobant quad = noeud->obtenirQuadEnglobantModele();
    double largeur = glm::abs(quad.coins[0].x - quad.coins[1].x);
    double hauteur = glm::abs(quad.coins[0].y - quad.coins[3].y);

    double facteurMiseAEchelle = noeud->obtenirFacteurMiseAEchelle();
    largeur *= facteurMiseAEchelle;

	// Calculer la position des coins du quad.
	glm::dvec3 tmp = { 0.0, 0.0, 0.0 };
	for (int i = 0; i < quad.N_COINS; i++) {
		quad.coins[i].x *= noeud->obtenirFacteurMiseAEchelle();
		tmp = quad.coins[i];
		utilitaire::calculerPositionApresRotation(tmp, quad.coins[i], noeud->obtenirAngleRotation());
		quad.coins[i] += (positionVirtuelleParent + noeud->obtenirPositionRelative());
	}
	noeud->assignerQuadEnglobantCourant(quad);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurMiseAJourQuad::visiter(NoeudLigne* noeud)
///
/// Fonction qui met � jour le quadrilat�re de la ligne pass�e en param�tre.
///
/// @param[in] noeud : Le noeud Ligne que l'on veut mettre � jour.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurMiseAJourQuad::visiter(NoeudLigne* noeud)
{
	glm::dvec3 positionVirtuelleParent = { 0.0, 0.0, 0.0 };	
	NoeudAbstrait* parent = noeud->obtenirParent();
	if (parent != nullptr) {
		positionVirtuelleParent = calculerPositionVirtuelle(parent->obtenirQuadEnglobantCourant());
	}

	/// Mettre � jour le quad de la duplication.
	utilitaire::QuadEnglobant quad;
	for (int i = 0; i < quad.N_COINS; i++) {
		quad.coins[i] = positionVirtuelleParent + noeud->obtenirPositionRelative();
	}
	noeud->assignerQuadEnglobantCourant(quad);

	/// Mettre � jour le quad des enfants.
	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++) {
		noeud->chercher(i)->accepterVisiteur(this);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurMiseAJourQuad::visiter(NoeudSegment* noeud)
///
/// Fonction qui met � jour le quadrilat�re du segment pass� en param�tre.
///
/// @param[in] noeud : Le noeud Segment que l'on veut mettre � jour.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurMiseAJourQuad::visiter(NoeudSegment* noeud)
{
	glm::dvec3 positionVirtuelleParent = { 0.0, 0.0, 0.0 };	
	NoeudAbstrait* parent = noeud->obtenirParent();
	// Calculer la position virtuelle du parent.
	if (parent != nullptr) {
		positionVirtuelleParent = calculerPositionVirtuelle(parent->obtenirQuadEnglobantCourant());
	}

	utilitaire::QuadEnglobant quad = noeud->obtenirQuadEnglobantModele();

    // Mise � jour du quad.
	glm::dvec3 tmp = { 0.0, 0.0, 0.0 };
	for (int i = 0; i < quad.N_COINS; i++) {
		quad.coins[i].x *= noeud->obtenirFacteurMiseAEchelle();
		tmp = quad.coins[i];
		utilitaire::calculerPositionApresRotation(tmp, quad.coins[i], noeud->obtenirAngleRotation());
		quad.coins[i] += (positionVirtuelleParent + noeud->obtenirPositionRelative());
	}
	noeud->assignerQuadEnglobantCourant(quad);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurMiseAJourQuad::visiter(NoeudJonction* noeud)
///
/// Fonction qui met � jour le quadrilat�re de la jonction pass�e en param�tre.
///
/// @param[in] noeud : Le noeud Jonction que l'on veut mettre � jour.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurMiseAJourQuad::visiter(NoeudJonction* noeud)
{
	glm::dvec3 positionVirtuelleParent = { 0.0, 0.0, 0.0 };	
	NoeudAbstrait* parent = noeud->obtenirParent();
	// Calculer la position virtuelle du parent.
	if (parent != nullptr) {
		positionVirtuelleParent = calculerPositionVirtuelle(parent->obtenirQuadEnglobantCourant());
	}

	utilitaire::QuadEnglobant quad = noeud->obtenirQuadEnglobantModele();

	// Calculer la position des coins du quad.
	glm::dvec3 tmp;
	for (int i = 0; i < quad.N_COINS; i++) {
		quad.coins[i] += (positionVirtuelleParent + noeud->obtenirPositionRelative());
	}
	noeud->assignerQuadEnglobantCourant(quad);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurMiseAJourQuad::visiter(NoeudDepart* noeud)
///
/// Fonction qui met � jour le quadrilat�re de la fl�che de d�part pass�e en param�tre.
///
/// @param[in] noeud : Le noeud Depart que l'on veut mettre � jour.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurMiseAJourQuad::visiter(NoeudDepart* noeud)
{
	glm::dvec3 positionVirtuelleParent = { 0.0, 0.0, 0.0 };	
	NoeudAbstrait* parent = noeud->obtenirParent();
	// Calculer la position virtuelle du parent.
	if (parent != nullptr) {
		positionVirtuelleParent = calculerPositionVirtuelle(parent->obtenirQuadEnglobantCourant());
	}


	utilitaire::QuadEnglobant quad = noeud->obtenirQuadEnglobantModele();

	glm::dvec3 tmp = { 0.0, 0.0, 0.0 };
	for (int i = 0; i < quad.N_COINS; i++) {
		tmp = quad.coins[i];
		utilitaire::calculerPositionApresRotation(tmp, quad.coins[i], noeud->obtenirAngleRotation());
		quad.coins[i] += positionVirtuelleParent + noeud->obtenirPositionRelative();
	}
	noeud->assignerQuadEnglobantCourant(quad);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurMiseAJourQuad::visiter(NoeudRobot* noeud)
///
/// Fonction qui met � jour le quadrilat�re du robot pass�e en param�tre.
///
/// @param[in] noeud : Le noeud Robot que l'on veut mettre � jour.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////

void VisiteurMiseAJourQuad::visiter(NoeudRobot* noeud)
{
	utilitaire::QuadEnglobant quad = noeud->obtenirQuadEnglobantModele();

    // Mise � jour du quad englobant.
	glm::dvec3 tmp = { 0.0, 0.0, 0.0 };
	for (int i = 0; i < quad.N_COINS; i++) {
		tmp = quad.coins[i];
		utilitaire::calculerPositionApresRotation(tmp, quad.coins[i], noeud->obtenirAngleRotation());
		quad.coins[i] += noeud->obtenirPositionRelative();
	}
	noeud->assignerQuadEnglobantCourant(quad);
	//noeud->mettreAJourCapteurs();
}

///TODO: A mettre dans utilitaire.

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurMiseAJourQuad::calculerPositionVirtuelle(const utilitaire::QuadEnglobant& quad)
///
/// Fonction qui calcule la position virtuelle du quad englobant.
///
/// @param[in] quad : Le le quad englobant que l'on veut calculer la position virtuelle.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
glm::dvec3 VisiteurMiseAJourQuad::calculerPositionVirtuelle(const utilitaire::QuadEnglobant& quad)
{
	glm::dvec3 positionVirtuelle = { 0.0, 0.0, 0.0 };
	for (int i = 0; i < quad.N_COINS; i++) {
		positionVirtuelle += quad.coins[i];
	}
	return positionVirtuelle /= quad.N_COINS;
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////