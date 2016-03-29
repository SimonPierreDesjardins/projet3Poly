#include "AffichageTexte.h"
#include <FTGL/ftgl.h>
#include <Windows.h>
#include "FacadeModele.h"
#include "ProjectionOrtho.h"


AffichageTexte::AffichageTexte()
{
    assert(!font_.Error());
    font_.FaceSize(16);
    vue_ = FacadeModele::obtenirInstance()->obtenirVue();
}

AffichageTexte::~AffichageTexte()
{
}

void AffichageTexte::afficher()
{
    glm::ivec2 dimensions = vue_->obtenirProjection().obtenirDimensionCloture();
    
    FTPoint positionProfil(OFFSET_X, dimensions.y - OFFSET_Y, 0.0);
    FTPoint positionTemps(OFFSET_X, OFFSET_Y, 0.0);

    glPushAttrib(GL_ALL_ATTRIB_BITS);

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    glColor3f(1.0, 1.0, 1.0);

    if (profilEstAffiche_)
    {
        font_.Render("profil", -1, positionProfil);
    }
    if (tempsEstAffiche_)
    {
        font_.Render("temps", -1, positionTemps);
    }
    glPopAttrib();
}
