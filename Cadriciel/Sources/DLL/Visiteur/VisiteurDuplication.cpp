///////////////////////////////////////////////////////////////////////////
/// @file VisiteurDuplication.cpp
/// @author Olivier St-Amour 
/// @date 2016-02-13
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////


#include "VisiteurDuplication.h"
#include "FacadeModele.h"
#include "NoeudTypes.h"
#include "ArbreRendu.h"
#include <memory>

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDuplication::VisiteurDuplication()
///
/// Constructeur. Il initialise l'attribut centreSelection_ selon la sélection.
///
/// @param[in] Aucun
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurDuplication::VisiteurDuplication()
{
	NoeudAbstrait* noeud = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher(0);
	calculerCentreSelection(noeud);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDuplication::~VisiteurDuplication()
///
/// Destructeur
///
/// @param[in] Aucun
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurDuplication::~VisiteurDuplication()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDuplication::visiter(ArbreRendu* noeud)
///
/// Fonction servant à donner l'accès au noeud Table.
///
/// @param[in] noeud : l'arbre rendu contenant le noeud Table, entre autres.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurDuplication::visiter(ArbreRendu* noeud)
{
	noeud->chercher("table")->accepterVisiteur(this);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDuplication::visiter(NoeudTable* noeud)
///
/// Fonction qui crée et ajoute un noeud Duplication au noeud Table passé en paramètre selon la sélection actuelle.
///
/// @param[in] noeud : Le noeud Table auquel on veut ajouter la duplication.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurDuplication::visiter(NoeudTable* noeud)
{
	ArbreRendu* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
	std::shared_ptr<NoeudAbstrait> nouveauNoeud = arbre->creerNoeud(ArbreRenduINF2990::NOM_DUPLICATION);
	noeud->ajouter(nouveauNoeud);

	duplication_ = nouveauNoeud.get();
	NoeudAbstrait* enfant = nullptr;
	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++) {
		enfant = noeud->chercher(i);
		if (enfant->estSelectionne()) {
			enfant->accepterVisiteur(this);
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDuplication::visiter(NoeudPoteau* noeud)
///
/// Fonction qui crée et ajoute un noeud Poteau au noeud Table passé en paramètre.
///
/// @param[in] noeud : Le noeud Poteau que l'on veut ajouter.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurDuplication::visiter(NoeudPoteau* noeud)
{
	ArbreRendu* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
	shared_ptr<NoeudAbstrait> nouveauNoeud = arbre->creerNoeud(ArbreRenduINF2990::NOM_POTEAU);
	
	nouveauNoeud->assignerFacteurMiseAEchelle(noeud->obtenirFacteurMiseAEchelle());
	// Assigner la position à la table dans la duplication si il y a plus qu'un noeud.
	nouveauNoeud->assignerPositionRelative(noeud->obtenirPositionRelative() - centreSelection_);
	duplication_->ajouter(nouveauNoeud);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDuplication::visiter(NoeudMur* noeud)
///
/// Fonction qui crée et ajoute un noeud Mur au noeud Table passé en paramètre.
///
/// @param[in] noeud : Le noeud Mur que l'on veut ajouter.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurDuplication::visiter(NoeudMur* noeud)
{
	ArbreRendu* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
	shared_ptr<NoeudAbstrait> nouveauNoeud = arbre->creerNoeud(ArbreRenduINF2990::NOM_MUR);

	nouveauNoeud->assignerAngleRotation(noeud->obtenirAngleRotation());
	nouveauNoeud->assignerFacteurMiseAEchelle(noeud->obtenirFacteurMiseAEchelle());
	// Assigner la position à la table dans la duplication si il y a plus qu'un noeud.
	nouveauNoeud->assignerPositionRelative(noeud->obtenirPositionRelative() - centreSelection_);
	duplication_->ajouter(nouveauNoeud);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDuplication::visiter(NoeudLigne* noeud)
///
/// Fonction qui crée et ajoute un noeud Ligne au noeud Table passé en paramètre.
///
/// @param[in] noeud : Le noeud Ligne que l'on veut ajouter.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurDuplication::visiter(NoeudLigne* noeud)
{
	ArbreRendu* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
	shared_ptr<NoeudAbstrait> nouvelleLigne = arbre->creerNoeud(ArbreRenduINF2990::NOM_LIGNENOIRE);

	nouvelleLigne->assignerFacteurMiseAEchelle(noeud->obtenirFacteurMiseAEchelle());
	nouvelleLigne->assignerPositionRelative(noeud->obtenirPositionRelative() - centreSelection_);
	// Appeler le visiteur des enfants.
	nouvelleLigne_ = nouvelleLigne.get();
	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++) {		
		noeud->chercher(i)->accepterVisiteur(this);
	}
	duplication_->ajouter(nouvelleLigne);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDuplication::visiter(NoeudDuplication* noeud)
///
/// Fonction qui crée et ajoute un noeud Duplication au noeud Table passé en paramètre.
///
/// @param[in] noeud : Le noeud Duplication que l'on veut ajouter.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurDuplication::visiter(NoeudDuplication* noeud)
{
	NoeudAbstrait* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
	NoeudAbstrait* table = arbre->chercher("table");
	
	// Ajouter les noeuds sur la table, puis détruire la duplication.
	std::shared_ptr<NoeudAbstrait> enfant = nullptr;
	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++) {
		enfant = noeud->obtenirDuplication(i);
		// Assigner la position relative du noeud à la table avant de l'ajouter.
		enfant->assignerPositionRelative(noeud->obtenirPositionRelative() + enfant->obtenirPositionRelative());
		table->ajouter(enfant);
	}
	table->effacer(noeud);
	arbre->accepterVisiteur(this);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDuplication::visiter(NoeudSegment* noeud)
///
/// Fonction qui crée et ajoute un noeud Segment au noeud Table passé en paramètre.
///
/// @param[in] noeud : Le noeud Segment que l'on veut ajouter.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurDuplication::visiter(NoeudSegment* noeud)
{
	ArbreRendu* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();

	// Creer le nouveau segment et copier les attributs du segment.
	shared_ptr<NoeudAbstrait> nouveauSegment = arbre->creerNoeud(ArbreRenduINF2990::NOM_SEGMENT);	
	nouveauSegment->assignerFacteurMiseAEchelle(noeud->obtenirFacteurMiseAEchelle());
	nouveauSegment->assignerAngleRotation(noeud->obtenirAngleRotation());
	nouveauSegment->assignerPositionRelative(noeud->obtenirPositionRelative());
	nouvelleLigne_->ajouter(nouveauSegment);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDuplication::visiter(NoeudJonction* noeud)
///
/// Fonction qui crée et ajoute un noeud Jonction au noeud Table passé en paramètre.
///
/// @param[in] noeud : Le noeud Jonction que l'on veut ajouter.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurDuplication::visiter(NoeudJonction* noeud)
{
	ArbreRendu* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
	
	// Creer la nouvelle jonction et copier la position relative.
	shared_ptr<NoeudAbstrait> nouvelleJonction = arbre->creerNoeud(ArbreRenduINF2990::NOM_JONCTION);
	nouvelleJonction->assignerPositionRelative(noeud->obtenirPositionRelative());
	nouvelleLigne_->ajouter(nouvelleJonction);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDuplication::calculerCentreSelection(NoeudAbstrait* noeud)
///
/// Fonction qui calcule le centre de la sélection actuelle en faisant la moyenne des points extrêmes de la sélection.
///
/// @param[in] noeud : Le noeud Abstrait que l'on veut dupliquer.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurDuplication::calculerCentreSelection(NoeudAbstrait* noeud)
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
	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants(); i++) {
		enfant = noeud->chercher(i);
		if (enfant->estSelectionne() && enfant->estDuplicable()) {
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
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////