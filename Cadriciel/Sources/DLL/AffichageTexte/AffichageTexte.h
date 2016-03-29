#ifndef AFFICHAGE_TEXTE_H
#define AFFICHAGE_TEXTE_H

#include <glm/glm.hpp>
#include <FTGL/ftgl.h>
#include <string>

namespace vue
{
    class Vue;
}

class AffichageTexte
{
public:
    AffichageTexte();
    ~AffichageTexte();

    void afficher();

    inline void assignerTempsEstAffiche(const bool& tempsEstAffiche);
    inline void assignerProfilEstAffiche(const bool& tempsEstAffiche);
    inline void assignerPositionTemps(const FTPoint& positionTemps);
    inline void assignerPositionProfil(const FTPoint&  positionProfil);

private:
    const char* FONT_PATH{"./media/font/Consolas.ttf"};
    const int OFFSET_X{ 25 };
    const int OFFSET_Y{ 50 };


    FTGLPixmapFont font_{FONT_PATH};

    bool tempsEstAffiche_{ false };
    bool profilEstAffiche_{ false };

    FTPoint positionProfil_{ 0.0, 0.0, 0.0 };
    FTPoint positionTemps_{ 0.0, 0.0, 0.0 };
    
    
    vue::Vue* vue_;
};


inline void AffichageTexte::assignerTempsEstAffiche(const bool& tempsEstAffiche)
{
    tempsEstAffiche_ = tempsEstAffiche;
}


inline void AffichageTexte::assignerProfilEstAffiche(const bool& profilEstAffiche)
{
    profilEstAffiche_ = profilEstAffiche;
}


inline void AffichageTexte::assignerPositionTemps(const FTPoint& positionTemps)
{
    positionTemps_ = positionTemps;
}

inline void AffichageTexte::assignerPositionProfil(const FTPoint&  positionProfil)
{
    positionProfil_ = positionProfil;
}

#endif // AFFICHAGE_TEXTE_H