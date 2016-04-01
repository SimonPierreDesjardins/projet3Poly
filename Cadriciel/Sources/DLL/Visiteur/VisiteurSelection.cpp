///////////////////////////////////////////////////////////////////////////
/// @file VisiteurSelection.cpp
/// @authors Ulric Villeneuve et Simon-Pierre Desjardins
/// @date 2016-01-26
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#include "FacadeModele.h"
#include "Vue.h"
#include "VisiteurSelection.h"
#include "ArbreRenduINF2990.h"
#include "NoeudTypes.h"
#include "Utilitaire.h"
#include "Modele3D.h"
#include "FormeEnglobanteAbstraite.h"
#include <iterator>


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
void VisiteurSelection::selectionner(Iterateur debut, Iterateur fin)
{
    debut_ = debut;
    fin_ = fin;
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
	if (!ctrlAppuye_) 
    {
		table->deselectionnerTout();
	}
    
    Iterateur it;
    for (it = debut_; it != fin_; it++)
    {
        NoeudAbstrait* enfant = nullptr;
        enfant = table->chercher(*it);
        assert(enfant, "enfant de la table recherché n'existe pas: " + *it);
        if (!ctrlAppuye_)
        {
            enfant->selectionnerTout();
        }
        else
        {
            bool estSelectionne = enfant->estSelectionne();
            if (estSelectionne)
            {
                enfant->deselectionnerTout();
            }
            else
            {
                enfant->selectionnerTout();
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////