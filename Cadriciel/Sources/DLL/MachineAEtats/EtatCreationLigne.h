///////////////////////////////////////////////////////////////////////////
/// @file EtatCreationLigne.h
/// @author 
/// @date 2016-01-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef ETAT_CREATION_LIGNE_H
#define ETAT_CREATION_LIGNE_H

#include "EtatAbstrait.h"
#include "VisiteurTypes.h"
#include <iostream>
#include <vector>

///////////////////////////////////////////////////////////////////////////
/// @class EtatCreationLigne
/// @brief État représentant la creation d'une ligne
///
/// @author Frédéric Grégoire
/// @date 2016-02-15
///////////////////////////////////////////////////////////////////////////
class EtatCreationLigne: public EtatAbstrait
{
public:
	EtatCreationLigne();
	virtual ~EtatCreationLigne();

	virtual void gererClicGaucheRelache(const int& x, const int& y);
	virtual void gererMouvementSouris(const int& x, const int& y);
	virtual void gererToucheEchappe();
	virtual void gererToucheControlEnfoncee();
	virtual void gererToucheControlRelachee();
	virtual void gererPositionCurseurConcret(const bool& positionEstSurTable);
	virtual void assignerSymboleCurseur();

private:
	std::unique_ptr<VisiteurCreationLigne> visiteurCreationLigne_{ nullptr };
	std::unique_ptr<VisiteurVerificationQuad> visiteurVerificationQuad_{ nullptr };
	std::unique_ptr<VisiteurMiseAJourQuad> visiteurMiseAJourQuad_{ nullptr };
		
	NoeudAbstrait* ligne_{ nullptr };
	NoeudAbstrait* segment_{ nullptr };
	bool enCreation_{ false };
	std::vector<glm::dvec3> positionsClic_;

	void calculerPositionCentreLigne();
	bool ligneEstSurTable();
};

#endif /// ETAT_CREATION_LIGNE_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
