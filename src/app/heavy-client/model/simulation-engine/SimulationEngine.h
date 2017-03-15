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
	SimulationEngine();
	~SimulationEngine();

	// Crée un contexte OpenGL et initialise celui-ci.
	void initialiserOpenGL(HWND hWnd);

	// Retourne la vue courante.
	inline vue::Vue* obtenirVue();
	//Assigne les parametres pour la vue ortho
	void assignerVueOrtho();
	//Assigne les parametres pour la vue orbite
	void assignerVueOrbite();

	void assignerVueOrbitePerso();

	//Assigne les parametres pour la vue à la première personne
	void assignerVuePremierePersonne();

	// Retourne l'arbre de rendu.
	inline ArbreRenduINF2990* obtenirArbreRenduINF2990() const;

	// Retourne l'arbre de rendu.
	inline ArbreRenduINF2990* obtenirArbreRenduINF2990();

	// Retourne l'affichage du texte.
	inline AffichageTexte* obtenirAffichageTexte() const;
	// Retourne le controleur de lumière.
	inline ControleurLumiere* obtenirControleurLumiere() const;


private:
	std::unique_ptr<ArbreRenduINF2990> arbre_{ nullptr };

	std::unique_ptr<vue::Vue> vue_{ nullptr };

	// La boite qui donne un environnement
	std::unique_ptr<utilitaire::BoiteEnvironnement> environnement_{ nullptr };

	// Le controle de l'affichage du texte.
	std::unique_ptr<AffichageTexte> affichageTexte_{ nullptr };

	// Le controle de l'affichage des lumières.
	std::unique_ptr<ControleurLumiere> controleurLumiere_{ nullptr };

};

////////////////////////////////////////////////////////////////////////
///
/// @fn inline const shared_ptr<ArbreRenduINF2990> FacadeModele::obtenirArbreRenduINF2990() const
///
/// Cette fonction retourne l'arbre de rendu de la scène (version constante
/// de la fonction).
///
/// @return L'arbre de rendu de la scène.
///
////////////////////////////////////////////////////////////////////////
inline ArbreRenduINF2990* SimulationEngine::obtenirArbreRenduINF2990() const
{
   return arbre_.get();
}

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
inline ArbreRenduINF2990* SimulationEngine::obtenirArbreRenduINF2990()
{
   return arbre_.get();
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
inline vue::Vue* SimulationEngine::obtenirVue()
{
   return vue_.get();
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
inline AffichageTexte* SimulationEngine::obtenirAffichageTexte() const
{
    return affichageTexte_.get();
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
inline ControleurLumiere* SimulationEngine::obtenirControleurLumiere() const
{
	return controleurLumiere_.get();
}

}

#endif // SIMULATION_ENGINE_H