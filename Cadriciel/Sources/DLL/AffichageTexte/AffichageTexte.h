#ifndef AFFICHAGE_TEXTE_H
#define AFFICHAGE_TEXTE_H

#include <string>
#include <chrono>
#include <ctime>
#include <glm/glm.hpp>
#include <FTGL/ftgl.h>

namespace vue
{
    class Vue;
}

class ProfilUtilisateur;

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

inline void AffichageTexte::assignerTempsEstAffiche(const bool& tempsEstAffiche)
{
    tempsEstAffiche_ = tempsEstAffiche;
}

inline void AffichageTexte::assignerProfilEstAffiche(const bool& profilEstAffiche)
{
    profilEstAffiche_ = profilEstAffiche;
}

#endif // AFFICHAGE_TEXTE_H