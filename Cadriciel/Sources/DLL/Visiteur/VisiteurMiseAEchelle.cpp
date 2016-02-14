///////////////////////////////////////////////////////////////////////////
/// @file VisiteurMiseAEchelle.cpp
/// @author Olivier St-Amour 
/// @date 2016-02-13
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#include "VisiteurMiseAEchelle.h"
#include "ArbreRendu.h"
#include "NoeudTypes.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurMiseAEchelle::VisiteurMiseAEchelle()
///
/// Constructeur
///
/// @param[in] Aucun
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurMiseAEchelle::VisiteurMiseAEchelle()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurMiseAEchelle::~VisiteurMiseAEchelle()
///
/// Destructeur
///
/// @param[in] Aucun
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurMiseAEchelle::~VisiteurMiseAEchelle()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurMiseAEchelle::initialiser(ArbreRendu* noeud)
///
/// Fonction qui initialise les valeurs du vecteur facteursDimensionsInitiaux_
/// selon les facteurs de dimensions des enfants de la table.
///
/// @param[in] noeud : l'arbre rendu contenant le noeud Table, entre autres.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurMiseAEchelle::initialiser(ArbreRendu* noeud)
{
	facteursDimensionsInitiaux_.clear();
	NoeudAbstrait* table = noeud->chercher("table");
	for (unsigned int i = 0; i < table->obtenirNombreEnfants(); i++)
	{
		facteursDimensionsInitiaux_.push_back(table->chercher(i)->obtenirFacteurMiseAEchelle());
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurMiseAEchelle::reinitialiser(ArbreRendu* noeud)
///
/// Fonction qui reinitialise les facteurs de dimensions des enfants de la 
/// table selon le vecteur facteursDimensionsInitiaux_.
///
/// @param[in] noeud : l'arbre rendu contenant le noeud Table, entre autres.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurMiseAEchelle::reinitialiser(ArbreRendu* noeud)
{
	NoeudAbstrait* table = noeud->chercher("table");
	for (unsigned int i = 0; i < table->obtenirNombreEnfants(); i++)
	{
		table->chercher(i)->assignerFacteurMiseAEchelle(facteursDimensionsInitiaux_[i]);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurMiseAEchelle::visiter(ArbreRendu* noeud)
///
/// Fonction servant à donner l'accès au noeud Table.
///
/// @param[in] noeud : l'arbre rendu contenant le noeud Table, entre autres.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurMiseAEchelle::visiter(ArbreRendu* noeud)
{
	noeud->chercher("table")->accepterVisiteur(this);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurMiseAEchelle::visiter(NoeudTable* noeud)
///
/// Fonction servant à donner l'accès aux enfants de la table.
///
/// @param[in] noeud : Le noeud Table contenant les enfants desquels on veut modifier le facteur de dimension.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurMiseAEchelle::visiter(NoeudTable* noeud)
{
	NoeudAbstrait* enfant;
	glm::dvec3 positionVirtuelle;
	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++)
	{
		enfant = noeud->chercher(i);
		if (enfant->estSelectionne())
		{
			enfant->accepterVisiteur(this);
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurMiseAEchelle::visiter(NoeudPoteau* noeud)
///
/// Fonction modifiant le facteur de dimension du poteau passé en paramètre.
///
/// @param[in] noeud : Le noeud Poteau duquel on veut modifier le facteur de dimension.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurMiseAEchelle::visiter(NoeudPoteau* noeud)
{
	double facteurMiseAEchelle = noeud->obtenirFacteurMiseAEchelle() + facteurMiseAEchelle_;
	if (facteurMiseAEchelle >= 0)
	{
		noeud->assignerFacteurMiseAEchelle(facteurMiseAEchelle);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurMiseAEchelle::visiter(NoeudMur* noeud)
///
/// Fonction modifiant le facteur de dimension du mur passé en paramètre.
///
/// @param[in] noeud : Le noeud Mur duquel on veut modifier le facteur de dimension.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurMiseAEchelle::visiter(NoeudMur* noeud)
{
	double facteurMiseAEchelle = noeud->obtenirFacteurMiseAEchelle() + facteurMiseAEchelle_ * 2;
	if (facteurMiseAEchelle >= 0)
	{
		noeud->assignerFacteurMiseAEchelle(facteurMiseAEchelle);
	}
}