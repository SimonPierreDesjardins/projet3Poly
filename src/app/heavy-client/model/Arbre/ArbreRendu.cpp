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
#include "Projection.h"

#include "GL/glew.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn ArbreRendu::ArbreRendu()
///
/// Ne fait qu'assigner que ce noeud n'est pas s�lectionnable.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
ArbreRendu::ArbreRendu()
	: NoeudComposite{ "racine" }
{
	// On ne veut pas que ce noeud soit s�lectionnable.
	assignerEstSelectionnable(false);

}


////////////////////////////////////////////////////////////////////////
///
/// @fn ArbreRendu::~ArbreRendu()
///
/// D�truit les usines des noeuds de l'arbre.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
ArbreRendu::~ArbreRendu()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn shared_ptr<NoeudAbstrait> ArbreRendu::creerNoeud(const std::string& typeNouveauNoeud) const
///
/// Cette fonction permet de cr�er un nouveau noeud, sans l'ajouter
/// directement � l'arbre de rendu.
///
/// @param[in] typeNouveauNoeud : Le type du nouveau noeud.
///
/// @return Le noeud nouvellement cr��.
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
/// @return Le noeud nouvellement cr��.
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
/// sur la pile des noms pour la s�lection, la profondeur maximale de
/// l'arbre est limit�e par la taille de la pile des matrices ainsi que
/// par celle de la pile des noms pour la s�lection.
///
/// Cette fonction v�rifie donc ces deux valeurs et retourne la plus
/// petite, c'est-�-dire celle qui limite la profondeur de l'arbre.
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
/// Celle-ci permet � un noeud d'accepter un visiteur 
/// en appelant la fonction visiter de celui-ci.
///
/// @param[in] visiteur : Pointeur vers le visiteur qui doit �tre accept� par le noeud.
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
/// Fonction servant � assigner le chemin d'un fichier de zone s�lectionn� par un utilisateur 
/// � la variable cheminFichierZone.
///
/// @param[in] chemin : Chemin vers le fichier.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void ArbreRendu::assignerCheminFichierZone(std::string chemin)
{
	cheminFichierZone = std::string(chemin);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn FILE* ArbreRendu::obtenirFichierZone(std::string mode)
///
/// Fonction permettant d'obtenir le fichier de zone s�lectionn� par l'utilisateur.
///
/// @param[in] mode : Si on ouvre le fichier en lecture ou en �criture.
///
/// @return Pointeur vers le fichier
///
////////////////////////////////////////////////////////////////////////
FILE* ArbreRendu::obtenirFichierZone(std::string mode)
{
	FILE* fichierZone;
	errno_t err;
	if (cheminFichierZone.substr(cheminFichierZone.find_last_of('\\') + 1, cheminFichierZone.length() - 1) == cheminFichierZoneDefaut.substr(cheminFichierZoneDefaut.find_last_of('/') + 1, cheminFichierZoneDefaut.length() - 1) && mode == "w"){
		std::string temp = cheminFichierZone.substr(0,cheminFichierZone.find_first_of('.'));
		int i = 1;
		while (utilitaire::fichierExiste(cheminFichierZone))
			cheminFichierZone = temp + std::to_string(i++) + EXTENSION_ZONE;
	}
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
/// @param[in] mode : Si on ouvre le fichier en lecture ou en �criture.
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
/// Cette fonction permet d'obtenir le nombre d'objet selectionn�
///
/// @return int : le nombre d'objet selectionn�
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
	return (double)((int)angle % 360);
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
				else{
					facteurMiseAEchelle = enfant->obtenirFacteurMiseAEchelle();
				}
					
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
/// Cette fonction assigne un angle de rotation � un noeud seulement s'il est
/// encore sur la table
///
/// @param double angle: l'angle a assigner a l'objet
///
////////////////////////////////////////////////////////////////////////
void ArbreRendu::assignerAngleRotation(const double& angle)
{
	std::unique_ptr<VisiteurRotation> visiteurRotation = std::make_unique <VisiteurRotation>();
	std::unique_ptr<VisiteurVerificationQuad> visiteurVerification = std::make_unique <VisiteurVerificationQuad>();

    NoeudAbstrait* table = chercher(0); 
    unsigned int nEnfants = table->obtenirNombreEnfants();
	for (unsigned int i = 0; i < nEnfants; i++) {
		NoeudAbstrait* enfant = table->chercher(i);
		if (enfant->estSelectionne()) 
        {
			double angleAvantChangement = enfant->obtenirAngleRotation();
			visiteurRotation->assignerAngleRotation(angle - angleAvantChangement);
			enfant->accepterVisiteur(visiteurRotation.get());

			accepterVisiteur(visiteurVerification.get());
            bool positionValide = visiteurVerification->objetsDansZoneSimulation();
			if (!positionValide) 
            {
                // 
				visiteurRotation->assignerAngleRotation(angleAvantChangement - angle);
				enfant->accepterVisiteur(visiteurRotation.get());
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::assignerFacteurGrandeur(double facteurMiseAEchelle)
///
/// Cette fonction assigne un facteur de mise � �chelle � un noeud seulement s'il est
/// encore sur la table
///
/// @param double angle: facteur de mise � �chelle
///
////////////////////////////////////////////////////////////////////////
void ArbreRendu::assignerFacteurMiseAEchelle(const double& facteurMiseAEchelle)
{
	std::unique_ptr<VisiteurVerificationQuad> visiteurVerification = std::make_unique <VisiteurVerificationQuad>();
	NoeudAbstrait* table = chercher("table");
	for (unsigned int i = 0; i < table->obtenirNombreEnfants(); i++) {
    	NoeudAbstrait* enfant = table->chercher(i);
		if (enfant->estSelectionne()) 
        {
            // Assigner le nouveau facteur de mise � �chelle.
			double facteurAvantChangement = enfant->obtenirFacteurMiseAEchelle();
			enfant->assignerFacteurMiseAEchelle(facteurMiseAEchelle);

            // V�rifier la nouvelle position du noeud.
			accepterVisiteur(visiteurVerification.get());
            bool positionValide = visiteurVerification->objetsDansZoneSimulation();
			if (!positionValide) 
            {
				enfant->assignerFacteurMiseAEchelle(facteurAvantChangement);
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::assignerPositionRelativeX(double positionRelativeX)
///
/// Cette fonction assigne une position en X � un noeud seulement s'il est
/// encore sur la table
///
/// @param double angle: position en X de l'objet
///
////////////////////////////////////////////////////////////////////////
void ArbreRendu::assignerPositionRelativeX(const double& positionRelativeX)
{
	std::unique_ptr<VisiteurVerificationQuad> visiteurVerification = std::make_unique <VisiteurVerificationQuad>();
	NoeudAbstrait* table = chercher(0);
    unsigned int nEnfants = table->obtenirNombreEnfants();
	for (unsigned int i = 0; i < nEnfants; i++) {
		NoeudAbstrait* enfant = table->chercher(i);
		if (enfant->estSelectionne()) 
        {
            // Ajuster la position du noeud et garder la derni�re position.
            double positionXAvantChangement = enfant->obtenirPositionRelative().x;
			glm::dvec3 position = enfant->obtenirPositionRelative();
			position.x = positionRelativeX;
			enfant->assignerPositionRelative(position);

            // Verifier la position du noeud.
			accepterVisiteur(visiteurVerification.get());
            bool positionValide = visiteurVerification->objetsDansZoneSimulation();

            // Replacer le noeud.
			if (!positionValide) 
            {
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
/// Cette fonction assigne une position en Y � un noeud seulement s'il est
/// encore sur la table
///
/// @param double angle: position en Y de l'objet
///
////////////////////////////////////////////////////////////////////////
void ArbreRendu::assignerPositionRelativeY(const double& positionRelativeY)
{
	std::unique_ptr<VisiteurVerificationQuad> visiteurVerification = std::make_unique <VisiteurVerificationQuad>();
	NoeudAbstrait* table = chercher(0);
	for (unsigned int i = 0; i < table->obtenirNombreEnfants(); i++) {
    	NoeudAbstrait* enfant = table->chercher(i);
		if (enfant->estSelectionne()) 
        {
            // Ajuster la position du noeud et garder la derni�re position.
			double positionYAvantChangement = enfant->obtenirPositionRelative()[1];
			glm::dvec3 position = enfant->obtenirPositionRelative();
			position.y = positionRelativeY;
			enfant->assignerPositionRelative(position);

            // V�rifier que la position est valide.
			accepterVisiteur(visiteurVerification.get());
            bool positionValide = visiteurVerification->objetsDansZoneSimulation();

            // Replacer le noeud.
			if (!positionValide) 
            {
				position[1] = positionYAvantChangement;
				enfant->assignerPositionRelative(position);
			}
		}
	}
}

////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////
