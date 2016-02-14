////////////////////////////////////////////////
/// @file   VisiteurAbstrait.cpp
/// @author Olivier St-Amour
/// @date   20016-01-13
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////

#include "VisiteurAbstrait.h"
#include "FacadeModele.h"
#include "Vue.h"
#include "Projection.h"
#include "Modele3D.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurAbstrait::VisiteurAbstrait()
///
/// Constructeur par d�faut.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurAbstrait::VisiteurAbstrait()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn  VisiteurAbstrait::~VisiteurAbstrait()
///
/// Destructeur d�clar� virtuel pour les classes d�riv�es.
///
/// @return Aucune (destructeur).
///NoeudDuplication
////////////////////////////////////////////////////////////////////////
VisiteurAbstrait::~VisiteurAbstrait()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn  VisiteurAbstrait::visiter(ArbreRendu* noeud)
///
/// Fonction virtuelle pour les classes d�riv�es donnant acc�s � l'arbreRendu pass� en param�tre.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurAbstrait::visiter(ArbreRendu* noeud)
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn  VisiteurAbstrait::visiter(NoeudTable* noeud)
///
/// Fonction virtuelle pour les classes d�riv�es donnant acc�s au noeud Table pass� en param�tre.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurAbstrait::visiter(NoeudTable* noeud)
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn  VisiteurAbstrait::visiterRectangle(NoeudTable* noeud)
///
/// Fonction virtuelle pour les classes d�riv�es donnant acc�s au noeud Table pass� en param�tre.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurAbstrait::visiterRectangle(NoeudTable* noeud)
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn  VisiteurAbstrait::visiter(NoeudPoteau* noeud)
///
/// Fonction virtuelle pour les classes d�riv�es donnant acc�s au noeud Poteau pass� en param�tre.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurAbstrait::visiter(NoeudPoteau* noeud)
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn  VisiteurAbstrait::visiter(NoeudMur* noeud)
///
/// Fonction virtuelle pour les classes d�riv�es donnant acc�s au noeud Mur pass� en param�tre.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurAbstrait::visiter(NoeudMur* noeud)
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn  VisiteurAbstrait::visiter(NoeudLigne* noeud)
///
/// Fonction virtuelle pour les classes d�riv�es donnant acc�s au noeud Ligne pass� en param�tre.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurAbstrait::visiter(NoeudLigne* noeud)
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn  VisiteurAbstrait::visiter(NoeudDuplication* noeud)
///
/// Fonction virtuelle pour les classes d�riv�es donnant acc�s au noeud Duplication pass� en param�tre.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurAbstrait::visiter(NoeudDuplication* noeud)
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn  VisiteurAbstrait::visiter(NoeudSegment* noeud)
///
/// Fonction virtuelle pour les classes d�riv�es donnant acc�s au noeud Segment pass� en param�tre.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurAbstrait::visiter(NoeudSegment* noeud)
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn  VisiteurAbstrait::visiter(NoeudDepart* noeud)
///
/// Fonction virtuelle pour les classes d�riv�es donnant acc�s au noeud Depart pass� en param�tre.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurAbstrait::visiter(NoeudDepart* noeud)
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn  VisiteurAbstrait::visiter(NoeudJonction* noeud)
///
/// Fonction virtuelle pour les classes d�riv�es donnant acc�s au noeud Jonction pass� en param�tre.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurAbstrait::visiter(NoeudJonction* noeud)
{

}

void VisiteurAbstrait::visiter(NoeudRobot* noeud){

}