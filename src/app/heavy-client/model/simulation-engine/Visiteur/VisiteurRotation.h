///////////////////////////////////////////////////////////////////////////
/// @file VisiteurRotation.h
/// @author Olivier St-Amour
/// @date 2016-01-29
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef VISITEUR_ROTATION_H
#define VISITEUR_ROTATION_H

#include "VisiteurAbstrait.h"

namespace engine
{
	class MapSession;
}

///////////////////////////////////////////////////////////////////////////
/// @class VisiteurRotation
/// @brief Visiteur permettant d'effectuer la rotation d'un objet
///
/// @author Frédéric Grégoire
/// @date 2016-02-15
///////////////////////////////////////////////////////////////////////////
class VisiteurRotation : public VisiteurAbstrait
{
public:
	/// Constructeur par défaut.
	VisiteurRotation();

	/// Destructeur.
	virtual ~VisiteurRotation();

	void rotateSelectedObjects(ArbreRendu* tree, engine::MapSession* mapSession);

	virtual void visiter(ArbreRendu* noeud);
	virtual void visiter(NoeudTable* noeud);
	virtual void visiter(NoeudPoteau* noeud);
	virtual void visiter(NoeudMur* noeud);
	virtual void visiter(NoeudLigne* noeud);
	virtual void visiter(NoeudDepart* noeud);
	virtual void visiter(NoeudTeleporteur* noeud);

	virtual void visiter(NoeudLigneCourseAbstrait* noeud);

	virtual void visiter(NoeudPaireTeleporteurs* noeud);


private:

	engine::MapSession* mapSession_{ nullptr };

	void assignerNouvellePositionRelative(NoeudAbstrait* noeud);
	
	void calculerCentreSelection(NoeudAbstrait* noeud);
	glm::dvec3 centreSelection_;
};

#endif // VISITEUR_ROTATION_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////