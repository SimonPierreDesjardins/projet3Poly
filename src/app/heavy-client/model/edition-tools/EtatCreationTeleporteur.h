///////////////////////////////////////////////////////////////////////////
/// @file EtatCreationTeleporteur.h
/// @author Simon-Pierre Desjardins
/// @date 2017-03-08
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef ETAT_CREATION_TELEPORTEUR_H
#define ETAT_CREATION_TELEPORTEUR_H

#include "EtatAbstrait.h"
#include "VisiteurTypes.h"
#include <iostream>

///////////////////////////////////////////////////////////////////////////
/// @class EtatCreationTeleporteur
/// @brief �tat repr�sentant la creation d'un teleporteur
///
/// @author Simon-Pierre Desjardins
/// @date 2017-03-08
///////////////////////////////////////////////////////////////////////////
class EtatCreationTeleporteur : public EtatAbstrait
{
public:
	EtatCreationTeleporteur();
	virtual ~EtatCreationTeleporteur();

	virtual void gererClicGaucheEnfonce(const int& x, const int& y);
	virtual void gererClicGaucheRelache(const int& x, const int& y);
	virtual void gererMouvementSouris(const int& x, const int& y);
	virtual void gererPositionCurseurConcret(const bool& positionEstSurTable);
	virtual void assignerSymboleCurseur();
	virtual void gererToucheEchappe();

	bool isInCreation() { return enCreation_; };

private:
	std::unique_ptr<VisiteurCreationTeleporteur> visiteurCreationTeleporteur_{ nullptr };
	std::unique_ptr<VisiteurVerificationQuad> visiteurVerificationQuad_{ nullptr };
	int compteurTeleporteur_;
	bool enCreation_{false};
	std::shared_ptr<NoeudAbstrait> teleporteur_;
	NoeudAbstrait* ancienTeleporteur_;
	NoeudAbstrait* teleporteurTemp;
};


#endif

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
