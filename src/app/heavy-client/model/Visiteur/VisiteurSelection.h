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

///////////////////////////////////////////////////////////////////////////
/// @class VisiteurSelection
/// @brief Visiteur permettant d'effectuer la s�lection d'un objet
///
/// @author Fr�d�ric Gr�goire
/// @date 2016-02-15
///////////////////////////////////////////////////////////////////////////
class VisiteurSelection : public VisiteurAbstrait
{
public:
    using Iterateur = std::vector<int>::iterator;

	/// Constructeur par d�faut.
	VisiteurSelection();

	/// Destructeur.
	virtual ~VisiteurSelection();
	
    // Initialiser la s�lection.
    void selectionner(Iterateur debut, Iterateur fin);

	/// Parcours du noeudTable.
	virtual void visiter(ArbreRendu* noeud);
	virtual void visiter(NoeudTable* noeud);

	//Indique si la touche control est appuyee
	inline void assignerCtrlAppuye(const bool& ctrlAppuye);

private:
	bool ctrlAppuye_ = false;
    Iterateur debut_, fin_;

};

////////////////////////////////////////////////////////////////////////
///
/// inline void VisiteurSelection::assignerCtrlAppuye(const bool& ctrlAppuye)
///
/// Fonction qui assigne un bool�en selon l'�tat de la touche Ctrl
///
/// @param[in] ctrlAppuye : l'�tat que l'on veut assigner au bool�en.
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