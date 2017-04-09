///////////////////////////////////////////////////////////////////////////
/// @file VisiteurSelection.h
/// @authors Ulric Villeneuve et Simon-Pierre Desjardins
/// @date 2016-01-26
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef VISITEUR_SELECTION_H
#define VISITEUR_SELECTION_H

#include "VisiteurAbstrait.h"
#include "Utilitaire.h"
#include <memory>
#include <vector>
#include <iterator>

namespace engine
{
	class MapSession;
}

///////////////////////////////////////////////////////////////////////////
/// @class VisiteurSelection
/// @brief Visiteur permettant d'effectuer la sélection d'un objet
///
/// @author Frédéric Grégoire
/// @date 2016-02-15
///////////////////////////////////////////////////////////////////////////
class VisiteurSelection : public VisiteurAbstrait
{
public:
    using Iterateur = std::vector<int>::iterator;

	/// Constructeur par défaut.
	VisiteurSelection();

	/// Destructeur.
	virtual ~VisiteurSelection();
	
    // Initialiser la sélection.
    void selectionner(Iterateur debut, Iterateur fin, engine::MapSession* mapSession, ArbreRendu* arbre);

	/// Parcours du noeudTable.
	virtual void visiter(ArbreRendu* noeud);
	virtual void visiter(NoeudTable* noeud);

	//Indique si la touche control est appuyee
	inline void assignerCtrlAppuye(const bool& ctrlAppuye);

private:
	bool ctrlAppuye_ = false;
    Iterateur debut_, fin_;
	engine::MapSession* mapSession_;
};

////////////////////////////////////////////////////////////////////////
///
/// inline void VisiteurSelection::assignerCtrlAppuye(const bool& ctrlAppuye)
///
/// Fonction qui assigne un booléen selon l'état de la touche Ctrl
///
/// @param[in] ctrlAppuye : l'état que l'on veut assigner au booléen.
///
////////////////////////////////////////////////////////////////////////
inline void VisiteurSelection::assignerCtrlAppuye(const bool& ctrlAppuye)
{
    ctrlAppuye_ = ctrlAppuye;
}

#endif // VISITEUR_SELECTION_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////