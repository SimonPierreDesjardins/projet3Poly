///////////////////////////////////////////////////////////////////////////
/// @file VisiteurDuplication.h
/// @author Olivier St-Amour
/// @date 2016-02-02
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef VISITEUR_DUPLICATION_H
#define VISITEUR_DUPLICATION_H

#include "VisiteurAbstrait.h"
 
class VisiteurDuplication : public VisiteurAbstrait
{
public:
	/// Constructeur par défaut.
	VisiteurDuplication();

	// Constructeur par paramètre.
	VisiteurDuplication(const int& x, const int& y);
	
	/// Destructeur.
	virtual ~VisiteurDuplication();

	inline void assignerDuplication(bool enDuplication);


	virtual void visiter(ArbreRendu* noeud);
	virtual void visiter(NoeudTable* noeud);	
	virtual void visiter(NoeudPoteau* noeud);
	virtual void visiter(NoeudMur* noeud);
	virtual void visiter(NoeudLigneNoire* noeud);
	virtual void visiter(NoeudSegment* noeud);
	virtual void visiter(NoeudDuplication* noeud);

private:
	int nNoeuds_{ 0 };
	bool enDuplication_{ false };
};

inline void VisiteurDuplication::assignerDuplication(bool enDuplication)
{
	enDuplication_ = enDuplication;
}

#endif // VISITEUR_DUPLICATION_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////