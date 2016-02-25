////////////////////////////////////////////////
/// @file   ArbreRendu.cpp
/// @author Martin Bisson
/// @date   2007-01-28
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////

#include "ArbreRendu.h"
#include "UsineNoeud.h"
#include "NoeudAbstrait.h"
#include "VisiteurAbstrait.h"
#include "FacadeModele.h"
#include "VisiteurTypes.h"

#include "GL/glew.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn ArbreRendu::ArbreRendu()
///
/// Ne fait qu'assigner que ce noeud n'est pas sélectionnable.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
ArbreRendu::ArbreRendu()
	: NoeudComposite{ "racine" }
{
	// On ne veut pas que ce noeud soit sélectionnable.
	assignerEstSelectionnable(false);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn ArbreRendu::~ArbreRendu()
///
/// Détruit les usines des noeuds de l'arbre.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
ArbreRendu::~ArbreRendu()
{
	int i = 0;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn shared_ptr<NoeudAbstrait> ArbreRendu::creerNoeud(const std::string& typeNouveauNoeud) const
///
/// Cette fonction permet de créer un nouveau noeud, sans l'ajouter
/// directement à l'arbre de rendu.
///
/// @param[in] typeNouveauNoeud : Le type du nouveau noeud.
///
/// @return Le noeud nouvellement créé.
///
////////////////////////////////////////////////////////////////////////
std::shared_ptr<NoeudAbstrait> ArbreRendu::creerNoeud(
	const std::string& typeNouveauNoeud
	) const
{
	if (usines_.find(typeNouveauNoeud) == usines_.end()) {
		// Incapable de trouver l'usine
		return nullptr;
	}
	const UsineAbstraite* usine{ (*(usines_.find(typeNouveauNoeud))).second.get() };
	return usine->creerNoeud();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn shared_ptr<NoeudAbstrait> ArbreRendu::ajouterNouveauNoeud(const std::string& typeParent, const std::string& typeNouveauNoeud)
///
/// Cette fonction permet d'ajouter un nouveau noeud dans l'arbre de
/// rendu.
///
/// @param[in] typeParent       : Le type du parent du nouveau noeud.
/// @param[in] typeNouveauNoeud : Le type du nouveau noeud.
///
/// @return Le noeud nouvellement créé.
///
////////////////////////////////////////////////////////////////////////
std::shared_ptr<NoeudAbstrait> ArbreRendu::ajouterNouveauNoeud(
	const std::string& typeParent,
	const std::string& typeNouveauNoeud
	)
{
	std::shared_ptr<NoeudAbstrait> parent{ chercher(typeParent) };
	if (parent == nullptr) {
		// Incapable de trouver le parent
		return nullptr;
	}
	std::shared_ptr<NoeudAbstrait> nouveauNoeud{ creerNoeud(typeNouveauNoeud) };
	if (nouveauNoeud) {
		parent->ajouter(nouveauNoeud);
	}
	return nouveauNoeud;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn unsigned int ArbreRendu::calculerProfondeurMaximale()
///
/// Cette fonction retourne la profondeur maximale possible de l'arbre.
/// Comme lors du rendu, on effectue un glPushMatrix() pour sauvegarder
/// les transformations, ainsi qu'un glPushName() pour ajouter un nom
/// sur la pile des noms pour la sélection, la profondeur maximale de
/// l'arbre est limitée par la taille de la pile des matrices ainsi que
/// par celle de la pile des noms pour la sélection.
///
/// Cette fonction vérifie donc ces deux valeurs et retourne la plus
/// petite, c'est-à-dire celle qui limite la profondeur de l'arbre.
///
/// @return La profondeur maximale possible de l'arbre de rendu.
///
////////////////////////////////////////////////////////////////////////
unsigned int ArbreRendu::calculerProfondeurMaximale()
{
	GLint profondeurPileMatrice, profondeurPileNoms;

	glGetIntegerv(GL_MAX_MODELVIEW_STACK_DEPTH, &profondeurPileMatrice);
	glGetIntegerv(GL_MAX_NAME_STACK_DEPTH, &profondeurPileNoms);

	return (profondeurPileMatrice < profondeurPileNoms) ? profondeurPileMatrice : profondeurPileNoms;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRendu::accepterVisiteur(VisiteurAbstrait* visiteur)
///
/// Fonction faisant partie du patron visiteur.
/// Celle-ci permet à un noeud d'accepter un visiteur 
/// en appelant la fonction visiter de celui-ci.
///
/// @param[in] visiteur : Pointeur vers le visiteur qui doit être accepté par le noeud.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ArbreRendu::accepterVisiteur(VisiteurAbstrait* visiteur)
{
	visiteur->visiter(this);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRendu::assignerCheminFichierZone(std::string chemin)
///
/// Fonction servant à assigner le chemin d'un fichier de zone sélectionné par un utilisateur 
/// à la variable cheminFichierZone.
///
/// @param[in] chemin : Chemin vers le fichier.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void ArbreRendu::assignerCheminFichierZone(std::string chemin)
{
	cheminFichierZone = string(chemin);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn FILE* ArbreRendu::obtenirFichierZone(std::string mode)
///
/// Fonction permettant d'obtenir le fichier de zone sélectionné par l'utilisateur.
///
/// @param[in] mode : Si on ouvre le fichier en lecture ou en écriture.
///
/// @return Pointeur vers le fichier
///
////////////////////////////////////////////////////////////////////////
FILE* ArbreRendu::obtenirFichierZone(std::string mode)
{
	FILE* fichierZone;
	errno_t err;
	if (err = fopen_s(&fichierZone, cheminFichierZone.c_str(), mode.c_str()) != 0) {
		return NULL;
	}
	return fichierZone;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn FILE* ArbreRendu::obtenirFichierZoneDefaut(std::string mode)
///
/// Fonction permettant d'obtenir le fichier de zone contenant la structure de base.
///
/// @param[in] mode : Si on ouvre le fichier en lecture ou en écriture.
///
/// @return Pointeur vers le fichier
///
////////////////////////////////////////////////////////////////////////
FILE* ArbreRendu::obtenirFichierZoneDefaut(std::string mode)
{
	FILE* fichierZone;
	errno_t err;
	if (err = fopen_s(&fichierZone, cheminFichierZoneDefaut.c_str(), mode.c_str()) != 0) {
		return NULL;
	}

	return fichierZone;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn std::string ArbreRendu::obtenirCheminFichierZoneDefaut()
///
/// Fonction permettant d'obtenir le chemin vers le fichier contenant la structure de base de l'arbre de rendu.
///
///
/// @return Pointeur vers le fichier
///
////////////////////////////////////////////////////////////////////////
std::string ArbreRendu::obtenirCheminFichierZoneDefaut()
{
	return cheminFichierZoneDefaut;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn int FacadeModele::obtenirNombreSelection()
///
/// Cette fonction permet d'obtenir le nombre d'objet selectionné
///
/// @return int : le nombre d'objet selectionné
///
////////////////////////////////////////////////////////////////////////
int ArbreRendu::obtenirNombreSelection()
{
	NoeudAbstrait* table = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher(0);
	NoeudAbstrait* enfant;
	int nbSelection = 0;
	if (FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990() == nullptr) {
		nbSelection = 0;
	}
	else {
		for (unsigned int i = 0; i < table->obtenirNombreEnfants(); i++) {
			enfant = table->chercher(i);
			if (enfant->estSelectionne()) {
				nbSelection += 1;
			}
		}
	}
	return nbSelection;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn double FacadeModele::obtenirAngleRotation()
///
/// Cette fonction permet d'obtenir l'angle de rotation d'un objet
///
/// @return doublee : l'angle de rotation de l'objet
///
////////////////////////////////////////////////////////////////////////
double ArbreRendu::obtenirAngleRotation()
{
	NoeudAbstrait* table = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher(0);
	NoeudAbstrait* enfant;
	bool trouve = false;
	double angle;
	if (FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990() == nullptr) {
		angle = 0;
	}
	else {
		for (unsigned int i = 0; i < table->obtenirNombreEnfants() && !trouve; i++) {
			enfant = table->chercher(i);
			if (enfant->estSelectionne()) {
				angle = enfant->obtenirAngleRotation();
				trouve = true;
			}
		}
	}
	return angle;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn double FacadeModele::obtenirFacteurGrandeur()
///
/// Cette fonction permet d'obtenir le facteur de grandissement d'un objet
///
/// @return doublee : le facteur de grandissement d'un objet
///
////////////////////////////////////////////////////////////////////////
double ArbreRendu::obtenirFacteurMiseAEchelle()
{
	NoeudAbstrait* table = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher(0);
	NoeudAbstrait* enfant;
	bool trouve = false;
	double facteurMiseAEchelle;
	if (FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990() == nullptr) {
		facteurMiseAEchelle = 1;
	}
	else {
		for (unsigned int i = 0; i < table->obtenirNombreEnfants() && !trouve; i++) {
			enfant = table->chercher(i);
			if (enfant->estSelectionne()) {
				if (enfant->obtenirType() == "ligneNoire" || enfant->obtenirType() == "depart") {
					facteurMiseAEchelle = 1;
				}
				facteurMiseAEchelle = enfant->obtenirFacteurMiseAEchelle();
				trouve = true;
			}
		}
	}
	return facteurMiseAEchelle;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn double FacadeModele::obtenirPositionRelativeX()
///
/// Cette fonction permet d'obtenir la position relative en X
///
/// @return doublee : la position relative en X
///
////////////////////////////////////////////////////////////////////////
double ArbreRendu::obtenirPositionRelativeX()
{
	NoeudAbstrait* table = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher(0);
	NoeudAbstrait* enfant;
	bool trouve = false;
	double positionX;
	if (FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990() == nullptr) {
		positionX = 0;
	}
	else {
		for (unsigned int i = 0; i < table->obtenirNombreEnfants() && !trouve; i++) {
			enfant = table->chercher(i);
			if (enfant->estSelectionne()) {
				positionX = enfant->obtenirPositionRelative()[0];
				trouve = true;
			}
		}
	}
	return positionX;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn double FacadeModele::obtenirPositionRelativeY()
///
/// Cette fonction permet d'obtenir la position relative en Y
///
/// @return doublee : la position relative en Y
///
////////////////////////////////////////////////////////////////////////
double ArbreRendu::obtenirPositionRelativeY()
{
	NoeudAbstrait* table = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher(0);
	NoeudAbstrait* enfant;
	bool trouve = false;
	double positionY;
	if (FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990() == nullptr) {
		positionY = 0;
	}
	else {
		for (unsigned int i = 0; i < table->obtenirNombreEnfants() && !trouve; i++) {
			enfant = table->chercher(i);
			if (enfant->estSelectionne()) {
				positionY = enfant->obtenirPositionRelative()[1];
				trouve = true;
			}
		}
	}
	return positionY;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::assignerAngleRotation(double angle)
///
/// Cette fonction assigne un angle de rotation à un noeud seulement s'il est
/// encore sur la table
///
/// @param double angle: l'angle a assigner a l'objet
///
////////////////////////////////////////////////////////////////////////
void ArbreRendu::assignerAngleRotation(const double& angle)
{
	std::unique_ptr<VisiteurRotation> visiteur = std::make_unique <VisiteurRotation>();
	std::unique_ptr<VisiteurVerificationQuad> visiteurQuad = std::make_unique <VisiteurVerificationQuad>();
	std::unique_ptr<VisiteurMiseAJourQuad> visiteurMiseAJour = std::make_unique <VisiteurMiseAJourQuad>();

	NoeudAbstrait* table = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher(0);
	NoeudAbstrait* enfant;

	for (unsigned int i = 0; i < table->obtenirNombreEnfants(); i++) {
		enfant = table->chercher(i);
		if (enfant->estSelectionne()) {

			double angleAvantChangement = enfant->obtenirAngleRotation();
			visiteur->assignerAngleRotation(angle - angleAvantChangement);
			enfant->accepterVisiteur(visiteur.get());

			FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepterVisiteur(visiteurMiseAJour.get());
			FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepterVisiteur(visiteurQuad.get());
			
			if (!visiteurQuad->objetsDansZoneSimulation()) {
				visiteur->assignerAngleRotation(angleAvantChangement - angle);
				enfant->accepterVisiteur(visiteur.get());
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::assignerFacteurGrandeur(double facteurMiseAEchelle)
///
/// Cette fonction assigne un facteur de mise à échelle à un noeud seulement s'il est
/// encore sur la table
///
/// @param double angle: facteur de mise à échelle
///
////////////////////////////////////////////////////////////////////////
void ArbreRendu::assignerFacteurMiseAEchelle(const double& facteurMiseAEchelle)
{
	std::unique_ptr<VisiteurVerificationQuad> visiteurQuad = std::make_unique <VisiteurVerificationQuad>();
	std::unique_ptr<VisiteurMiseAJourQuad> visiteurMiseAJour = std::make_unique <VisiteurMiseAJourQuad>();

	NoeudAbstrait* table = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher("table");
	NoeudAbstrait* enfant;
	for (unsigned int i = 0; i < table->obtenirNombreEnfants(); i++) {
		enfant = table->chercher(i);
		if (enfant->estSelectionne()) {
			double facteurAvantChangement = enfant->obtenirFacteurMiseAEchelle();
			enfant->assignerFacteurMiseAEchelle(facteurMiseAEchelle);

			FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepterVisiteur(visiteurMiseAJour.get());
			FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepterVisiteur(visiteurQuad.get());
			
			if (!visiteurQuad->objetsDansZoneSimulation()) {
				enfant->assignerFacteurMiseAEchelle(facteurAvantChangement);
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::assignerPositionRelativeX(double positionRelativeX)
///
/// Cette fonction assigne une position en X à un noeud seulement s'il est
/// encore sur la table
///
/// @param double angle: position en X de l'objet
///
////////////////////////////////////////////////////////////////////////
void ArbreRendu::assignerPositionRelativeX(const double& positionRelativeX)
{
	std::unique_ptr<VisiteurVerificationQuad> visiteurQuad = std::make_unique <VisiteurVerificationQuad>();
	std::unique_ptr<VisiteurMiseAJourQuad> visiteurMiseAJour = std::make_unique <VisiteurMiseAJourQuad>();

	NoeudAbstrait* table = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher(0);
	NoeudAbstrait* enfant;
	for (unsigned int i = 0; i < table->obtenirNombreEnfants(); i++) {
		enfant = table->chercher(i);
		if (enfant->estSelectionne()) {
			double positionXAvantChangement = enfant->obtenirPositionRelative()[0];

			glm::dvec3 position = enfant->obtenirPositionRelative();
			position[0] = positionRelativeX;
			enfant->assignerPositionRelative(position);

			FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepterVisiteur(visiteurMiseAJour.get());
			FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepterVisiteur(visiteurQuad.get());
			
			if (!visiteurQuad->objetsDansZoneSimulation()) {
				position[0] = positionXAvantChangement;
				enfant->assignerPositionRelative(position);
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::assignerPositionRelativeY(double positionRelativeY)
///
/// Cette fonction assigne une position en Y à un noeud seulement s'il est
/// encore sur la table
///
/// @param double angle: position en Y de l'objet
///
////////////////////////////////////////////////////////////////////////
void ArbreRendu::assignerPositionRelativeY(const double& positionRelativeY)
{
	std::unique_ptr<VisiteurVerificationQuad> visiteurQuad = std::make_unique <VisiteurVerificationQuad>();
	std::unique_ptr<VisiteurMiseAJourQuad> visiteurMiseAJour = std::make_unique <VisiteurMiseAJourQuad>();

	NoeudAbstrait* table = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher(0);
	NoeudAbstrait* enfant;
	for (unsigned int i = 0; i < table->obtenirNombreEnfants(); i++) {
		enfant = table->chercher(i);
		if (enfant->estSelectionne()) {
			double positionYAvantChangement = enfant->obtenirPositionRelative()[1];

			glm::dvec3 position = enfant->obtenirPositionRelative();
			position[1] = positionRelativeY;
			enfant->assignerPositionRelative(position);

			FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepterVisiteur(visiteurMiseAJour.get());
			FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepterVisiteur(visiteurQuad.get());
			
			if (!visiteurQuad->objetsDansZoneSimulation()) {
				position[1] = positionYAvantChangement;
				enfant->assignerPositionRelative(position);
			}
		}
	}
}

////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////
