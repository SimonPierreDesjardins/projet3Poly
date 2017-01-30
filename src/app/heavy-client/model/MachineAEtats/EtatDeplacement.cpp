///////////////////////////////////////////////////////////////////////////
/// @file EtatDeplacement.cpp
/// @author 
/// @date 2016-01-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#include "EtatDeplacement.h"
#include "VisiteurDeplacement.h"
#include "VisiteurVerificationQuad.h"
#include "FacadeModele.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn EtatDeplacement::EtatDeplacement()
///
/// Constructeur par d�fault
///
////////////////////////////////////////////////////////////////////////
EtatDeplacement::EtatDeplacement()
{
	visiteurDeplacement_ = std::make_unique<VisiteurDeplacement>();
	visiteurVerificationQuad_ = std::make_unique<VisiteurVerificationQuad>();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn EtatDeplacement::~EtatDeplacement()
///
/// Destructeur par d�fault
///
////////////////////////////////////////////////////////////////////////
EtatDeplacement::~EtatDeplacement()
{
	if (clicGaucheEnfonce_) {
		reinitialiser();
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatDeplacement::gererClicGaucheEnfonce(const int& x, const int& y)
///
/// Cette fonction d�place un objet s'il est s�lectionn� tant que le clique gauche
/// est enfonc�
///
/// @param const int& x: position en x du cursor
/// @param const int& y: position en y du cursor
///
////////////////////////////////////////////////////////////////////////
void EtatDeplacement::gererClicGaucheEnfonce(const int& x, const int& y)
{
	clicGaucheEnfonce_ = true;
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, dernierePositionVirtuelle_);
	positionVirtuelleInitiale_ = dernierePositionVirtuelle_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatDeplacement::gererClicGaucheRelache(const int& x, const int& y)
///
/// Cette fonction assigne la nouvelle position de l'objet s'il est sur la table.
/// Sinon il est replac� � sa position originale.
///
/// @param const int& x: position en x du cursor
/// @param const int& y: position en y du cursor
///
////////////////////////////////////////////////////////////////////////
void EtatDeplacement::gererClicGaucheRelache(const int& x, const int& y)
{
	clicGaucheEnfonce_ = false;
	if (arbre_ != nullptr) {
		arbre_->accepterVisiteur(visiteurVerificationQuad_.get());
	}
	if (!visiteurVerificationQuad_->objetsDansZoneSimulation()) {
		reinitialiser();
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatDeplacement::gererMouvementSouris(const int& x, const int& y)
///
/// Cette fonction change les attributs de position X et Y d'un objet en fonction de la 
/// position du curseur
///
/// @param const int& x: position en x du cursor
/// @param const int& y: position en y du cursor
///
////////////////////////////////////////////////////////////////////////
void EtatDeplacement::gererMouvementSouris(const int& x, const int& y)
{
	EtatAbstrait::gererMouvementSouris(x, y);
	glm::dvec3 positionVirtuelle;
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, positionVirtuelle);
	
	if (clicGaucheEnfonce_) {
		visiteurDeplacement_->assignerPositionRelative(positionVirtuelle - dernierePositionVirtuelle_);
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepterVisiteur(visiteurDeplacement_.get());
		dernierePositionVirtuelle_ = positionVirtuelle;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatDeplacement::reinitialiser()
///
/// Cette fonction remet les attributs initials � un objet
///
////////////////////////////////////////////////////////////////////////
void EtatDeplacement::reinitialiser()
{
	visiteurDeplacement_->assignerPositionRelative(positionVirtuelleInitiale_ - dernierePositionVirtuelle_);
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepterVisiteur(visiteurDeplacement_.get());
}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////