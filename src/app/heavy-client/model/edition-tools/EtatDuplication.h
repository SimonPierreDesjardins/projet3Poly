///////////////////////////////////////////////////////////////////////////
/// @file EtatDuplication.h
/// @author 
/// @date 2016-01-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef ETAT_DUPLICATION_H
#define ETAT_DUPLICATION_H

#include "OnlineTool.h"
#include "VisiteurDuplication.h"
#include "VisiteurDeplacement.h"
#include "VisiteurVerificationQuad.h"
#include "VisiteurSuppression.h"

///////////////////////////////////////////////////////////////////////////
/// @class EtatDuplication
/// @brief État représentant la duplication d'un objet
///
/// @author Frédéric Grégoire
/// @date 2016-02-15
///////////////////////////////////////////////////////////////////////////
class EtatDuplication : public OnlineTool
{
public:
	EtatDuplication(client_network::MapSession* mapSession);

	virtual ~EtatDuplication();
	virtual void gererClicGaucheRelache(const int& x, const int& y);
	virtual void gererMouvementSouris(const int& x, const int& y);
	virtual void gererPositionCurseurConcret(const bool& positionEstSurTable);
	virtual void assignerSymboleCurseur();

private:
	VisiteurVerificationQuad visiteurVerificationQuad_;
	VisiteurDuplication visiteurDuplication_;
	VisiteurDeplacement visiteurDeplacement_;
	VisiteurSuppression visiteurSuppression_;

	NoeudAbstrait* duplication_{ nullptr };
	bool enDuplication_{ false };
};

#endif

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
