///////////////////////////////////////////////////////////////////////////
/// @file VisiteurDeplacement.h
/// @author Olivier St-Amour
/// @date 2016-02-03
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef VISITEUR_DEPLACEMENT_H
#define VISITEUR_DEPLACEMENT_H

#include "VisiteurAbstrait.h"

namespace client_network
{
	class MapSession;
}

///////////////////////////////////////////////////////////////////////////
/// @class VisiteurDeplacement
/// @brief Visiteur permettant d'effectuer le déplacement d'un objet
///
/// @author Frédéric Grégoire
/// @date 2016-02-15
///////////////////////////////////////////////////////////////////////////
class VisiteurDeplacement : public VisiteurAbstrait
{
public:
	/// Constructeur par défaut.
	VisiteurDeplacement(client_network::MapSession* mapSession);

	/// Destructeur.
	virtual ~VisiteurDeplacement();

	virtual void visiter(ArbreRendu* noeud);
	virtual void visiter(NoeudTable* noeud);
	virtual void visiter(NoeudDuplication* noeud);

private:
	VisiteurDeplacement() = delete;
	client_network::MapSession* mapSession_;

	void moveSelectedChildren(NoeudAbstrait* entity);

};


#endif // VISITEUR_Deplacement

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////