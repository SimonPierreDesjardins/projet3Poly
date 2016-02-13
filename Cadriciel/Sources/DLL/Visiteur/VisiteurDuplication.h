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

	/// Destructeur.
	virtual ~VisiteurDuplication();

	inline void assignerEnDuplication(bool enDuplication);
	inline NoeudAbstrait* obtenirDuplication();

	virtual void visiter(ArbreRendu* noeud);
	virtual void visiter(NoeudTable* noeud);	
	virtual void visiter(NoeudPoteau* noeud);
	virtual void visiter(NoeudMur* noeud);
	virtual void visiter(NoeudLigne* noeud);
	virtual void visiter(NoeudSegment* noeud);
	virtual void visiter(NoeudJonction* noeud);
	virtual void visiter(NoeudDuplication* noeud);

private:
	int nNoeuds_{ 0 };
	bool enDuplication_{ false };
	NoeudAbstrait* nouvelleLigne_{ nullptr };
	NoeudAbstrait* duplication_{ nullptr };
};

inline void VisiteurDuplication::assignerEnDuplication(bool enDuplication)
{
	enDuplication_ = enDuplication;
}

inline NoeudAbstrait* VisiteurDuplication::obtenirDuplication()
{
	return duplication_;
}

#endif // VISITEUR_DUPLICATION_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////