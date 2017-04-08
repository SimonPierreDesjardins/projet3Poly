///////////////////////////////////////////////////////////////////////////
/// @file EtatCreationPoteau.h
/// @author 
/// @date 2016-01-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef ETAT_CREATION_POTEAU_H
#define ETAT_CREATION_POTEAU_H

#include "OnlineTool.h"
#include "VisiteurTypes.h"
#include <iostream>

///////////////////////////////////////////////////////////////////////////
/// @class EtatCreationPoteau
/// @brief État représentant la creation d'un poteau
///
/// @author Frédéric Grégoire
/// @date 2016-02-15
///////////////////////////////////////////////////////////////////////////
class EtatCreationPoteau : public OnlineTool
{
public:
	EtatCreationPoteau(client_network::ClientMapSession* mapSession);
	virtual ~EtatCreationPoteau();

	virtual void gererClicGaucheEnfonce(const int& x, const int& y);
	virtual void gererClicGaucheRelache(const int& x, const int& y);
	virtual void gererMouvementSouris(const int& x, const int& y);
	virtual void gererPositionCurseurConcret(const bool& positionEstSurTable);
	virtual void assignerSymboleCurseur();

private:
	std::unique_ptr<VisiteurCreationPoteau> visiteurCreationPoteau_{ nullptr };
	std::unique_ptr<VisiteurVerificationQuad> visiteurVerificationQuad_{ nullptr };

	EtatCreationPoteau() = delete;
};


#endif

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
