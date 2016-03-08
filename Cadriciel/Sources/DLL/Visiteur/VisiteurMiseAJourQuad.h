///////////////////////////////////////////////////////////////////////////
/// @file VisiteurMiseAJourQuad.h
/// @author Olivier St-Amour
/// @date 2016-02-13
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef VISITEUR_MISE_A_JOUR_QUAD_H
#define VISITEUR_MISE_A_JOUR_QUAD_H

#include "VisiteurAbstrait.h"

namespace utilitaire{
	struct QuadEnglobant;
};

///////////////////////////////////////////////////////////////////////////
/// @class VisiteurMiseAJourQuad
/// @brief Visiteur permettant de mettre à jour la boite englobante d'un objet
///
/// @author Frédéric Grégoire
/// @date 2016-02-15
///////////////////////////////////////////////////////////////////////////
class VisiteurMiseAJourQuad : public VisiteurAbstrait
{
public:
	/// Constructeur par défaut.
	VisiteurMiseAJourQuad();

	/// Destructeur.
	virtual ~VisiteurMiseAJourQuad();

	virtual void visiter(ArbreRendu* noeud);
	virtual void visiter(NoeudTable* noeud);
	virtual void visiter(NoeudDuplication* noeud);
	virtual void visiter(NoeudPoteau* noeud);
	virtual void visiter(NoeudMur* noeud);
	virtual void visiter(NoeudLigne* noeud);
	virtual void visiter(NoeudSegment* noeud);
	virtual void visiter(NoeudJonction* noeud);
	virtual void visiter(NoeudDepart* noeud);
	virtual void visiter(NoeudRobot* noeud);

private:
	glm::dvec3 calculerPositionVirtuelle(const utilitaire::QuadEnglobant& quad);
	NoeudAbstrait* table_;
	ArbreRendu* arbre_;
	NoeudAbstrait* robot_;
};

#endif // VISITEUR_MISE_A_JOUR_QUAD

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////