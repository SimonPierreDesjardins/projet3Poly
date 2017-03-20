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

namespace client_network
{
	class MapSession;
}

///////////////////////////////////////////////////////////////////////////
/// @class VisiteurSuppression
/// @brief Visiteur permettant d'effectuer la supression d'un objet
///
/// @author Fr�d�ric Gr�goire
/// @date 2016-02-15
///////////////////////////////////////////////////////////////////////////
class VisiteurSuppression : public VisiteurAbstrait
{
public:
	/// Constructeur par d�faut.
	VisiteurSuppression(client_network::MapSession* mapSession);

	/// Destructeur.
	virtual ~VisiteurSuppression();

	virtual void visiter(ArbreRendu* tree);

	/// Parcours du noeudTable.
	virtual void visiter(NoeudTable* table);

	virtual void visiter(NoeudDuplication* duplication);

private:
	VisiteurSuppression() = delete;

	client_network::MapSession* mapSession_;

	void deleteSelectedEntityAndChildren(NoeudAbstrait* entity);

};

#endif // VISITEUR_SUPPRESSION_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////