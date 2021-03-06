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
	: NoeudComposite{ 0, "racine" }
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
std::shared_ptr<NoeudAbstrait> ArbreRendu::creerNoeud(const std::string& typeNouveauNoeud) const
{
	if (usines_.find(typeNouveauNoeud) == usines_.end()) {
		// Incapable de trouver l'usine
		return nullptr;
	}
	
	const UsineAbstraite* usine{ (*(usines_.find(typeNouveauNoeud))).second.get() };

	std::shared_ptr<NoeudAbstrait> nouveauNoeud = usine->creerNoeud();
	
	return nouveauNoeud;
}

std::shared_ptr<NoeudAbstrait> ArbreRendu::creerNoeud(EntityType entityType) const
{
	std::shared_ptr<NoeudAbstrait> newEntity = nullptr;
	// Find the name from the type.
	auto nameIt = names_.find(entityType);
	if (nameIt != names_.end())
	{
		// Find the factory from the name.
		auto factoryIt = usines_.find(nameIt->second);
		if (factoryIt != usines_.end())
		{
			newEntity = factoryIt->second->creerNoeud();
		}
	}
	return newEntity;
}

////////////////////////////////////////////////////////////////////////
//
// @fn shared_ptr<NoeudAbstrait> ArbreRendu::ajouterNouveauNoeud(const std::string& typeParent, const std::string& typeNouveauNoeud)
//
// Cette fonction permet d'ajouter un nouveau noeud dans l'arbre de
// rendu.
//
// @param[in] typeParent       : Le type du parent du nouveau noeud.
// @param[in] typeNouveauNoeud : Le type du nouveau noeud.
//
// @return Le noeud nouvellement cr��.
//
////////////////////////////////////////////////////////////////////////
std::shared_ptr<NoeudAbstrait> ArbreRendu::ajouterNouveauNoeud(const std::string& typeParent,
	                                                           const std::string& typeNouveauNoeud)
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
//
// @fn shared_ptr<NoeudAbstrait> ArbreRendu::ajouterNouveauNoeud(const std::string& typeParent, const std::string& typeNouveauNoeud)
//
// Cette fonction permet d'ajouter un nouveau noeud dans l'arbre de
// rendu.
//
// @param[in] typeParent       : Le type du parent du nouveau noeud.
// @param[in] typeNouveauNoeud : Le type du nouveau noeud.
//
// @return Le noeud nouvellement cr��.
//
////////////////////////////////////////////////////////////////////////
std::shared_ptr<NoeudAbstrait> ArbreRendu::ajouterNouveauNoeud(NoeudAbstrait* parent,
	const std::string& typeNouveauNoeud)
{
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

std::string ArbreRendu::obtenirCheminFichierZone()
{
	return cheminFichierZone;
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
	int nbSelection = 0;
	NoeudAbstrait* table = chercher(0);
	if (table) 
	{
		for (unsigned int i = 0; i < table->obtenirNombreEnfants(); i++) {
			NoeudAbstrait* enfant = table->chercher(i);
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
	double angle = 0.0;

	NoeudAbstrait* table = chercher(0);
	if (table)
	{
		bool trouve = false;
		for (unsigned int i = 0; i < table->obtenirNombreEnfants() && !trouve; i++) {
			NoeudAbstrait* enfant = table->chercher(i);
			if (enfant->estSelectionne()) {
				angle = enfant->getPhysicsComponent().rotation.z;
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
	double facteurMiseAEchelle = 1.0;
	NoeudAbstrait* table = chercher(0);
	if (table)
	{
		bool trouve = false;
		for (unsigned int i = 0; i < table->obtenirNombreEnfants() && !trouve; i++) {
			NoeudAbstrait* enfant = table->chercher(i);
			if (enfant->estSelectionne()) {
				if (enfant->obtenirNom() == "ligneNoire" || enfant->obtenirNom() == "depart") {
					facteurMiseAEchelle = 1;
				}
				else{
					facteurMiseAEchelle = enfant->getPhysicsComponent().scale.x;
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
	double positionX = 0.0;
	NoeudAbstrait* table = chercher(0);
	if (table)
	{
		bool trouve = false;
		for (unsigned int i = 0; i < table->obtenirNombreEnfants() && !trouve; i++) {
			NoeudAbstrait* enfant = table->chercher(i);
			if (enfant->estSelectionne()) {
				positionX = enfant->getPhysicsComponent().relativePosition.x;
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
	double positionY = 0.0;
	NoeudAbstrait* table = chercher(0);
	if (table)
	{
		bool trouve = false;
		for (unsigned int i = 0; i < table->obtenirNombreEnfants() && !trouve; i++) {
			NoeudAbstrait* enfant = table->chercher(i);
			if (enfant->estSelectionne()) {
				positionY = enfant->getPhysicsComponent().relativePosition.y;
				trouve = true;
			}
		}
	}
	return positionY;
}
////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////
