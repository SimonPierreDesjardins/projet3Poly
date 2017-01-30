///////////////////////////////////////////////////////////////////////////
/// @file EtatMiseAEchelle.cpp
/// @author Olivier St-Amour
/// @date 2016-01-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#include "EtatMiseAEchelle.h"
#include "VisiteurTypes.h"
#include "FacadeModele.h"
#include <cmath>

////////////////////////////////////////////////////////////////////////
///
/// @fn EtatMiseAEchelle::EtatMiseAEchelle()
///
/// Constructeur par d�fault
///
////////////////////////////////////////////////////////////////////////
EtatMiseAEchelle::EtatMiseAEchelle()
{
	visiteurMiseAEchelle_ = std::make_unique<VisiteurMiseAEchelle>();
	visiteurVerificationQuad_ = std::make_unique<VisiteurVerificationQuad>();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn EtatMiseAEchelle::~EtatMiseAEchelle()
///
/// Destructeur par d�fault
///
////////////////////////////////////////////////////////////////////////
EtatMiseAEchelle::~EtatMiseAEchelle()
{
	if (clicGaucheEnfonce_) {
		visiteurMiseAEchelle_->reinitialiser(arbre_);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatMiseAEchelle::gererClicGaucheEnfonce(const int& x, const int& y)
///
/// Cette fonction sauvegarde l'emplacement du clique
///
/// @param const int& x: position en x du cursor
/// @param const int& y: position en y du cursor
///
////////////////////////////////////////////////////////////////////////
void EtatMiseAEchelle::gererClicGaucheEnfonce(const int& x, const int& y)
{
	clicGaucheEnfonce_ = true;
	glm::dvec3 positionVirtuelle = { 0.0, 0.0, 0.0 };
	vue_->convertirClotureAVirtuelle(x, y, positionVirtuelle);
	dernierePositionY_ = positionVirtuelle.y;
	positionInitialeY_ = positionVirtuelle.y;
	visiteurMiseAEchelle_->initialiser(arbre_);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatMiseAEchelle::gererClicGaucheRelache(const int& x, const int& y)
///
/// Cette fonction assigne le facteur mise � �chelle si l'objet est encore dans
/// la zone de cr�ation.
///
/// @param const int& x: position en x du cursor
/// @param const int& y: position en y du cursor
///
////////////////////////////////////////////////////////////////////////
void EtatMiseAEchelle::gererClicGaucheRelache(const int& x, const int& y)
{
	clicGaucheEnfonce_ = false;
	glm::dvec3 positionVirtuelle = { 0.0, 0.0, 0.0 };
	vue_->convertirClotureAVirtuelle(x, y, positionVirtuelle);
	dernierePositionY_ = positionVirtuelle.y;

	if (arbre_ != nullptr) {
		arbre_->accepterVisiteur(visiteurVerificationQuad_.get());
	}
	if (!visiteurVerificationQuad_->objetsDansZoneSimulation()) {
		visiteurMiseAEchelle_->reinitialiser(arbre_);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatMiseAEchelle::gererMouvementSouris(const int& x, const int& y)
///
/// Cette fonction change le facteur de dimension en fonction de la position
/// actuelle de la souris. Si le bouton gauche n'est pas appuy�, rien.
///
/// @param const int& x: position en x du cursor
/// @param const int& y: position en y du cursor
///
////////////////////////////////////////////////////////////////////////
void EtatMiseAEchelle::gererMouvementSouris(const int& x, const int& y)
{
	EtatAbstrait::gererMouvementSouris(x, y);

	if (clicGaucheEnfonce_) {
		glm::dvec3 positionVirtuelle = { 0.0, 0.0, 0.0 };
		vue_->convertirClotureAVirtuelle(x, y, positionVirtuelle);

		visiteurMiseAEchelle_->assignerFacteurMiseAEchelle(positionVirtuelle.y - dernierePositionY_);
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepterVisiteur(visiteurMiseAEchelle_.get());

		dernierePositionY_ = positionVirtuelle.y;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatMiseAEchelle::reinitialiser()
///
/// Remet l'objet � sa dimension originale
///
////////////////////////////////////////////////////////////////////////
void EtatMiseAEchelle::reinitialiser()
{
	visiteurMiseAEchelle_->assignerFacteurMiseAEchelle(positionInitialeY_ - dernierePositionY_);
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepterVisiteur(visiteurMiseAEchelle_.get());
}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////