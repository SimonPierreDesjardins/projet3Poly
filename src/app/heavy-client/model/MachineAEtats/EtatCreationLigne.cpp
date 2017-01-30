///////////////////////////////////////////////////////////////////////////
/// @file EtatCreationLigneNoire.cpp
/// @author 
/// @date 2016-01-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#include "EtatCreationLigne.h"
#include "FacadeModele.h"
#include "Vue.h"
#include "ArbreRenduINF2990.h"
#include "Utilitaire.h"

#include <iostream> 

////////////////////////////////////////////////////////////////////////
///
/// @fn EtatCreationLigne::EtatCreationLigne()
///
/// Constructeur par d�fault
///
////////////////////////////////////////////////////////////////////////
EtatCreationLigne::EtatCreationLigne()
{
	visiteurCreationLigne_ = std::make_unique<VisiteurCreationLigne>();
	visiteurVerificationQuad_ = std::make_unique<VisiteurVerificationQuad>();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn EtatCreationLigne::~EtatCreationLigne()
///
/// Destructeur par d�fault
///
////////////////////////////////////////////////////////////////////////
EtatCreationLigne::~EtatCreationLigne()
{
	// Effacer la ligne si on change d'outil lors d'une cr�ation.
	if (enCreation_ && ligne_ != nullptr && segment_ != nullptr) {
		NoeudAbstrait* table = ligne_->obtenirParent();
		table->effacer(ligne_);
	}
	ligne_ = nullptr;
	segment_ = nullptr;
	positionsClic_.clear();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatCreationLigne::gererClicGaucheRelache(const int& x, const int& y)
///
/// Cette fonction cr�e une ligne si le curseur est sur la table et que le clique est � moins
/// de trois pixels. Cr�e un segement de ligne si CTRL est enfonc� par la suite sinon
/// derni�re ligne cr��.
///
/// @param const int& x: position en x du cursor
/// @param const int& y: position en y du cursor
///
////////////////////////////////////////////////////////////////////////
void EtatCreationLigne::gererClicGaucheRelache(const int& x, const int& y)
{
	// Si le curseur n'est pas sur la table, on ne gere par le clic gauche.
	if (!estClickDrag() && curseurEstSurTable_ && ligneEstSurTable()) {
		// Calcul et assignation de la position virtuelle.
		glm::dvec3 positionVirtuelle;
		vue_->convertirClotureAVirtuelle(x, y, positionVirtuelle);
		positionsClic_.push_back(positionVirtuelle);

		// Premier clic avec ou sans CTRL enfoncee.
		if (!enCreation_) {
			enCreation_ = true;
			arbre_->accepterVisiteur(visiteurCreationLigne_.get());
			ligne_ = visiteurCreationLigne_->obtenirReferenceNoeud();

			std::shared_ptr<NoeudAbstrait> nouveauNoeud = arbre_->creerNoeud(ArbreRenduINF2990::NOM_SEGMENT);
			segment_ = nouveauNoeud.get();
			ligne_->ajouter(nouveauNoeud);

		}
		// Clic subsequent avec CTRL enfoncee.
		else if (enCreation_ && toucheCtrlEnfonce_) {		
			std::shared_ptr<NoeudAbstrait> nouveauNoeud = arbre_->creerNoeud(ArbreRenduINF2990::NOM_SEGMENT);
			std::shared_ptr<NoeudAbstrait> jonction = arbre_->creerNoeud(ArbreRenduINF2990::NOM_JONCTION);
			jonction->assignerPositionRelative(positionVirtuelle);
			ligne_->ajouter(jonction);
			ligne_->ajouter(nouveauNoeud);
			segment_ = nouveauNoeud.get();
		}
		// Clic subsequent sans CTRL enfoncee (dernier clic).
		else if (enCreation_ && !toucheCtrlEnfonce_) {
			calculerPositionCentreLigne();
			ligne_ = nullptr;
			segment_ = nullptr;
			enCreation_ = false;
			positionsClic_.clear();
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatCreationLigne::gererToucheEchappe()
///
/// Cette fonction supprime une ligne si elle est en cr�ation. Sinon rien
///
////////////////////////////////////////////////////////////////////////
void EtatCreationLigne::gererToucheEchappe()
{
	if (enCreation_) {
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->effacer(ligne_);
		ligne_ = nullptr;
		segment_ = nullptr;
		enCreation_ = false;
		positionsClic_.clear();
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatCreationLigne::gererMouvementSouris(const int& x, const int& y)
///
/// Cette fonction assigne la longeur et l'angle d'une ligne lorsqu'elle est en
/// cr�ation, sinon rien
///
/// @param const int& x: position en x du cursor
/// @param const int& y: position en y du cursor
///
////////////////////////////////////////////////////////////////////////
void EtatCreationLigne::gererMouvementSouris(const int& x, const int& y)
{
	EtatAbstrait::gererMouvementSouris(x, y);
	glm::dvec3 positionVirtuelle;
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, positionVirtuelle);
	
	gererPositionCurseur(positionVirtuelle);

	if (enCreation_) {
		assert(segment_ != nullptr);

		// Calculer et assigner l'angle de rotation.
		double angle = utilitaire::calculerAngleRotation(positionsClic_.back(), positionVirtuelle);
		segment_->assignerAngleRotation(angle);
		
		// Calculer et assigner le facteur de mise � �chelle.
		double distance = utilitaire::calculerDistanceHypothenuse(positionsClic_.back(), positionVirtuelle);
		segment_->assignerFacteurMiseAEchelle(distance);

		// Calculer et assigner la position relative.
		glm::dvec3 positionRelative = utilitaire::calculerPositionEntreDeuxPoints(positionsClic_.back(), positionVirtuelle);
		segment_->assignerPositionRelative(positionRelative);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatCreationLigne::gererToucheControlEnfoncee()
///
/// Cette fonction assigne la valeur True si la touche CTRL est enfonc�e
///
////////////////////////////////////////////////////////////////////////
void EtatCreationLigne::gererToucheControlEnfoncee()
{
	if (!toucheCtrlEnfonce_) {
		toucheCtrlEnfonce_ = true;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatCreationLigne::gererToucheControlRelachee()
///
/// Cette fonction assigne la valeur False si la touche CTRL est rel�ch�e
///
////////////////////////////////////////////////////////////////////////
void EtatCreationLigne::gererToucheControlRelachee()
{
	toucheCtrlEnfonce_ = false;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatCreationLigne::calculerPositionCentreLigne()
///
/// Cette fonction calcul le centre d'une ligne
///
////////////////////////////////////////////////////////////////////////
void EtatCreationLigne::calculerPositionCentreLigne()
{
	// Si le vecteur de positions est vide, on sort.
	if (positionsClic_.empty()) return;

	// Initialiser les minimums et les maximums 
	double minX = positionsClic_[0].x;
	double maxX = positionsClic_[0].x;
	double minY = positionsClic_[0].y;
	double maxY = positionsClic_[0].y;

	// Trouver les min / max dans les positions des clics.
	for (int i = 0; i < positionsClic_.size(); i++) {
		if (positionsClic_[i].x > maxX) {
			maxX = positionsClic_[i].x;
		}
		if (positionsClic_[i].x < minX) {
			minX = positionsClic_[i].x;
		}
		if (positionsClic_[i].y > maxY) {
			maxY = positionsClic_[i].y;
		}
		if (positionsClic_[i].y < minY) {
			minY = positionsClic_[i].y;
		}
	}
	// Calculer et assigner la position relative � la ligne
	glm::dvec3 centre = { (minX + maxX) / 2.0, (minY + maxY) / 2.0, 0 };
	ligne_->assignerPositionRelative(centre);

	// Ajuster la position relative des segments.
	glm::dvec3 positionEnfant;
	for (unsigned int i = 0; i < ligne_->obtenirNombreEnfants(); i++) {
		positionEnfant = ligne_->chercher(i)->obtenirPositionRelative();
		positionEnfant -= centre;
		ligne_->chercher(i)->assignerPositionRelative(positionEnfant);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatCreationMur::gererPositionCurseurConcret(const bool& positionEstSurTable)
///
/// Cette fonction affiche l'objet si le curseur est sur la table et arr�te
/// d'afficher l'objet si le curseur n'est pas sur la table.
///
/// @param bool positionEstSurTable: True si curseur est sur la table, sinon false.
///
////////////////////////////////////////////////////////////////////////
void EtatCreationLigne::gererPositionCurseurConcret(const bool& positionEstSurTable)
{
	if (positionEstSurTable && !curseurEstSurTable_) {
		curseurEstSurTable_ = true;
		if (segment_ != nullptr) {
			segment_->assignerAffiche(true);
		}
	}
	else if (!positionEstSurTable && curseurEstSurTable_) {
		curseurEstSurTable_ = false;
		if (segment_ != nullptr) {
			segment_->assignerAffiche(false);
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool EtatCreationLigne::ligneEstSurTable()
///
///	Appel le visiteurMiseAJourQuad et le visiteurVerificationQuad pour 
/// v�rifier si la ligne est sur la table au moment de la cr�ation.
///
/// @return bool: True si la ligne est sur la table, sin non false.
///
////////////////////////////////////////////////////////////////////////
bool EtatCreationLigne::ligneEstSurTable()
{
	arbre_->accepterVisiteur(visiteurVerificationQuad_.get());
	return visiteurVerificationQuad_->objetsDansZoneSimulation();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatAbstrait::assignerSymboleCurseur()
///
/// Cette fonction assigne le symbole interdit au curseur si celui-ci
/// ne se trouve pas sur la table. 
///
////////////////////////////////////////////////////////////////////////
void EtatCreationLigne::assignerSymboleCurseur()
{
	if (!curseurEstSurTable_)
	{
		HCURSOR Cursor = LoadCursor(NULL, IDC_NO);
		SetCursor(Cursor);
	}
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
