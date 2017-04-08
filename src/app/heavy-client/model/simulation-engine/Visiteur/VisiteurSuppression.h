///////////////////////////////////////////////////////////////////////////
/// @file VisiteurSuppression.h
/// @authors Ulric Villeneuve et Simon-Pierre Desjardins
/// @date 2016-02-09
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef VISITEUR_SUPPRESSION_H
#define VISITEUR_SUPPRESSION_H

#include "VisiteurAbstrait.h"

namespace engine
{
	class MapSession;
}

///////////////////////////////////////////////////////////////////////////
/// @class VisiteurSuppression
/// @brief Visiteur permettant d'effectuer la supression d'un objet
///
/// @author Frédéric Grégoire
/// @date 2016-02-15
///////////////////////////////////////////////////////////////////////////
class VisiteurSuppression : public VisiteurAbstrait
{
public:
	/// Constructeur par défaut.
	VisiteurSuppression(engine::MapSession* mapSession);

	/// Destructeur.
	virtual ~VisiteurSuppression();

	virtual void visiter(ArbreRendu* tree);

	/// Parcours du noeudTable.
	virtual void visiter(NoeudTable* table);

	virtual void visiter(NoeudDuplication* duplication);

private:
	VisiteurSuppression() = delete;

	engine::MapSession* mapSession_;
};

#endif // VISITEUR_SUPPRESSION_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////