///////////////////////////////////////////////////////////////////////////
/// @file VisiteurVerificationObjets.h
/// @author Olivier St-Amour
/// @date 2016-02-09
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef VISITEUR_VERIFICATION_OBJETS_H
#define VISITEUR_VERIFICATION_OBJETS_H

#include "VisiteurAbstrait.h"

class VisiteurVerificationObjets : public VisiteurAbstrait
{
public:
	/// Constructeur par défaut.
	VisiteurVerificationObjets();

	/// Destructeur.
	virtual ~VisiteurVerificationObjets();

	/// Obtenir si tous les objets sont dans la zone de simulation.
	inline bool objetsDansZoneSimulation();

	virtual void visiter(ArbreRendu* noeud);
	virtual void visiter(NoeudTable* noeud);
	virtual void visiter(NoeudDuplication* noeud);
	virtual void visiter(NoeudPoteau* noeud);
	virtual void visiter(NoeudMur* noeud);
	virtual void visiter(NoeudLigneNoire* noeud);
	virtual void visiter(NoeudSegment* noeud);


private:
	bool verifierPointEstSurTable(glm::dvec3 point);
	
	bool objetsDansZoneSimulation_;


};

inline bool VisiteurVerificationObjets::objetsDansZoneSimulation()
{
	return objetsDansZoneSimulation_;
}

#endif // VISITEUR_VERIFICATION_OBJETS

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////