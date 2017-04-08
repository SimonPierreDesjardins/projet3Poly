#ifndef SIMULATION_ENGINE_H
#define SIMULATION_ENGINE_H

#include "Vue.h"
#include "Camera.h"
#include "OpenGL_Programme.h"
#include "OpenGL_Nuanceur.h"
#include "ArbreRenduINF2990.h"

#include "BoiteEnvironnement.h"
#include "AffichageTexte.h"
#include "ControleurLumiere.h"

namespace engine
{

class SimulationEngine
{
public:
	SimulationEngine() = default;
	~SimulationEngine();

	void initialize();

	void initializeRendering(HWND hWnd, ProfilUtilisateur* profile);
	void free();

	void setOrthoView();
	void setOrbitalView();
	void setFirstPersonView(NoeudAbstrait* entity);
	void setCloseOrbitalView();
	void setEnvironnement(int environnementId);

	inline ArbreRenduINF2990* getEntityTree();
	inline AffichageTexte* getTextDisplay();
	inline ControleurLumiere* getLightController();
	inline vue::Vue* getView();

	void getDesktopResolution(int& horizontal, int& vertical);

	void render();
	void animate(double dt);
	void stopRendering();
	void resumeRendering();

private:

	bool isInitialized_{ false };
	bool isRendering_{ false };
	/// Poignée ("handle") vers la fenêtre où l'affichage se fait.
	HWND  hWnd_{ nullptr };
	/// Poignée ("handle") vers le contexte OpenGL.
	HGLRC hGLRC_{ nullptr };
	/// Poignée ("handle") vers le "device context".
	HDC   hDC_{ nullptr };

	ArbreRenduINF2990 tree_;
	std::unique_ptr<vue::Vue> view_{ nullptr };
	// La boite qui donne un environnement

	std::vector<utilitaire::BoiteEnvironnement> environnements_;
	utilitaire::BoiteEnvironnement* environnementCourant_ = nullptr;

	// Le controle de l'affichage du texte.
	std::unique_ptr<AffichageTexte> textDisplay_{ nullptr };
	// Le controle de l'affichage des lumières.
	ControleurLumiere lightController_;
};

////////////////////////////////////////////////////////////////////////
///
/// @fn inline shared_ptr<ArbreRenduINF2990> FacadeModele::obtenirArbreRenduINF2990()
///
/// Cette fonction retourne l'arbre de rendu de la scène (version non constante
/// de la fonction).
///
/// @return L'arbre de rendu de la scène.
///
////////////////////////////////////////////////////////////////////////
inline ArbreRenduINF2990* SimulationEngine::getEntityTree()
{
	return &tree_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline vue::Vue* FacadeModele::obtenirVue()
///
/// Cette fonction retourne la vue qui est présentement utilisée pour
/// voir la scène.
///
/// @return La vue courante.
///
////////////////////////////////////////////////////////////////////////
inline vue::Vue* SimulationEngine::getView()
{
   return view_.get();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline AffichageTexte* SimulationEngine::obtenirAffichageTexte() const
///
/// Cette fonction retourne le module qui gère l'affichage du texte.
///
/// @return L'arbre de rendu de la scène.
///
////////////////////////////////////////////////////////////////////////
inline AffichageTexte* SimulationEngine::getTextDisplay()
{
    return textDisplay_.get();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline ControleurLumiere* SimulationEngine::obtenirControleurLumiere() const
///
/// Cette fonction retourne le module qui gère l<affichage de la lumiere
///
/// @return le controleur de lumiere.
///
////////////////////////////////////////////////////////////////////////
inline ControleurLumiere* SimulationEngine::getLightController()
{
	return &lightController_;
}

}

#endif // SIMULATION_ENGINE_H