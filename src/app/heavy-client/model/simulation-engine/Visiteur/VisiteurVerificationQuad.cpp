///////////////////////////////////////////////////////////////////////////
/// @file VisiteurVerificationQuad.cpp
/// @author Olivier St-Amour 
/// @date 2016-02-13
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#include "VisiteurVerificationQuad.h"
#include "ArbreRendu.h"
#include "NoeudTypes.h"
#include "RectangleEnglobant.h"
#include "CercleEnglobant.h"

#define coinMinX -48
#define coinMaxX  48
#define coinMinY -24
#define coinMaxY  24

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurVerificationQuad::VisiteurVerificationQuad()
///
/// Constructeur
///
/// @param[in] Aucun
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurVerificationQuad::VisiteurVerificationQuad()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurVerificationQuad::~VisiteurVerificationQuad()
///
/// Destructeur
///
/// @param[in] Aucun
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurVerificationQuad::~VisiteurVerificationQuad()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurVerificationQuad::visiter(ArbreRendu* noeud)
///
/// Fonction servant � donner l'acc�s au noeud Table.
///
/// @param[in] noeud : l'arbre rendu contenant le noeud Table, entre autres.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurVerificationQuad::visiter(ArbreRendu* arbre)
{
    // Mettre � jour l'arbre de rendu avant de faire la v�rification.
    arbre->animer(0.0);
	arbre->chercher("table")->accepterVisiteur(this);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurVerificationQuad::visiter(NoeudTable* noeud)
///
/// Fonction servant � donner l'acc�s aux enfants du noeud Table.
///
/// @param[in] noeud : Le noeud Table contenant les enfants auxquels on veut avoir acc�s.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurVerificationQuad::visiter(NoeudTable* noeud)
{
	objetsDansZoneSimulation_ = true;
	NoeudAbstrait* enfant = nullptr;
    boiteTable_ = noeud->obtenirBoiteEnglobanteModele();
	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants() && objetsDansZoneSimulation_; i++) {
		enfant = noeud->chercher(i);
		enfant->accepterVisiteur(this);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurVerificationQuad::visiter(NoeudDuplication* noeud)
///
/// Fonction servant � donner l'acc�s au nouveau noeud cr��e lors de la duplication.
///
/// @param[in] noeud : Le noeud Duplication contenant les enfants auxquels on veut avoir acc�s.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurVerificationQuad::visiter(NoeudDuplication* noeud)
{
    unsigned int n = noeud->obtenirNombreEnfants();
	for (unsigned int i = 0; i < n && objetsDansZoneSimulation_; i++) {
		noeud->chercher(i)->accepterVisiteur(this);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurVerificationQuad::visiter(NoeudPoteau* noeud)
///
/// Fonction qui v�rifie que le poteau pass� en param�tre se trouve dans les limites de la table.
///
/// @param[in] noeud : Le noeud Poteau sur lequel on veut effectuer la v�rication.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurVerificationQuad::visiter(NoeudPoteau* noeud)
{
    objetsDansZoneSimulation_ = noeud->obtenirFormeEnglobante()->calculerEstDansLimites(coinMinX, coinMaxX, coinMinY, coinMaxY);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurVerificationQuad::visiter(NoeudMur* noeud)
///
/// Fonction qui v�rifie que le mur pass� en param�tre se trouve dans les limites de la table.
///
/// @param[in] noeud : Le noeud Mur sur lequel on veut effectuer la v�rication.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurVerificationQuad::visiter(NoeudMur* noeud)
{
	objetsDansZoneSimulation_ = noeud->obtenirFormeEnglobante()->calculerEstDansLimites(coinMinX, coinMaxX, coinMinY, coinMaxY);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurVerificationQuad::visiter(NoeudDepart* noeud)
///
/// Fonction qui v�rifie que la fl�che de d�part pass�e en param�tre se trouve dans les limites de la table.
///
/// @param[in] noeud : Le noeud Depart sur lequel on veut effectuer la v�rication.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurVerificationQuad::visiter(NoeudDepart* noeud)
{
	objetsDansZoneSimulation_ = noeud->obtenirFormeEnglobante()->calculerEstDansLimites(coinMinX, coinMaxX, coinMinY, coinMaxY);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurVerificationQuad::visiter(NoeudLigne* noeud)
///
/// Fonction qui v�rifie que la ligne pass�e en param�tre se trouve dans les limites de la table.
///
/// @param[in] noeud : Le noeud Ligne sur lequel on veut effectuer la v�rication.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurVerificationQuad::visiter(NoeudLigne* noeud)
{
	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants() && objetsDansZoneSimulation_; i++) {
		noeud->chercher(i)->accepterVisiteur(this);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurVerificationQuad::visiter(NoeudSegment* noeud)
///
/// Fonction qui v�rifie que le segment pass� en param�tre se trouve dans les limites de la table.
///
/// @param[in] noeud : Le noeud Segment sur lequel on veut effectuer la v�rication.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurVerificationQuad::visiter(NoeudSegment* noeud)
{
	objetsDansZoneSimulation_ = noeud->obtenirFormeEnglobante()->calculerEstDansLimites(coinMinX, coinMaxX, coinMinY, coinMaxY);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurVerificationQuad::verifierPointEstSurTable(glm::dvec3 point)
///
/// Fonction qui v�rifie que le point pass� en param�tre se trouve dans les limites de la table.
///
/// @param[in] point : Le point sur lequel on veut effectuer la v�rication.
///
/// @return bool :`Bool�en qui indique si le poitn pass� en param�tre se trouve ou non dans les limites de la table.
///
////////////////////////////////////////////////////////////////////////
bool VisiteurVerificationQuad::verifierPointEstSurTable(glm::dvec3 point)
{
	// Les valeurs maximales de la table.
	const double MIN_X = -48.0;
	const double MAX_X =  48.0;
	const double MIN_Y = -24.0;
	const double MAX_Y =  24.0;

	return (MIN_X <= point.x && point.x <= MAX_X && MIN_Y <= point.y && point.y <= MAX_Y);
}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////