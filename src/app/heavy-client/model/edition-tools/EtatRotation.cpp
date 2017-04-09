///////////////////////////////////////////////////////////////////////////
/// @file EtatRotation.cpp
/// @author 
/// @date 2016-01-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#include "FacadeModele.h"
#include "EtatRotation.h"
#include "VisiteurRotation.h"
#include "ArbreRenduINF2990.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn EtatRotation::EtatRotation()
///
/// Constructeur par défault
///
////////////////////////////////////////////////////////////////////////
EtatRotation::EtatRotation(client_network::ClientMapSession* mapSession)
	: OnlineTool(mapSession)
{
	setType(ROTATION);
	visiteurRotation_ = std::make_unique<VisiteurRotation>(mapSession);
	visiteurVerificationQuad_ = std::make_unique<VisiteurVerificationQuad>();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn EtatRotation::~EtatRotation()
///
/// Destructeur par défault
///
////////////////////////////////////////////////////////////////////////
EtatRotation::~EtatRotation()
{
	if (clicGaucheEnfonce_) {
		reinitialiser();
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatRotation::gererClicGaucheEnfonce(const int& x, const int& y)
///
/// Cette fonction assigne un booléan à true si le bouton gauche de la souris est
/// appuyé et sauvegarde la position courante.
///
/// @param const int& x: position en x du cursor
/// @param const int& y: position en y du cursor
///
////////////////////////////////////////////////////////////////////////
void EtatRotation::gererClicGaucheEnfonce(const int& x, const int& y)
{
	clicGaucheEnfonce_ = true;
	dernierePositionY_ = y;
	positionInitialeY_ = y;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatRotation::gererClicGaucheRelache(const int& x, const int& y)
///
/// Cette fonction assigne un angle de rotation à l'objet s'il est toujours sur
/// la table. Sinon il est remis à sa position initiale.
///
/// @param const int& x: position en x du cursor
/// @param const int& y: position en y du cursor
///
////////////////////////////////////////////////////////////////////////
void EtatRotation::gererClicGaucheRelache(const int& x, const int& y)
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
/// @fn void EtatRotation::gererMouvementSouris(const int& x, const int& y)
///
/// Cette fonction change l'attribut angle de rotation avec le position en y de la 
/// souris lorsque le clique gauche est appuyé.
///
/// @param const int& x: position en x du cursor
/// @param const int& y: position en y du cursor
///
////////////////////////////////////////////////////////////////////////
void EtatRotation::gererMouvementSouris(const int& x, const int& y)
{
	EtatAbstrait::gererMouvementSouris(x, y);
	if (clicGaucheEnfonce_) {
		visiteurRotation_->assignerAngleRotation((double)(y - dernierePositionY_));
		visiteurRotation_->rotateSelectedObjects(arbre_);
		dernierePositionY_ = y;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatRotation::reinitialiser()
///
/// Remet l'objet à sson angle original.
///
////////////////////////////////////////////////////////////////////////
void EtatRotation::reinitialiser()
{
	visiteurRotation_->assignerAngleRotation((double)(positionInitialeY_- dernierePositionY_));
	visiteurRotation_->rotateSelectedObjects(arbre_);
}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////