#include <memory>
#include <windows.h>

#include "GL/glew.h"
#include "FreeImage.h"
#include "AideGL.h"
#include "VueOrtho.h"
#include "VueOrbite.h"
#include "Camera.h"
#include "Projection.h"
#include "EnginSon.h"
#include "CompteurAffichage.h"

#include "SimulationEngine.h"

namespace engine {

SimulationEngine::~SimulationEngine()
{
	free();
}

// Cr�e un contexte OpenGL et initialise celui-ci.
void SimulationEngine::initializeRendering(HWND hWnd, ProfilUtilisateur* userProfile)
{
	hWnd_ = hWnd;
	bool succes{ aidegl::creerContexteGL(hWnd_, hDC_, hGLRC_) };
	assert(succes && "Le contexte OpenGL n'a pu �tre cr��.");

	// Initialisation des extensions de OpenGL
	glewInit();

	// FreeImage, utilis�e par le chargeur, doit �tre initialis�e
	FreeImage_Initialise();

	// La couleur de fond
	glClearColor(0.32f, 0.32f, 0.32f, 1.0f);

	// Les lumi�res
	glEnable(GL_LIGHTING);
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glEnable(GL_COLOR_MATERIAL);
	/// Pour normaliser les normales dans le cas d'utilisation de glScale[fd]
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);

	// Qualit�
	glShadeModel(GL_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	// Profondeur
	glEnable(GL_DEPTH_TEST);

	// Le cull face
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// Lumi�re ambiante "globale"
	// Attention :
	// La plupart des mod�les export�s n'ont pas de composante ambiante. (Ka dans les mat�riaux .mtl)
	lightController_.afficherLumiereAmbianteGlobale();

	// Cr�ation de l'arbre de rendu.  � moins d'�tre compl�tement certain
	// d'avoir une bonne raison de faire autrement, il est plus sage de cr�er
	// l'arbre apr�s avoir cr�� le contexte OpenGL.
	tree_.initialiser();

	// On cr�e une vue par d�faut. 
	view_ = std::make_unique<vue::VueOrtho>(vue::Camera(
			glm::dvec3(0, 0, 10), glm::dvec3(0, 0, 0),
			glm::dvec3(0, 10, 0), glm::dvec3(0, 0, 1)),
			vue::ProjectionOrtho{
				0, 500, 0, 500,
				1, 1000, 1, 10000, 1.25,
				-50, 50, -50, 50, false });

	textDisplay_ = std::make_unique<AffichageTexte>(view_.get(), userProfile);
	isInitialized_ = true;
}

void SimulationEngine::free()
{
	tree_.vider();
	utilitaire::CompteurAffichage::libererInstance();

	bool succes{ aidegl::detruireContexteGL(hWnd_, hDC_, hGLRC_) };
	assert(succes && "Le contexte OpenGL n'a pu �tre d�truit.");

	FreeImage_DeInitialise();
	isInitialized_ = false;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::render() const
///
/// Cette fonction affiche le contenu de la sc�ne.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void SimulationEngine::render()
{
	if (!isInitialized_ || !isRendering_)
		return;
    
	// Efface l'ancien rendu
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);


    glInitNames();

	// Ne devrait pas �tre n�cessaire
	view_->appliquerProjection();


	// Positionne la cam�ra
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	view_->appliquerCamera();

	// obtenir la cloture pour ajuster la taille de l'environnement en fonction
	int xmin;
	int xmax;
	int ymin;
	int ymax;
	view_->obtenirProjection().obtenirCoordonneesCloture(xmin, xmax, ymin, ymax);

	
	// AfficherEnvironnement
	if (environnement_ != nullptr)
	{
		int horizontal = 0;
		int vertical = 0;
		glm::dvec3 centre(0.0);

		//Si nous sommes en vue orthogonale, ajustons le centre
		if (!view_->obtenirProjection().estPerspective()){
			glm::ivec2 centreProj = view_->obtenirCentreVue();
			centre.x += centreProj.x;
			centre.y += centreProj.y;
		}
			
		getDesktopResolution(horizontal, vertical);
		environnement_->afficher(centre, horizontal / 4);
	}
		

	// Positionner la lumi�re.
	glm::vec4 position{ 0, 0, 1, 0 };
	
	glm::vec4 zeroContribution{ 0.0f, 0.0f, 0.0f, 1 };
	glm::vec4 contributionMaximale{ 1.0, 1.0, 1.0, 1.0 };

	glLightfv(GL_LIGHT0, GL_POSITION, glm::value_ptr(position));
	// La plupart des mod�les export�s n'ont pas de composante ambiante. (Ka dans les mat�riaux .mtl)
	glLightfv(GL_LIGHT0, GL_AMBIENT, glm::value_ptr(zeroContribution));
	// On sature les objets de lumi�re
	glLightfv(GL_LIGHT0, GL_DIFFUSE, glm::value_ptr(contributionMaximale));
	// Pas de composante sp�culaire.
	glLightfv(GL_LIGHT0, GL_SPECULAR, glm::value_ptr(zeroContribution));

	EnginSon::obtenirInstance()->obtenirSystemeSon()->update();
	//Affiche la lumi�re directionnelle
	lightController_.afficherLumiereDirectionnelle();
	//controleurLumiere_->afficherLumiereSpotGyro();
	//controleurLumiere_->afficherLumiereSpotRobot();

	// Afficher la sc�ne.
	tree_.afficher(-1);

	// Compte de l'affichage
	utilitaire::CompteurAffichage::obtenirInstance()->signalerAffichage();

    textDisplay_->afficher();

	// �change les tampons pour que le r�sultat du rendu soit visible.
	::SwapBuffers(hDC_);
}

void SimulationEngine::stopRendering()
{

}

void SimulationEngine::resumeRendering()
{

}

void SimulationEngine::animate(double dt)
{
	tree_.animer(dt);
	view_->animer(dt);
}

//Assigne les parametres pour la vue ortho
void SimulationEngine::setOrthoView()
{
	view_ = std::make_unique<vue::VueOrtho>(
		vue::Camera(
			glm::dvec3(0, 0, 10), glm::dvec3(0, 0, 0),
			glm::dvec3(0, 10, 0), glm::dvec3(0, 0, 1)), 
		vue::ProjectionOrtho{
			0, 500, 0, 500,
			1, 1000, 80, 105, 1.25,
			-50, 50, -50, 50, false });
	textDisplay_->assignerVue(view_.get());
}

//Assigne les parametres pour la vue orbite
void SimulationEngine::setOrbitalView()
{
	view_ = std::make_unique<vue::VueOrbite>(
		vue::Camera(
			glm::dvec3(0, 0, 170), glm::dvec3(0, 0, 0),
			glm::dvec3(0, 10, 0), glm::dvec3(0, 0, 1)), 
		vue::ProjectionPerspective{
			0, 500, 0, 500,
			1, 10000, 1, 100000, 1.25,
			-50, 50, -50, 50, true }, false,false);
	textDisplay_->assignerVue(view_.get());
}

//Assigne les parametres pour la vue � la premi�re personne
void SimulationEngine::setFirstPersonView(NoeudAbstrait* entity)
{
	glm::dvec3 position = entity->getPhysicsComponent().absolutePosition;

	view_ = std::make_unique<vue::VueOrbite>(
		vue::Camera(
			glm::dvec3(position.x, position.y, 4), glm::dvec3(100, 0, 1),
			glm::dvec3(0, 0, 1), glm::dvec3(0, 0, 1)), 
		vue::ProjectionPerspective{
			0, 500, 0, 500,
			1, 10000, 10, 10000, 1.25,
			-50, 50, -50, 50, true }, true,false);
	textDisplay_->assignerVue(view_.get());
}

void SimulationEngine::setCloseOrbitalView()
{
	view_ = std::make_unique<vue::VueOrbite>(
		vue::Camera(
			glm::dvec3(0, 0, 25), glm::dvec3(0, 0, 0),
			glm::dvec3(0, 10, 0), glm::dvec3(0, 0, 1)),
		vue::ProjectionPerspective{
		0, 500, 0, 500,
		1, 10000, 1, 100000, 1.25,
		-50, 50, -50, 50, true }, false,true);
	//place la camera pour qu'elle est un bon angle sur le robot
	view_->deplacerXY(-375, 550);
	textDisplay_->assignerVue(view_.get());
}

void SimulationEngine::setEnvironnement(int environnementId)
{
	switch (environnementId)
	{
	case 0:
		environnement_ = std::make_unique<utilitaire::BoiteEnvironnement>(
			".\\media\\textures\\Skybox1\\posz.jpg", ".\\media\\textures\\Skybox1\\negz.jpg",
			".\\media\\textures\\Skybox1\\posx.jpg", ".\\media\\textures\\Skybox1\\negx.jpg",
			".\\media\\textures\\Skybox1\\negy.jpg", ".\\media\\textures\\Skybox1\\posy.jpg");
		break;

	case 1:
		environnement_ = std::make_unique<utilitaire::BoiteEnvironnement>(
			".\\media\\textures\\Skybox2\\posz.jpg", ".\\media\\textures\\Skybox2\\negz.jpg",
			".\\media\\textures\\Skybox2\\posx.jpg", ".\\media\\textures\\Skybox2\\negx.jpg",
			".\\media\\textures\\Skybox2\\negy.jpg", ".\\media\\textures\\Skybox2\\posy.jpg");
		break;

	default:
		environnement_ = nullptr;
		break;
	}
}

void SimulationEngine::getDesktopResolution(int& horizontal, int& vertical)
{
	RECT desktop;
	// Get a handle to the desktop window
	const HWND hDesktop = GetDesktopWindow();
	// Get the size of screen to the variable desktop
	GetWindowRect(hDesktop, &desktop);
	// The top left corner will have coordinates (0,0)
	// and the bottom right corner will have coordinates
	// (horizontal, vertical)
	horizontal = desktop.right;
	vertical = desktop.bottom;
}

}
