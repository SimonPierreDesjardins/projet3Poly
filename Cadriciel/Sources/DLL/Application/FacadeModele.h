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


#include <windows.h>
#include <string>
#include <memory>

#include "Vue.h"
#include "ArbreRenduINF2990.h"
#include "EtatAbstrait.h"
#include "ModeAbstrait.h"

class NoeudAbstrait;

///////////////////////////////////////////////////////////////////////////
/// @class FacadeModele
/// @brief Classe qui constitue une interface (une façade) sur l'ensemble
///        du modèle et des classes qui le composent.
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
   /// Libère l'instance unique de la classe.
   static void libererInstance();

   /// Crée un contexte OpenGL et initialise celui-ci.
   void initialiserOpenGL(HWND hWnd);
   /// Charge la configuration à partir d'un fichier XML.
   void chargerConfiguration() const;
   /// Enregistre la configuration courante dans un fichier XML.
   void enregistrerConfiguration() const;
   /// Libère le contexte OpenGL.
   void libererOpenGL();
   /// Affiche le contenu du modèle.
   void afficher() const;
   /// Affiche la base du contenu du modèle.
   void afficherBase() const;

   /// Modifie l'etat courant.
   void assignerEtat(Etat etat);
   // Obtenir l'etat courant.
   inline EtatAbstrait* obtenirEtat();

   /// Modifie l'etat courant.
   void assignerMode(Mode mode);
   // Obtenir l'etat courant.
   inline ModeAbstrait* obtenirMode();

   // Obtenir le nombre d'objet sélectionné
   int obtenirNombreSelection();

   // Obtient si le modèle est autorisé à recevoir des entrées utilisateurs. 
   inline bool obtenirAutorisationInputSouris() const; 
   // Assigne si le modèle est autorisé à recevoir des entrées utilisateurs. 
   inline void assignerAutorisationInputSouris(const bool& autorisation);

   inline bool obtenirAutorisationInputClavier() const;

   inline void assignerAutorisationInputClavier(const bool& autorisation);

   // Obtient l'angle de rotaion du noeud selectionné. 
   double obtenirAngleRotation();
   // Obtient le facteur de mise à échelle du noeud selectionné. 
   double obtenirFacteurMiseAEchelle();
   // Obtient la position relative en X du noeud selectionné.
   double obtenirPositionRelativeX();
   // Obtient la position relative en Y du noeud selectionné.
   double obtenirPositionRelativeY();

   // Assigne l'angle de rotaion du noeud selectionné. 
   void assignerAngleRotation(const double& angle);
   // Assigne le facteur de mise à échelle du noeud selectionné.
   void assignerFacteurMiseAEchelle(const double& facteurMiseAEchelle);
   // Assigne la position relative en x du noeud sélectionné.
   void assignerPositionRelativeX(const double& positionRelativeX);
   // Assigne la position relative en x du noeud sélectionné. 
   void assignerPositionRelativeY(const double& positionRelativeY);

   /// Retourne la vue courante.
   inline vue::Vue* obtenirVue();
   /// Retourne l'arbre de rendu.
   inline ArbreRenduINF2990* obtenirArbreRenduINF2990() const;
   /// Retourne l'arbre de rendu.
   inline ArbreRenduINF2990* obtenirArbreRenduINF2990();

   /// Réinitialise la scène.
   void reinitialiser();

   /// Anime la scène.
   void animer(float temps);
   void stopAffichage();
   void continuerAffichage();

private:
   /// Constructeur par défaut.
   FacadeModele() = default;

   bool peutAfficher_{true};
   bool autorisationInputSouris_{ true };
   bool autorisationInputClavier_{ true };
   /// Constructeur copie désactivé.
   FacadeModele(const FacadeModele&) = delete;
   /// Opérateur d'assignation désactivé.
   FacadeModele& operator =(const FacadeModele&) = delete;

   /// Nom du fichier XML dans lequel doit se trouver la configuration.
   static const std::string FICHIER_CONFIGURATION;

   /// Pointeur vers l'instance unique de la classe.
   static std::unique_ptr<FacadeModele> instance_;

   /// Poignée ("handle") vers la fenêtre où l'affichage se fait.
   HWND  hWnd_{ nullptr };
   /// Poignée ("handle") vers le contexte OpenGL.
   HGLRC hGLRC_{ nullptr };
   /// Poignée ("handle") vers le "device context".
   HDC   hDC_{ nullptr };

   /// Vue courante de la scène.
   std::unique_ptr<vue::Vue> vue_{ nullptr };
   /// Arbre de rendu contenant les différents objets de la scène.
   std::unique_ptr<ArbreRenduINF2990> arbre_{ nullptr };
   
   std::unique_ptr<EtatAbstrait> etat_{ nullptr };
   std::unique_ptr<ModeAbstrait> mode_{ nullptr };
};

////////////////////////////////////////////////////////////////////////
///
/// @fn inline std::shared_ptr<EtatAbstrait> FacadeModele::obtenirEtat()
///
/// Cette fonction retourne l'état dans lequel se trouve présentement
/// le modèle.
///
/// @return L'état courant.
///
////////////////////////////////////////////////////////////////////////
inline EtatAbstrait* FacadeModele::obtenirEtat()
{
	return etat_.get();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline std::shared_ptr<ModeAbstrait> FacadeModele::obtenirMode()
///
/// Cette fonction retourne le mode dans lequel se trouve présentement
/// le modèle.
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
/// Cette fonction retourne la vue qui est présentement utilisée pour
/// voir la scène.
///
/// @return La vue courante.
///
////////////////////////////////////////////////////////////////////////
inline vue::Vue* FacadeModele::obtenirVue()
{
   return vue_.get();
}

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
inline ArbreRenduINF2990* FacadeModele::obtenirArbreRenduINF2990() const
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
inline ArbreRenduINF2990* FacadeModele::obtenirArbreRenduINF2990()
{
   return arbre_.get();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn  bool obtenirAutorisationInput()
///
/// Retourne si oui ou non le modele prend présentement les entrées claviers utilisateurs
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
/// Assigne la valeur autorisation à la variable autorisationInputClavier_.
///
/// @param[in] autorisation : Si vrai, permet au modele de prendre les entrées claviers utilisateurs.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
inline void FacadeModele::assignerAutorisationInputClavier(const bool& autorisation)
{ 
	autorisationInputClavier_ = autorisation;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn  bool obtenirAutorisationInput()
///
/// Retourne si oui ou non le modele prend présentement les entrées souris sourisutilisateurs
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
/// Assigne la valeur autorisation à la variable autorisationInputSouris_.
///
/// @param[in] autorisation : Si vrai, permet au modele de prendre les entrées souris utilisateurs.
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
