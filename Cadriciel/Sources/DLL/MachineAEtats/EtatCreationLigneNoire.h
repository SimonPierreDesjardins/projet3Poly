///////////////////////////////////////////////////////////////////////////
/// @file EtatCreationLigneNoire.h
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

class EtatCreationLigneNoire : public EtatAbstrait
{
public:
	EtatCreationLigneNoire();
	virtual ~EtatCreationLigneNoire();

	virtual void gererClicGaucheEnfonce(const int& x, const int& y);
	virtual void gererClicGaucheRelache(const int& x, const int& y);
	virtual void gererMouvementSouris(const int& x, const int& y);
	virtual void effectuerOperation();

	std::shared_ptr<const NoeudAbstrait> referenceNoeud_;

};








#endif