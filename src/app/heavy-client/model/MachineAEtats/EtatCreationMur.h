///////////////////////////////////////////////////////////////////////////
/// @file EtatCreationMur.h
/// @author 
/// @date 2016-01-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef ETAT_CREATION_MUR_H
#define ETAT_CREATION_MUR_H

#include "EtatAbstrait.h"
#include "VisiteurTypes.h"
#include <iostream>

///////////////////////////////////////////////////////////////////////////
/// @class EtatCreationMur
/// @brief �tat repr�sentant la creation d'un mur
///
/// @author Fr�d�ric Gr�goire
/// @date 2016-02-15
///////////////////////////////////////////////////////////////////////////
class EtatCreationMur : public EtatAbstrait
{
public:
	EtatCreationMur();
	virtual ~EtatCreationMur();

	virtual void gererClicGaucheEnfonce(const int& x, const int& y);
	virtual void gererClicGaucheRelache(const int& x, const int& y);
	virtual void gererMouvementSouris(const int& x, const int&y);
	virtual void gererToucheEchappe();
	virtual void gererPositionCurseurConcret(const bool& positionEstSurTable);
	virtual void assignerSymboleCurseur();

private:
	std::unique_ptr<VisiteurCreationMur> visiteurCreationMur_{ nullptr };
	std::unique_ptr<VisiteurVerificationQuad> visiteurVerificationQuad_{ nullptr };

	bool enCreation_{ false };
	glm::dvec3 positionPremierClic_{ glm::dvec3() };
	NoeudAbstrait* mur_{ nullptr };
};

#endif

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
