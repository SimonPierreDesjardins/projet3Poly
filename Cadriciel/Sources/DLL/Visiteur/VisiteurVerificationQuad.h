///////////////////////////////////////////////////////////////////////////
/// @file VisiteurVerificationQuad.h
/// @author Olivier St-Amour
/// @date 2016-02-09
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef VISITEUR_VERIFICATION_QUAD_H
#define VISITEUR_VERIFICATION_QUAD_H

#include "VisiteurAbstrait.h"
#include "VisiteurMiseAJourQuad.h"
#include <memory>

class VisiteurVerificationQuad : public VisiteurAbstrait
{
public:
	/// Constructeur par défaut.
	VisiteurVerificationQuad();

	/// Destructeur.
	virtual ~VisiteurVerificationQuad();

	/// Obtenir si tous les objets sont dans la zone de simulation.
	inline bool objetsDansZoneSimulation();

	virtual void visiter(ArbreRendu* noeud);
	virtual void visiter(NoeudTable* noeud);
	virtual void visiter(NoeudDupliquation* noeud);
	virtual void visiter(NoeudPoteau* noeud);
	virtual void visiter(NoeudMur* noeud);
	virtual void visiter(NoeudLigne* noeud);
	virtual void visiter(NoeudSegment* noeud);
	virtual void visiter(NoeudDepart* noeud);

private:
	bool verifierPointEstSurTable(glm::dvec3 point);
	bool objetsDansZoneSimulation_;
};

inline bool VisiteurVerificationQuad::objetsDansZoneSimulation()
{
	return objetsDansZoneSimulation_;
}

#endif // VISITEUR_VERIFICATION_QUAD

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////