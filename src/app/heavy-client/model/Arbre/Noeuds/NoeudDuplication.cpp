///////////////////////////////////////////////////////////////////////////////
/// @file NoeudDuplication.cpp
/// @author Olivier St-Amour
/// @date 2016-02-10
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudDuplication.h"
#include "VisiteurAbstrait.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudDuplication::NoeudDuplication(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par d�faut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudDuplication::NoeudDuplication(const std::string& typeNoeud)
	: NoeudComposite{ typeNoeud }
{
	estDuplicable_ = false;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudDuplication::~NoeudDuplication()
///
/// Ce destructeur d�sallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////

NoeudDuplication::~NoeudDuplication()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudDepart::afficherConcret() const
///
/// Cette fonction appelle l'affichage des �l�ments � dupliquer
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudDuplication::afficherConcret() const
{
	NoeudComposite::afficherConcret();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudDuplication::accepterVisiteur(VisiteurAbstrait* visiteur)
///
/// Cette fonction prend le pointeur de ce noeud et le passe au visiteur pour que ce dernier puisse d�l�guer
/// sa t�che � la m�thode qui se charge de ce type de noeud.
///
/// @param[in] visiteur: le pointeur au visiteur abstrait. (pour d�l�guer au concret apr�s)
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudDuplication::accepterVisiteur(VisiteurAbstrait* visiteur)
{
	visiteur->visiter(this);
}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////