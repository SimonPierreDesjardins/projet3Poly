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
///        Cette classe permet de faire l'affichage du chronom�tre ainsi 
///        que le nom du profil courant.   
///	       
/// 
/// @author Olivier St-Amour
/// @date 2016-03-29
///////////////////////////////////////////////////////////////////////////
class AffichageTexte
{
public:
    AffichageTexte();
    ~AffichageTexte();

    void afficher();

    void demarrerChrono();
    void pauseChrono();
    void reinitialiserChrono();

    inline void assignerTempsEstAffiche(const bool& tempsEstAffiche);
    inline void assignerProfilEstAffiche(const bool& tempsEstAffiche);

private:
    const char* FONT_PATH{"./media/font/Consolas.ttf"};
    const int OFFSET_X{ 25 };
    const int OFFSET_Y{ 50 };

    vue::Vue* vue_{ nullptr };
    ProfilUtilisateur* profil_{ nullptr };

    FTGLPixmapFont font_{FONT_PATH};

    bool tempsEstAffiche_{ false };
    bool profilEstAffiche_{ false };
    bool enPause_{ true };

    std::chrono::time_point<std::chrono::system_clock> debut_, pause_;
};


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void AffichageTexte::assignerTempsEstAffiche(const bool& tempsEstAffiche)
///
/// Fonction qui permet d'assigner le boolean qui indique si l'affichage 
/// du temps est r�alis�.
///
/// @param[in] tempsEstAffiche : le boolean qui indique si l'affichage est r�alis�.
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
/// du profil courant est r�alis�.
///
/// @param[in] tempsEstAffiche : le boolean qui indique si l'affichage est r�alis�.
/// 
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
inline void AffichageTexte::assignerProfilEstAffiche(const bool& profilEstAffiche)
{
    profilEstAffiche_ = profilEstAffiche;
}

#endif // AFFICHAGE_TEXTE_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////