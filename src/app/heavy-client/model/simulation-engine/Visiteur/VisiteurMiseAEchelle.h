///////////////////////////////////////////////////////////////////////////
/// @file VisiteurMiseAEchelle.h
/// @author Olivier St-Amour
/// @date 2016-02-03
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef VISITEUR_MISE_A_ECHELLE_H
#define VISITEUR_MISE_A_ECHELLE_H

#include "VisiteurAbstrait.h"
#include <vector>

namespace client_network
{
	class MapSession;
}

///////////////////////////////////////////////////////////////////////////
/// @class VisiteurMiseAEchelle
/// @brief Visiteur permettant d'effectuer une mise à échelle d'un objet
///
/// @author Frédéric Grégoire
/// @date 2016-02-15
///////////////////////////////////////////////////////////////////////////
class VisiteurMiseAEchelle : public VisiteurAbstrait
{
public:
	/// Constructeur par défaut.
	VisiteurMiseAEchelle();

	/// Destructeur.
	virtual ~VisiteurMiseAEchelle();

	void resizeSelectedEntities(ArbreRendu* tree, client_network::MapSession* mapSession);

	void initialiser(ArbreRendu* arbre);
	void reinitialiser(ArbreRendu* arbre, client_network::MapSession* mapSession);
	virtual void visiter(ArbreRendu* noeud);
	virtual void visiter(NoeudTable* noeud);
	virtual void visiter(NoeudPoteau* noeud);
	virtual void visiter(NoeudMur* noeud);
private:
	std::vector<double> facteursDimensionsInitiaux_;
	client_network::MapSession* mapSession_;
};


#endif // VISITEUR_MISE_A_ECHELLE_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////