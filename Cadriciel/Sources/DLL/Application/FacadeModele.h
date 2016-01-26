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

class NoeudAbstrait;
class ArbreRenduINF2990;
class EtatAbstrait;

namespace vue {
   class Vue;
}


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
   static std::shared_ptr<FacadeModele> obtenirInstance();
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
   void modifierEtat(std::shared_ptr<EtatAbstrait> etat);
   // Obtenir l'etat courant.
   inline std::shared_ptr<EtatAbstrait> obtenirEtat();

   /// Retourne la vue courante.
   inline std::shared_ptr<vue::Vue> obtenirVue();
   /// Retourne l'arbre de rendu.
   inline std::shared_ptr<ArbreRenduINF2990> obtenirArbreRenduINF2990() const;
   /// Retourne l'arbre de rendu.
   inline std::shared_ptr<ArbreRenduINF2990> obtenirArbreRenduINF2990();

   /// Réinitialise la scène.
   void reinitialiser();

   /// Anime la scène.
   void animer(float temps);


private:
   /// Constructeur par défaut.
   FacadeModele() = default;

   /// Constructeur copie désactivé.
   FacadeModele(const FacadeModele&) = delete;
   /// Opérateur d'assignation désactivé.
   FacadeModele& operator =(const FacadeModele&) = delete;

   /// Nom du fichier XML dans lequel doit se trouver la configuration.
   static const std::string FICHIER_CONFIGURATION;

   /// Pointeur vers l'instance unique de la classe.
   static std::shared_ptr<FacadeModele> instance_;

   /// Poignée ("handle") vers la fenêtre où l'affichage se fait.
   HWND  hWnd_{ nullptr };
   /// Poignée ("handle") vers le contexte OpenGL.
   HGLRC hGLRC_{ nullptr };
   /// Poignée ("handle") vers le "device context".
   HDC   hDC_{ nullptr };

   /// Vue courante de la scène.
   std::shared_ptr<vue::Vue> vue_{ nullptr };
   /// Arbre de rendu contenant les différents objets de la scène.
   std::shared_ptr<ArbreRenduINF2990> arbre_{ nullptr };
   
   std::shared_ptr<EtatAbstrait> etat_{ nullptr };
  
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
inline std::shared_ptr<EtatAbstrait> FacadeModele::obtenirEtat()
{
	return etat_;
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
inline std::shared_ptr<vue::Vue> FacadeModele::obtenirVue()
{
   return vue_;
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
inline std::shared_ptr<ArbreRenduINF2990> FacadeModele::obtenirArbreRenduINF2990() const
{
   return arbre_;
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
inline std::shared_ptr<ArbreRenduINF2990> FacadeModele::obtenirArbreRenduINF2990()
{
   return arbre_;
}


#endif // __APPLICATION_FACADEMODELE_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
