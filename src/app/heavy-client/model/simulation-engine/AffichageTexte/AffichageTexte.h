///////////////////////////////////////////////////////////////////////////
/// @file AffichageTexte.h
/// @author Olivier St-Amour
/// @date 2016-03-29
/// @version 3.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef AFFICHAGE_TEXTE_H
#define AFFICHAGE_TEXTE_H

#include <chrono>
#include <FTGL/ftgl.h>

namespace vue
{
    class Vue;
}

class ProfilUtilisateur;

///////////////////////////////////////////////////////////////////////////
/// @class AffichageTexte
/// @brief Classe qui permet de faire l'affichage OpenGL.
///
///        Cette classe permet de faire l'affichage du chronomètre ainsi 
///        que le nom du profil courant.   
///	       
/// 
/// @author Olivier St-Amour
/// @date 2016-03-29
///////////////////////////////////////////////////////////////////////////
class AffichageTexte
{
public:
    AffichageTexte(vue::Vue* vue, ProfilUtilisateur* profil);
    ~AffichageTexte();

	inline void assignerVue(vue::Vue* vue); 

    void afficher();

    void demarrerChrono();
    void pauseChrono();
    void reinitialiserChrono();

    inline void assignerTempsEstAffiche(const bool& tempsEstAffiche);
    inline void assignerProfilEstAffiche(const bool& tempsEstAffiche);

	double obtenirDuree();

	void assignerPiecesEstAfficher(bool estAffiche);
	void assignerFinModePiecesEstAfficher(bool estAffiche);
	void assignerAvantDebutCourse(bool estAffiche);
	void assignerTempsFinal(bool estAffiche);
	bool obtenirTempsFinal();

private:
    const char* FONT_PATH{"./media/font/Consolas.ttf"};
	const char* FONT_PATH_CENTURY{ "./media/font/CenturyGothic.ttf" };
    const int OFFSET_X{ 25 };
    const int OFFSET_Y{ 50 };

    vue::Vue* vue_{ nullptr };
    ProfilUtilisateur* profil_{ nullptr };

    FTGLPixmapFont font_{FONT_PATH};
	FTGLPixmapFont fontCentury_{ FONT_PATH_CENTURY };

    bool tempsEstAffiche_{ false };
    bool profilEstAffiche_{ false };
	bool piecesEstAffiche_{ false };
	bool finModePieces_{ false };
    bool enPause_{ true };
	bool avantDebutCourse_{ false };
	bool tempsFinal_{ false };

	double duree_{ 0.0 };

    std::chrono::time_point<std::chrono::system_clock> debut_, pause_;

    AffichageTexte() = delete;
};


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void AffichageTexte::assignerTempsEstAffiche(const bool& tempsEstAffiche)
///
/// Fonction qui permet d'assigner le boolean qui indique si l'affichage 
/// du temps est réalisé.
///
/// @param[in] tempsEstAffiche : le boolean qui indique si l'affichage est réalisé.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
inline void AffichageTexte::assignerTempsEstAffiche(const bool& tempsEstAffiche)
{
    tempsEstAffiche_ = tempsEstAffiche;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void AffichageTexte::assignerProfilEstAffiche(const bool& profilEstAffiche)
///
/// Fonction qui permet d'assigner le boolean qui indique sur l'affichage 
/// du profil courant est réalisé.
///
/// @param[in] tempsEstAffiche : le boolean qui indique si l'affichage est réalisé.
/// 
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
inline void AffichageTexte::assignerProfilEstAffiche(const bool& profilEstAffiche)
{
    profilEstAffiche_ = profilEstAffiche;
}

////////////////////////////////////////////////////////////////////////
//
// @fn inline void AffichageTexte::assignerVue(vue::Vue* vue)
//
// Fonction qui permet d'assigner la vue courante de la façade modèle.
//
// @param[in] vue : Un pointeur sur la vue.
//
////////////////////////////////////////////////////////////////////////
inline void AffichageTexte::assignerVue(vue::Vue* vue)
{
	vue_ = vue;
}

#endif // AFFICHAGE_TEXTE_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////