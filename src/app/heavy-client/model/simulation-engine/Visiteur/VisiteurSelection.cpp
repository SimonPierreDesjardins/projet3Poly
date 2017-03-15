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
/// Permet d'intitialiser la s�lection des objets sur la table.
///
/// @param[in] debut : L'it�rateur qui pointe sur le d�but du vecteur de selection.
/// @param[in] fin : L'it�rateur qui pointe sur la fin du vecteur de selection.
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
/// Fonction servant � donner l'acc�s au noeud Table.
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
/// Fonction qui s�lectionne les objets du noeud Table pass� en param�tre selon
/// le vecteur de selection travers� par le biais d'it�rateurs.
///
/// @param[in] noeud : Le noeud table sur lequel on fait la s�lection des objets.
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
        assert(enfant);
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