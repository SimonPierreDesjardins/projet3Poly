///////////////////////////////////////////////////////////////////////////////
/// @file FacadeModele.cpp
/// @author Martin Bisson
/// @date 2007-05-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

// Commentaire Doxygen mis sur la première page de la documentation Doxygen.
/**

@mainpage Projet intégrateur de deuxième année -- INF2990

*/

#include <windows.h>
#include <cassert>

#include "GL/glew.h"
#include "FreeImage.h"

#include "FacadeModele.h"

#include "VueOrtho.h"
#include "Camera.h"
#include "Projection.h"

#include "Utilitaire.h"
#include "AideGL.h"
#include "ArbreRenduINF2990.h"

#include "ConfigScene.h"
#include "CompteurAffichage.h"

// Remlacement de EnveloppeXML/XercesC par TinyXML
// Julien Gascon-Samson, été 2011
#include "tinyxml2.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "EtatTypes.h"
#include "ModeTypes.h"

/// Pointeur vers l'instance unique de la classe.
std::unique_ptr<FacadeModele> FacadeModele::instance_{ nullptr };

/// Chaîne indiquant le nom du fichier de configuration du projet.
const std::string FacadeModele::FICHIER_CONFIGURATION{ "configuration.xml" };



////////////////////////////////////////////////////////////////////////
///
/// @fn FacadeModele* FacadeModele::obtenirInstance()
///
/// Cette fonction retourne un pointeur vers l'instance unique de la
/// classe.  Si cette instance n'a pas été créée, elle la crée.  Cette
/// création n'est toutefois pas nécessairement "thread-safe", car
/// aucun verrou n'est pris entre le test pour savoir si l'instance
/// existe et le moment de sa création.
///
/// @return Un pointeur vers l'instance unique de cette classe.
///
////////////////////////////////////////////////////////////////////////
FacadeModele* FacadeModele::obtenirInstance()
{
	if (instance_.get() == nullptr)
	{
		instance_ = std::unique_ptr<FacadeModele>(new FacadeModele());
	}
	return instance_.get();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::libererInstance()
///
/// Cette fonction libère l'instance unique de cette classe.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::libererInstance()
{
	instance_ = nullptr;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn FacadeModele::~FacadeModele()
///
/// Ce destructeur libère les objets du modèle.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
FacadeModele::~FacadeModele()
{
	arbre_ = nullptr;
	vue_ = nullptr;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::initialiserOpenGL(HWND hWnd)
///
/// Cette fonction permet d'initialiser le contexte OpenGL.  Elle crée
/// un contexte OpenGL sur la fenêtre passée en paramètre, initialise
/// FreeImage (utilisée par le chargeur de modèles) et assigne des 
/// paramètres du contexte OpenGL.
///
/// @param[in] hWnd : La poignée ("handle") vers la fenêtre à utiliser.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::initialiserOpenGL(HWND hWnd)
{
	assignerEtat(SELECTION);
	assignerMode(MENU_PRINCIPAL);

	hWnd_ = hWnd;
	bool succes{ aidegl::creerContexteGL(hWnd_, hDC_, hGLRC_) };
	assert(succes && "Le contexte OpenGL n'a pu être créé.");

	// Initialisation des extensions de OpenGL
	glewInit();

	// Initialisation de la configuration
	chargerConfiguration();

	// FreeImage, utilisée par le chargeur, doit être initialisée
	FreeImage_Initialise();

	// La couleur de fond
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// Les lumières
	glEnable(GL_LIGHTING);
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glEnable(GL_COLOR_MATERIAL);
	/// Pour normaliser les normales dans le cas d'utilisation de glScale[fd]
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHT0);

	// Qualité
	glShadeModel(GL_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	// Profondeur
	glEnable(GL_DEPTH_TEST);

	// Le cull face
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// Lumière ambiante "globale"
	// Attention :
	// La plupart des modèles exportés n'ont pas de composante ambiante. (Ka dans les matériaux .mtl)
	glm::vec4 ambiant{ 0.2f, 0.2f, 0.2f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, glm::value_ptr(ambiant));

	// Création de l'arbre de rendu.  À moins d'être complètement certain
	// d'avoir une bonne raison de faire autrement, il est plus sage de créer
	// l'arbre après avoir créé le contexte OpenGL.
	arbre_ = std::make_unique<ArbreRenduINF2990>();
	arbre_->initialiser();

	// On crée une vue par défaut.
	vue_ = std::make_unique<vue::VueOrtho>(
		vue::Camera{
			glm::dvec3(0, 0, 10), glm::dvec3(0, 0, 0),
			glm::dvec3(0, 10, 0), glm::dvec3(0, 0, 1) },
		vue::ProjectionOrtho{
			0, 500, 0, 500,
			1, 1000, 1, 10000, 1.25,
			-50, 50, -50, 50 }
	);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::chargerConfiguration() const
///
/// Cette fonction charge la configuration à partir d'un fichier XML si
/// ce dernier existe.  Sinon, le fichier de configuration est généré à
/// partir de valeurs par défaut directement dans le code.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::chargerConfiguration() const
{
	// Vérification de l'existance du ficher

	// Si le fichier n'existe pas, on le crée.
	if (!utilitaire::fichierExiste(FICHIER_CONFIGURATION)) {
		enregistrerConfiguration();
	}
	// si le fichier existe on le lit
	else {
		tinyxml2::XMLDocument document;

		// Lire à partir du fichier de configuration
		document.LoadFile(FacadeModele::FICHIER_CONFIGURATION.c_str());

		// On lit les différentes configurations.
		ConfigScene::obtenirInstance()->lireDOM(document);
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::enregistrerConfiguration() const
///
/// Cette fonction génère un fichier XML de configuration à partir de
/// valeurs par défaut directement dans le code.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::enregistrerConfiguration() const
{
	tinyxml2::XMLDocument document;
	// Écrire la déclaration XML standard...
	document.NewDeclaration(R"(?xml version="1.0" standalone="yes"?)");
	
	// On enregistre les différentes configurations.
	ConfigScene::obtenirInstance()->creerDOM(document);

	// Écrire dans le fichier
	document.SaveFile(FacadeModele::FICHIER_CONFIGURATION.c_str());
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::libererOpenGL()
///
/// Cette fonction libère le contexte OpenGL et désinitialise FreeImage.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::libererOpenGL()
{
	utilitaire::CompteurAffichage::libererInstance();

	// On libère les instances des différentes configurations.
	ConfigScene::libererInstance();


	bool succes{ aidegl::detruireContexteGL(hWnd_, hDC_, hGLRC_) };
	assert(succes && "Le contexte OpenGL n'a pu être détruit.");

	FreeImage_DeInitialise();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::afficher() const
///
/// Cette fonction affiche le contenu de la scène.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::afficher() const
{
	if (!peutAfficher_)
		return;
	// Efface l'ancien rendu
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// Ne devrait pas être nécessaire
	vue_->appliquerProjection();

	// Positionne la caméra
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	vue_->appliquerCamera();

	// Afficher la scène
	afficherBase();

	// Compte de l'affichage
	utilitaire::CompteurAffichage::obtenirInstance()->signalerAffichage();

	// Échange les tampons pour que le résultat du rendu soit visible.
	::SwapBuffers(hDC_);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::afficherBase() const
///
/// Cette fonction affiche la base du contenu de la scène, c'est-à-dire
/// qu'elle met en place l'éclairage et affiche les objets.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::afficherBase() const
{
	// Positionner la lumière.
	glm::vec4 position{ 0, 0, 1, 0 };
	
	glm::vec4 zeroContribution{ 0.0f, 0.0f, 0.0f, 1 };
	glm::vec4 contributionMaximale{ 1.0, 1.0, 1.0, 1.0 };

	glLightfv(GL_LIGHT0, GL_POSITION, glm::value_ptr(position));
	// La plupart des modèles exportés n'ont pas de composante ambiante. (Ka dans les matériaux .mtl)
	glLightfv(GL_LIGHT0, GL_AMBIENT, glm::value_ptr(zeroContribution));
	// On sature les objets de lumière
	glLightfv(GL_LIGHT0, GL_DIFFUSE, glm::value_ptr(contributionMaximale));
	// Pas de composante spéculaire.
	glLightfv(GL_LIGHT0, GL_SPECULAR, glm::value_ptr(zeroContribution));

	// Afficher la scène.
	arbre_->afficher();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::reinitialiser()
///
/// Cette fonction réinitialise la scène à un état "vide".
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::reinitialiser()
{
	// Réinitialisation de la scène.
	arbre_->initialiser();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::animer(float temps)
///
/// Cette fonction effectue les différents calculs d'animations
/// nécessaires pour le mode jeu, tel que les différents calculs de
/// physique du jeu.
///
/// @param[in] temps : Intervalle de temps sur lequel effectuer le calcul.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::animer(float temps)
{
	// Mise à jour des objets.
	arbre_->animer(temps);

	// Mise à jour de la vue.
	vue_->animer(temps);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::modifierEtat (EtatAbstrait* etat)
///
/// Cette fonction change l'attribut etat_ pour la valeur de l'état en paramètre.
///
/// @param[in] etat : Nouvel état à traiter.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::assignerEtat(Etat etat)
{
		switch (etat)
		{
			case SELECTION :
				etat_.reset(nullptr);
				etat_ = std::make_unique<EtatSelection>();
				break;

			case DEPLACEMENT :
				etat_.reset(nullptr);
				etat_ = std::make_unique<EtatDeplacement>();
				break;

			case ROTATION :
				etat_.reset(nullptr);
				etat_ = std::make_unique<EtatRotation>();
				break;

			case MISE_A_ECHELLE :
				etat_.reset(nullptr);
				etat_ = std::make_unique<EtatMiseAEchelle>();
				break;

			case DUPLICATION :
				etat_.reset(nullptr);
				etat_ = std::make_unique<EtatDuplication>();
				break;

			case CREATION_POTEAU :
				etat_.reset(nullptr);
				etat_ = std::make_unique<EtatCreationPoteau>();
				break;

			case CREATION_MUR :
				etat_.reset(nullptr);
				etat_ = std::make_unique<EtatCreationMur>();
				break;

			case CREATION_LIGNE_NOIRE :
				etat_.reset(nullptr);
				etat_ = std::make_unique<EtatCreationLigneNoire>();
				break;
			
			case ZOOM:
				etat_.reset(nullptr);
				etat_ = std::make_unique<EtatLoupe>();
				break;

			default:
				break;
		}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::assignerMode(Mode mode)
///
/// Cette fonction change l'attribut mode_ pour la valeur du mode en paramètre.
///
/// @param[in] etat : Nouveau mode à traiter.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::assignerMode(Mode mode)
{
	switch (mode)
	{
		case MENU_PRINCIPAL:
			mode_.reset(nullptr);
			mode_ = std::make_unique<ModeMenuPrincipal>();
			break;

		case SIMULATION:
			mode_.reset(nullptr);
			mode_ = std::make_unique<ModeSimulation>();
			break;

		case EDITION:
			mode_.reset(nullptr);
			mode_ = std::make_unique<ModeEdition>();
			break;

		case CONFIGURE:
			mode_.reset(nullptr);
			mode_ = std::make_unique<ModeConfigure>();
			break;

		case TEST:
			mode_.reset(nullptr);
			mode_ = std::make_unique<ModeTest>();
			break;

		default:
			break;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn __declspec(dllexport) double __cdecl obtenirAngleRotation()
///
/// Cette fonction permet d'obtenir l'angle de rotation d'un objet
///
/// @return doublee : l'angle de rotation de l'objet
///
////////////////////////////////////////////////////////////////////////
double FacadeModele::obtenirAngleRotation()
{
	if (obtenirInstance()->arbre_ == nullptr)
	{
		return 1;
	}
	else
	{
		for (int i = 0; i < obtenirInstance()->arbre_->chercher(0)->obtenirNombreEnfants(); i++)
		{
			if (obtenirInstance()->arbre_->chercher(0)->chercher(i)->estSelectionne())
			{
				return obtenirInstance()->arbre_->chercher(0)->chercher(i)->getAngleRotationRelatif();
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn __declspec(dllexport) double obtenirFacteurGrandeur()
///
/// Cette fonction permet d'obtenir le facteur de grandissement d'un objet
///
/// @return doublee : le facteur de grandissement d'un objet
///
////////////////////////////////////////////////////////////////////////
double FacadeModele::obtenirFacteurGrandeur()
{
	if (obtenirInstance()->arbre_ == nullptr)
	{
		return 1;
	}
	else
	{
		for (int i = 0; i < obtenirInstance()->arbre_->chercher(0)->obtenirNombreEnfants(); i++)
		{
			if (obtenirInstance()->arbre_->chercher(0)->chercher(i)->estSelectionne())
			{
				return obtenirInstance()->arbre_->chercher(0)->chercher(i)->getfacteurMiseAEchelle();
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn __declspec(dllexport) double obtenirPositionRelativeX()
///
/// Cette fonction permet d'obtenir la position relative en X
///
/// @return doublee : la position relative en X
///
////////////////////////////////////////////////////////////////////////
double FacadeModele::obtenirPositionRelativeX()
{
	if (obtenirInstance()->arbre_ == nullptr)
	{
		return 1;
	}
	else
	{
		for (int i = 0; i < obtenirInstance()->arbre_->chercher(0)->obtenirNombreEnfants(); i++)
		{
			if (obtenirInstance()->arbre_->chercher(0)->chercher(i)->estSelectionne())
			{
				return obtenirInstance()->arbre_->chercher(0)->chercher(i)->getPositionRelatif()[0];
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn __declspec(dllexport) double obtenirPositionRelativeX()
///
/// Cette fonction permet d'obtenir la position relative en Y
///
/// @return doublee : la position relative en Y
///
////////////////////////////////////////////////////////////////////////
double FacadeModele::obtenirPositionRelativeY()
{
	if (obtenirInstance()->arbre_ == nullptr)
	{
		return 1;
	}
	else
	{
		for (int i = 0; i < obtenirInstance()->arbre_->chercher(0)->obtenirNombreEnfants(); i++)
		{
			if (obtenirInstance()->arbre_->chercher(0)->chercher(i)->estSelectionne())
			{
				return obtenirInstance()->arbre_->chercher(0)->chercher(i)->getPositionRelatif()[1];
			}
		}
	}
}

//TODO:
//Appeler un visiteur
void FacadeModele::assignerAngleRotation(double angle)
{
	for (int i = 0; i < obtenirInstance()->arbre_->chercher(0)->obtenirNombreEnfants(); i++)
	{
		if (obtenirInstance()->arbre_->chercher(0)->chercher(i)->estSelectionne())
		{
			obtenirInstance()->arbre_->chercher(0)->chercher(i)->assignerAngleRotation(angle);
		}
	}
}

//TODO:
//Appeler un visiteur
void FacadeModele::assignerFacteurGrandeur(double facteurGrandeur) 
{
	for (int i = 0; i < obtenirInstance()->arbre_->chercher(0)->obtenirNombreEnfants(); i++)
	{
		if (obtenirInstance()->arbre_->chercher(0)->chercher(i)->estSelectionne())
		{
			obtenirInstance()->arbre_->chercher(0)->chercher(i)->assignerFacteurMiseAEchelle(facteurGrandeur);
		}
	}
}

void FacadeModele::assignerPositionRelativeX(double positionRelativeX)
{
	for (int i = 0; i < obtenirInstance()->arbre_->chercher(0)->obtenirNombreEnfants(); i++)
	{
		if (obtenirInstance()->arbre_->chercher(0)->chercher(i)->estSelectionne())
		{
			glm::dvec3 position = obtenirInstance()->arbre_->chercher(0)->chercher(i)->getPositionRelatif();
			position[0] = positionRelativeX;
			obtenirInstance()->arbre_->chercher(0)->chercher(i)->assignerPositionRelative(position);
		}
	}
}

void FacadeModele::assignerPositionRelativeY(double positionRelativeY)
{
	for (int i = 0; i < obtenirInstance()->arbre_->chercher(0)->obtenirNombreEnfants(); i++)
	{
		if (obtenirInstance()->arbre_->chercher(0)->chercher(i)->estSelectionne())
		{
			glm::dvec3 position = obtenirInstance()->arbre_->chercher(0)->chercher(i)->getPositionRelatif();
			position[1] = positionRelativeY;
			obtenirInstance()->arbre_->chercher(0)->chercher(i)->assignerPositionRelative(position);
		}
	}
}

void FacadeModele::continuerAffichage(){
	peutAfficher_ = true;
}

void FacadeModele::stopAffichage(){
	peutAfficher_ = false;
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
