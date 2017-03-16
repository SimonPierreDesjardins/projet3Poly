///////////////////////////////////////////////////////////////////////////
/// @file VisiteurSelection.cpp
/// @authors Ulric Villeneuve et Simon-Pierre Desjardins
/// @date 2016-01-26
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#include <iterator>
#include <unordered_set>

#include "FacadeModele.h"
#include "Vue.h"
#include "VisiteurSelection.h"
#include "ArbreRenduINF2990.h"
#include "NoeudTypes.h"
#include "Utilitaire.h"
#include "Modele3D.h"
#include "FormeEnglobanteAbstraite.h"
#include "MapSession.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurSelection::VisiteurSelection()
///
/// Constructeur
///
/// @param[in] Aucun
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurSelection::VisiteurSelection()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurSelection::~VisiteurSelection()
///
/// Destructeur
///
/// @param[in] Aucun
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurSelection::~VisiteurSelection()
{

}

    
////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurSelection::selectionner(Iterateur debut, Iterateur fin)
///
/// Permet d'intitialiser la sélection des objets sur la table.
///
/// @param[in] debut : L'itérateur qui pointe sur le début du vecteur de selection.
/// @param[in] fin : L'itérateur qui pointe sur la fin du vecteur de selection.
///
////////////////////////////////////////////////////////////////////////
void VisiteurSelection::selectionner(Iterateur debut, Iterateur fin, client_network::MapSession* mapSession)
{
    debut_ = debut;
    fin_ = fin;
	mapSession_ = mapSession;
    FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepterVisiteur(this);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurSelection::visiter(ArbreRendu* noeud)
///
/// Fonction servant à donner l'accès au noeud Table.
///
/// @param[in] noeud : l'arbre rendu contenant le noeud Table, entre autres.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurSelection::visiter(ArbreRendu* noeud)
{
	noeud->chercher("table")->accepterVisiteur(this);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurSelection::visiter(NoeudTable* noeud)
///
/// Fonction qui sélectionne les objets du noeud Table passé en paramètre selon
/// le vecteur de selection traversé par le biais d'itérateurs.
///
/// @param[in] noeud : Le noeud table sur lequel on fait la sélection des objets.
///
////////////////////////////////////////////////////////////////////////
void VisiteurSelection::visiter(NoeudTable* table)
{	
	std::unordered_set<int> selectedIndexes;
	selectedIndexes.insert(debut_, fin_);

	uint32_t nChildren = table->obtenirNombreEnfants();
	for (int i = 0; i < nChildren; ++i)
	{
		bool estSelectionne = table->chercher(i)->estSelectionne();
		// If this node is not being selected
		if (selectedIndexes.find(i) == selectedIndexes.end())
		{
			// Node is being unselected and was selected (default behavior)
			if (!ctrlAppuye_ && estSelectionne)
			{
				mapSession_->updateSelectionStateLocalEntityAndChildren(table->chercher(i), false);
			}
		} 
		else 
		{
			// Node was not selected and is now being selected (default behavior)
			if (!ctrlAppuye_ && !estSelectionne)
			{
				mapSession_->updateSelectionStateLocalEntityAndChildren(table->chercher(i), true);
			}
			// Node is being clicked on, selection is inverted (ctrl behavior)
			else if (ctrlAppuye_)
			{
				mapSession_->updateSelectionStateLocalEntityAndChildren(table->chercher(i), !estSelectionne);
			} 
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////