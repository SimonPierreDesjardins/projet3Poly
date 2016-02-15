///////////////////////////////////////////////////////////////////////////
/// @file VisiteurRotation.cpp
/// @author Olivier St-Amour 
/// @date 2016-02-13
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#include "VisiteurRotation.h"
#include "FacadeModele.h"
#include "ArbreRenduINF2990.h"
#include "NoeudTypes.h"
#include "Utilitaire.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurRotation::VisiteurRotation()
///
/// Constructeur. Il calcul le centre de la sélection du noeud Table.
///
/// @param[in] Aucun
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurRotation::VisiteurRotation()
{
	NoeudAbstrait* noeud = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher(0);
	calculerCentreSelection(noeud);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurRotation::~VisiteurRotation()
///
/// Destructeur
///
/// @param[in] Aucun
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurRotation::~VisiteurRotation()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurRotation::visiter(ArbreRendu* noeud)
///
/// Fonction servant à donner l'accès au noeud Table.
///
/// @param[in] noeud : l'arbre rendu contenant le noeud Table, entre autres.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurRotation::visiter(ArbreRendu* noeud)
{
	noeud->chercher(0)->accepterVisiteur(this);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurRotation::visiter(NoeudTable* noeud)
///
/// Fonction servant à donner l'accès aux noeuds enfants sélectionnés de la table passée en paramètre.
///
/// @param[in] noeud : Les enfants de la table auxquels ont veut appliquer une rotation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurRotation::visiter(NoeudTable* noeud)
{
	NoeudAbstrait* enfant = nullptr;
	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++) {
		enfant = noeud->chercher(i);
		if (enfant != nullptr && enfant->estSelectionne()) {
			enfant->accepterVisiteur(this);
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurRotation::visiter(NoeudPoteau* noeud)
///
/// Fonction qui modifie la position du noeud Poteau passé en paramètre selon la rotation effectuée.
///
/// @param[in] noeud : Le noeud Poteau auquel ont veut appliquer une rotation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurRotation::visiter(NoeudPoteau* noeud)
{
	assignerNouvellePositionRelative(noeud);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurRotation::visiter(NoeudMur* noeud)
///
/// Fonction qui modifie la position et l'angle de rotation du noeud Mur passé en paramètre selon la rotation effectuée.
///
/// @param[in] noeud : Le noeud Mur auquel ont veut appliquer une rotation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurRotation::visiter(NoeudMur* noeud)
{
	// Assigner le nouvel angle de rotation.
	double angle = noeud->obtenirAngleRotation() + angleRotation_;
	noeud->assignerAngleRotation(angle);
	assignerNouvellePositionRelative(noeud);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurRotation::visiter(NoeudDepart* noeud)
///
/// Fonction qui modifie la position et l'angle de rotation du noeud Depart passé en paramètre selon la rotation effectuée.
///
/// @param[in] noeud : Le noeud Depart auquel ont veut appliquer une rotation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurRotation::visiter(NoeudDepart* noeud)
{
	// Assigner le nouvel angle de rotation.
	double angle = noeud->obtenirAngleRotation() + angleRotation_;
	noeud->assignerAngleRotation(angle);
	assignerNouvellePositionRelative(noeud);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurRotation::visiter(NoeudLigne* noeud)
///
/// Fonction qui modifie la position et l'angle de rotation des enfants (segments) du noeud Ligne passé en paramètre selon la rotation effectuée.
///
/// @param[in] noeud : Le noeud Ligne auquel ont veut appliquer une rotation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurRotation::visiter(NoeudLigne* noeud)
{
	assignerNouvellePositionRelative(noeud);
	NoeudAbstrait* enfant = nullptr;
	double angle = 0.0;
	glm::dvec3 nouvellePositionRelative = { 0.0, 0.0, 0.0 };
	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++) {
		enfant = noeud->chercher(i);
		utilitaire::calculerPositionApresRotation(enfant->obtenirPositionRelative(), nouvellePositionRelative, angleRotation_);
		enfant->assignerPositionRelative(nouvellePositionRelative);
		angle = enfant->obtenirAngleRotation() + angleRotation_;
		enfant->assignerAngleRotation(angle);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurRotation::calculerCentreSelection(NoeudAbstrait* noeud)
///
/// Fonction qui calcule le centre de la sélection en faisant la moyenne des points extrêmes de tous les objets sélectionnés.
///
/// @param[in] noeud : Le noeud auquel ont veut appliquer une rotation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurRotation::calculerCentreSelection(NoeudAbstrait* noeud)
{
	if (noeud->obtenirNombreEnfants() < 1) return;
	// Initialiser les minimums et les maximums 
	double minX = 0.0;
	double maxX = 0.0;
	double minY = 0.0;
	double maxY = 0.0;
	double x = 0.0;
	double y = 0.0;
	bool estPremierSelectionne = true;
	NoeudAbstrait* enfant = nullptr;
	// Trouver les min / max dans les positions des noeuds sur la table.
	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++)
	{
		enfant = noeud->chercher(i);
		if (enfant != nullptr && enfant->estSelectionne())
		{
			x = enfant->obtenirPositionRelative().x;
			y = enfant->obtenirPositionRelative().y;

			if (x > maxX || estPremierSelectionne) {
				maxX = x;
			}
			if (x < minX || estPremierSelectionne) {
				minX = x;
			}
			if (y > maxY || estPremierSelectionne) {
				maxY = y; 
			}
			if (y < minY || estPremierSelectionne) {
				minY = y;
			}
			if (estPremierSelectionne) {
				estPremierSelectionne = false;
			}
		}
	}
	// Calculer et assigner la position relative à la ligne
	 centreSelection_= { (minX + maxX) / 2.0, (minY + maxY) / 2.0, 0.0 };
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurRotation::assignerNouvellePositionRelative(NoeudAbstrait* noeud)
///
/// Fonction qui calcule la nouvelle position du noeud passé en paramètre selon la rotation effectuée.
///
/// @param[in] noeud : Le noeud auquel ont veut appliquer une rotation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurRotation::assignerNouvellePositionRelative(NoeudAbstrait* noeud)
{
	glm::dvec3 distanceCentreSelection = noeud->obtenirPositionRelative() - centreSelection_;
	glm::dvec3 nouvelleDistanceCentreSelection = { 0.0, 0.0, 0.0 };
	utilitaire::calculerPositionApresRotation(distanceCentreSelection, nouvelleDistanceCentreSelection, angleRotation_);
	noeud->assignerPositionRelative(nouvelleDistanceCentreSelection + centreSelection_);
}
