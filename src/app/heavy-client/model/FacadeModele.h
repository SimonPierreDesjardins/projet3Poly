//////////////////////////////////////////////////////////////////////////////
/// @file FacadeModele.h
/// @author DGI
/// @date 2005-06-15
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef __APPLICATION_FACADEMODELE_H__
#define __APPLICATION_FACADEMODELE_H__

#include <string>
#include <memory>

#include "Vue.h"
#include "Camera.h"
#include "OpenGL_Programme.h"
#include "OpenGL_Nuanceur.h"

#include "EtatAbstrait.h"
#include "ModeAbstrait.h"
#include "ProfilUtilisateur.h"

#include "MapSessionManager.h"
#include "NetworkManager.h"
#include "EventHandler.h"

#include "SimulationEngine.h"

class NoeudAbstrait;
class OnlineMapMode;
class ArbreRenduINF2990;
class AffichageTexte;
class ControleurLumiere;

///////////////////////////////////////////////////////////////////////////
/// @class FacadeModele
/// @brief Classe qui constitue une interface (une fa�ade) sur l'ensemble
///        du mod�le et des classes qui le composent.
///
/// @author Martin Bisson
/// @date 2007-02-20
///////////////////////////////////////////////////////////////////////////
class FacadeModele
{
public:

	/// Destructeur.
	~FacadeModele();

	/// Obtient l'instance unique de la classe.
	static FacadeModele* obtenirInstance();
	/// Lib�re l'instance unique de la classe.
	static void libererInstance();

	void initialize(HWND hWnd);

	/// Cr�e un contexte OpenGL et initialise celui-ci.
	void initialiserOpenGL(HWND hWnd);

	void libererOpenGL();

	void repartirMessage(UINT msg, WPARAM wParam, LPARAM lParam);

	/// Affiche le contenu du mod�le.
	void afficher();

	/// Modifie le Mode courant.
	void assignerMode(Mode mode);
	/// Modifie le mode courant pour un mode en ligne avec une session utilisateur.
	void setOnlineMapMode(Mode mode, client_network::MapSession* mapSession);

	// Obtenir le Mode courant.
	inline ModeAbstrait* obtenirMode();

	// Obtient si le mod�le est autoris� � recevoir des entr�es utilisateurs. 
	inline bool obtenirAutorisationInputSouris() const; 
	// Assigne si le mod�le est autoris� � recevoir des entr�es utilisateurs. 
	inline void assignerAutorisationInputSouris(const bool& autorisation);

	inline bool obtenirAutorisationInputClavier() const;

	inline void assignerAutorisationInputClavier(const bool& autorisation);

	/// Retourne la vue courante.
	inline vue::Vue* obtenirVue();

	//Assigne les parametres pour la vue ortho
	void assignerVueOrtho();
	//Assigne les parametres pour la vue orbite
	void assignerVueOrbite();
	void assignerVueOrbitePerso();
	//Assigne les parametres pour la vue � la premi�re personne
	void assignerVuePremierePersonne();

	/// Retourne l'arbre de rendu.
	inline ArbreRenduINF2990* obtenirArbreRenduINF2990();
	/// Retourne le profil de l'utilisateur.
	inline ProfilUtilisateur* obtenirProfilUtilisateur();
	// Retourne l'affichage du texte.
	inline AffichageTexte* obtenirAffichageTexte();
	// Retourne le controleur de lumi�re.
	inline ControleurLumiere* obtenirControleurLumiere();
	// Retourne le gestionnaire de la connection r�seau
	inline client_network::NetworkManager* getNetworkManager();
	// Retourne le gestionnaire d'evenements
	inline event_handler::EventHandler* getEventHandler();

	/// R�initialise la sc�ne.
	void reinitialiser();

	/// Anime la sc�ne.
	void animer(float temps);
	void stopAffichage();
	void continuerAffichage();

	/// Assigne un skybox � rendre
	void assignerEnvironnement(int noEnviro);

	/// Retourne la dimension de l'�cran
	void getDesktopResolution(int& horizontal, int& vertical);

private:
	bool peutAfficher_{ true };
	bool autorisationInputSouris_{ true };
	bool autorisationInputClavier_{ true };
	/// Constructeur copie d�sactiv�.
	FacadeModele(const FacadeModele&) = delete;
	/// Op�rateur d'assignation d�sactiv�.
	FacadeModele& operator =(const FacadeModele&) = delete;

	/// Nom du fichier XML dans lequel doit se trouver la configuration.
	static const std::string FICHIER_CONFIGURATION;

	/// Pointeur vers l'instance unique de la classe.
	static std::unique_ptr<FacadeModele> instance_;

	/// Poign�e ("handle") vers la fen�tre o� l'affichage se fait.
	HWND  hWnd_{ nullptr };
	/// Poign�e ("handle") vers le contexte OpenGL.
	HGLRC hGLRC_{ nullptr };
	/// Poign�e ("handle") vers le "device context".
	HDC   hDC_{ nullptr };

	event_handler::EventHandler eventHandler_;
	client_network::MapSessionManager mapSessionManager_;
    client_network::NetworkManager network_;

	engine::SimulationEngine engine_;

	/// Le mode d'utilisation courant.
	std::unique_ptr<ModeAbstrait> mode_{ nullptr };

	/// Le profil utilisateur.
	ProfilUtilisateur profil_;

	FacadeModele();
};

////////////////////////////////////////////////////////////////////////
///
/// @fn inline std::shared_ptr<ModeAbstrait> FacadeModele::obtenirMode()
///
/// Cette fonction retourne le mode dans lequel se trouve pr�sentement
/// le mod�le.
///
/// @return le mode courant.
///
////////////////////////////////////////////////////////////////////////
inline ModeAbstrait* FacadeModele::obtenirMode()
{
	return mode_.get();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline vue::Vue* FacadeModele::obtenirVue()
///
/// Cette fonction retourne la vue qui est pr�sentement utilis�e pour
/// voir la sc�ne.
///
/// @return La vue courante.
///
////////////////////////////////////////////////////////////////////////
inline vue::Vue* FacadeModele::obtenirVue()
{
	return engine_.getView();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline shared_ptr<ArbreRenduINF2990> FacadeModele::obtenirArbreRenduINF2990()
///
/// Cette fonction retourne l'arbre de rendu de la sc�ne (version non constante
/// de la fonction).
///
/// @return L'arbre de rendu de la sc�ne.
///
////////////////////////////////////////////////////////////////////////
inline ArbreRenduINF2990* FacadeModele::obtenirArbreRenduINF2990()
{
	return engine_.getEntityTree();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline ProfilUtilisateur* FacadeModele::obtenirProfilUtilisateur()
///
/// Cette fonction retourne le profil courant de l'utilisateur 
///
/// @return L'arbre de rendu de la sc�ne.
///
////////////////////////////////////////////////////////////////////////
ProfilUtilisateur* FacadeModele::obtenirProfilUtilisateur()
{
	return &profil_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline AffichageTexte* FacadeModele::obtenirAffichageTexte() const
///
/// Cette fonction retourne le module qui g�re l'affichage du texte.
///
/// @return L'arbre de rendu de la sc�ne.
///
////////////////////////////////////////////////////////////////////////
inline AffichageTexte* FacadeModele::obtenirAffichageTexte()
{
	return engine_.getTextDisplay();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline ControleurLumiere* FacadeModele::obtenirControleurLumiere() const
///
/// Cette fonction retourne le module qui g�re l<affichage de la lumiere
///
/// @return le controleur de lumiere.
///
////////////////////////////////////////////////////////////////////////
inline ControleurLumiere* FacadeModele::obtenirControleurLumiere()
{
	return engine_.getLightController();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn  bool obtenirAutorisationInput()
///
/// Retourne si oui ou non le modele prend pr�sentement les entr�es claviers utilisateurs
///
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
inline bool FacadeModele::obtenirAutorisationInputClavier() const
{
	return autorisationInputClavier_; 
}

////////////////////////////////////////////////////////////////////////
///
/// @fn  bool obtenirAutorisationInput()
///
/// Assigne la valeur autorisation � la variable autorisationInputClavier_.
///
/// @param[in] autorisation : Si vrai, permet au modele de prendre les entr�es claviers utilisateurs.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
inline void FacadeModele::assignerAutorisationInputClavier(const bool& autorisation)
{ 
	autorisationInputClavier_ = autorisation;
}

inline client_network::NetworkManager* FacadeModele::getNetworkManager()
{
	return &network_;
}

inline event_handler::EventHandler* FacadeModele::getEventHandler()
{
	return &eventHandler_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn  bool obtenirAutorisationInput()
///
/// Retourne si oui ou non le modele prend pr�sentement les entr�es souris sourisutilisateurs
///
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
bool FacadeModele::obtenirAutorisationInputSouris() const 
{ 
	return autorisationInputSouris_; 
}

////////////////////////////////////////////////////////////////////////
///
/// @fn  void assignerAutorisationInputSouris(bool autorisation)
///
/// Assigne la valeur autorisation � la variable autorisationInputSouris_.
///
/// @param[in] autorisation : Si vrai, permet au modele de prendre les entr�es souris utilisateurs.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::assignerAutorisationInputSouris(const bool& autorisation)
{ 
	autorisationInputSouris_ = autorisation; 
}


#endif // __APPLICATION_FACADEMODELE_H__

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
