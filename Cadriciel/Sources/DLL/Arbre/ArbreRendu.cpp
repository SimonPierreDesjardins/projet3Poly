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

////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////
