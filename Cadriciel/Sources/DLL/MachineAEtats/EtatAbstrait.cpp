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
#include "FacadeModele.h"
#include "Vue.h"
#include "Projection.h"

glm::ivec2 EtatAbstrait::currentPosition_ = { 0.0, 0.0 };


////////////////////////////////////////////////////////////////////////
///
/// @fn EtatAbstrait::EtatAbstrait()
///
/// Constructeur par défault. Assigne arbre_ à arbre courant
///
////////////////////////////////////////////////////////////////////////
EtatAbstrait::EtatAbstrait()
{
	arbre_ = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
	vue_ = FacadeModele::obtenirInstance()->obtenirVue();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn EtatAbstrait::~EtatAbstrait()
///
/// Destructeur par défault
///
////////////////////////////////////////////////////////////////////////
EtatAbstrait::~EtatAbstrait()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatAbstrait::gererClicDroitEnfonce(const int& x, const int& y)
///
/// Cette fonction assigne un booléan à true si le bouton droit de la souris est
/// appuyé.
///
/// @param const int& x: position en x du cursor
/// @param const int& y: position en y du cursor
///
////////////////////////////////////////////////////////////////////////
void EtatAbstrait::gererClicDroitEnfonce(const int& x, const int& y)
{
	clicDroitEnfonce_ = true;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatAbstrait::gererClicDroitRelache(const int& x, const int& y)
///
/// Cette fonction assigne un booléan à false si le bouton droit de la souris est
/// relâché.
///
/// @param const int& x: position en x du cursor
/// @param const int& y: position en y du cursor
///
////////////////////////////////////////////////////////////////////////
void EtatAbstrait::gererClicDroitRelache(const int& x, const int& y)
{
	clicDroitEnfonce_ = false;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatAbstrait::gererClicGaucheEnfonce(const int& x, const int& y)
///
/// Cette fonction assigne un booléan à true si le bouton gauche de la souris est
/// appuyé et sauvegarde la position courante.
///
/// @param const int& x: position en x du cursor
/// @param const int& y: position en y du cursor
///
////////////////////////////////////////////////////////////////////////
void EtatAbstrait::gererClicGaucheEnfonce(const int& x, const int& y)
{
	clicGaucheEnfonce_ = true;
	anchor = glm::ivec2(x, y);
	currentPosition_ = anchor;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatAbstrait::gererClicGaucheRelache(const int& x, const int& y)
///
/// Cette fonction assigne un booléan à false si le bouton gauche de la souris est
/// relâché.
///
/// @param const int& x: position en x du cursor
/// @param const int& y: position en y du cursor
///
////////////////////////////////////////////////////////////////////////
void EtatAbstrait::gererClicGaucheRelache(const int& x, const int& y)
{
	clicGaucheEnfonce_ = false;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatAbstrait::gererMouvementSouris(const int & x, const int& y)
///
/// Cette fonction gère les mouvements de la souris. Si le clique droit est enfoncé
/// on peux déplacer la caméra, sinon rien
///
/// @param const int& x: position en x du cursor
/// @param const int& y: position en y du cursor
///
////////////////////////////////////////////////////////////////////////
void EtatAbstrait::gererMouvementSouris(const int & x, const int& y)
{
	if (clicDroitEnfonce_) {
		if (FacadeModele::obtenirInstance()->obtenirVue()->obtenirProjection().estPerspective()) {
			FacadeModele::obtenirInstance()->obtenirVue()->rotaterXY(glm::ivec2(-(x - currentPosition_.x), y - currentPosition_.y));
		}
		else {
			FacadeModele::obtenirInstance()->obtenirVue()->deplacerXY(glm::ivec2(-(x - currentPosition_.x), y - currentPosition_.y));
		}
	}
	currentPosition_ = glm::ivec2(x, y);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool EtatAbstrait::estClickDrag()
///
/// Cette fonction vérifie si le point d'origine et le point final d'un clique
/// est à plus de trois pixels
///
////////////////////////////////////////////////////////////////////////
bool EtatAbstrait::estClickDrag()
{
	return (std::abs(currentPosition_.x - anchor.x) > 3 || std::abs(currentPosition_.y - anchor.y) > 3);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatAbstrait::gererToucheEchappe()
///
/// Cette fonction gère la touche Escape
///
////////////////////////////////////////////////////////////////////////
void EtatAbstrait::gererToucheEchappe()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatAbstrait::gererToucheControlEnfoncee()
///
/// Cette fonction gère la touche Control enfoncee
///
////////////////////////////////////////////////////////////////////////
void EtatAbstrait::gererToucheControlEnfoncee()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatAbstrait::gererToucheControlRelachee()
///
/// Cette fonction gère la touche Control relâchée
///
////////////////////////////////////////////////////////////////////////
void EtatAbstrait::gererToucheControlRelachee()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatAbstrait::gererToucheAltEnfoncee()
///
/// Cette fonction gère la touche Alt enfoncee
///
////////////////////////////////////////////////////////////////////////
void EtatAbstrait::gererToucheAltEnfoncee()
{
	toucheAltEnfonce_ = true;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatAbstrait::gererToucheAltRelachee()
///
/// Cette fonction gère la touche Alt relâchée
///
////////////////////////////////////////////////////////////////////////
void EtatAbstrait::gererToucheAltRelachee()
{
	toucheAltEnfonce_ = false;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatAbstrait::gererTouchePlus()
///
/// Cette fonction gère la touche +=, permet de faire un zoom avant.
///
////////////////////////////////////////////////////////////////////////
void EtatAbstrait::gererTouchePlus(){
	if (FacadeModele::obtenirInstance()->obtenirVue()->obtenirProjection().estPerspective()) {
		//TODO: Gérer le zoom plus pour une camera
	}
	else {
		FacadeModele::obtenirInstance()->obtenirVue()->zoomerIn();
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatAbstrait::gererToucheMoins()
///
/// Cette fonction gère la touche -=, permet de faire un zoom arrière.
///
////////////////////////////////////////////////////////////////////////
void EtatAbstrait::gererToucheMoins(){
	if (FacadeModele::obtenirInstance()->obtenirVue()->obtenirProjection().estPerspective()) {
		//TODO: Gérer le zoom moins pour une camera
	}
	else {
		FacadeModele::obtenirInstance()->obtenirVue()->zoomerOut();
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatAbstrait::gererPositionCurseur(const glm::dvec3& position)
///
/// Cette fonction vérifie que le curseur est sur la table 
/// et appel la méthode concrète.
///
/// @param const glm::dvec3& position: position de la souris
///
////////////////////////////////////////////////////////////////////////
void EtatAbstrait::gererPositionCurseur(const glm::dvec3& position)
{
	const int MIN_X = -48;
	const int MAX_X =  48;
	const int MIN_Y = -24;
	const int MAX_Y =  24;
	bool positionEstSurTable = (MIN_X <= position.x && position.x <= MAX_X && MIN_Y <= position.y && position.y <= MAX_Y);

	gererPositionCurseurConcret(positionEstSurTable);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatAbstrait::gererPositionCurseurConcret(const bool& positionEstSurTable)
///
/// Implémentation concrète de la gestion de la position du curseur. Il s'agit 
/// d'une méthode implémentée par les classes dérivées.
///
/// @param bool positionEstSurTable: True si la souris est sur la table sinon false
///
////////////////////////////////////////////////////////////////////////
void EtatAbstrait::gererPositionCurseurConcret(const bool& positionEstSurTable)
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatAbstrait::assignerSymbolePointeur(bool estSymboleStandard)
///
/// Cette fonction assigne l'image du curseur.
///
////////////////////////////////////////////////////////////////////////
void EtatAbstrait::assignerSymboleCurseur()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatAbstrait::reinitialiser()
///
////////////////////////////////////////////////////////////////////////
void EtatAbstrait::reinitialiser()
{
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////

