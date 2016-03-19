#include "CercleEnglobant.h"
#include "GL/glew.h"
#include "Utilitaire.h"
#include "RectangleEnglobant.h"


#include <iostream>


CercleEnglobant::CercleEnglobant()
{
}


CercleEnglobant::CercleEnglobant(const glm::dvec3& positionCentre, const double& rayon)
    : FormeEnglobanteAbstraite(positionCentre), rayon_(rayon)
{
}


CercleEnglobant::~CercleEnglobant()
{
}


void CercleEnglobant::initialiser(const utilitaire::BoiteEnglobante& boiteEnglobante)
{
    // Calcul des dimensions de la boite englobante.
    double hauteur = glm::abs(boiteEnglobante.coinMax.y - boiteEnglobante.coinMin.y);
    double largeur = glm::abs(boiteEnglobante.coinMax.x - boiteEnglobante.coinMin.x);
    // Le rayon est la dimension la plus grande.
    rayon_ = hauteur > largeur ? hauteur : largeur;
    rayon_ /= 2;
}

bool CercleEnglobant::calculerEstDansLimites(const double& xMin, const double& xMax,
                                             const double& yMin, const double& yMax) const
{
    const int N_COINS = 4;
    glm::dvec3 coins[N_COINS];
    coins[0] = { positionCentre_.x + rayon_, positionCentre_.y + rayon_, 0.0};
    coins[1] = { positionCentre_.x - rayon_, positionCentre_.y + rayon_, 0.0};
    coins[2] = { positionCentre_.x - rayon_, positionCentre_.y - rayon_, 0.0};
    coins[3] = { positionCentre_.x + rayon_, positionCentre_.y - rayon_, 0.0};

    bool coinsDansLimite = true;
    for (int i = 0; i < N_COINS && coinsDansLimite; i++)
    {
        coinsDansLimite = utilitaire::DANS_LIMITESXY(coins[i].x, xMin, xMax,
                                                     coins[i].y, yMin, yMax);
    }
    return coinsDansLimite;

}

void CercleEnglobant::mettreAJour(const glm::dvec3& positionCentre, const double& rayon)
{
    positionCentre_ = positionCentre;
    rayon_ = rayon;
}


bool CercleEnglobant::calculerEstDansForme(const glm::dvec3& point) const
{
	double distance = glm::distance(point, positionCentre_);
	return distance <= rayon_;
}

bool CercleEnglobant::calculerIntersection(const CercleEnglobant& cercle) const
{
    return false;
}


bool CercleEnglobant::calculerIntersection(const RectangleEnglobant& rectangle) const
{
    return false;
}


void CercleEnglobant::afficher() const
{
    afficher({ 0.0, 0.0, 0.0 });
}


void CercleEnglobant::afficher(const glm::dvec3& origine) const
{

    glm::dvec3 positionRelative = positionCentre_ - origine;
    int nSegments = 360;
    float theta = 2 * (float)utilitaire::PI / (float)(nSegments);
    float facteurTangentiel = tanf(theta);
    float facteurAngulaire = cosf(theta);
    float x = (float)rayon_;
    float y = 0.0;

    glPushMatrix();

    glTranslated(positionRelative.x, positionRelative.y, positionRelative.z);

    if (!enCollision_)
    {
        glColor3f(1.0, 0.0, 0.0);
    }
    else
    {
        glColor3f(0.0, 1.0, 0.0);
    }

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++)
    {
        glVertex3f(x, y, 5.0);
        // Obtenir la perpendiculaire. 
        float tx = -y;
        float ty = x;

        x += tx * facteurTangentiel;
        y += ty * facteurTangentiel;

        x *= facteurAngulaire;
        y *= facteurAngulaire;
    }
    glEnd();
    glPopMatrix();
}

bool CercleEnglobant::calculerCollision(const RectangleEnglobant& rectangle, glm::dvec3& normale) const
{
    bool collision = rectangle.calculerCollision(*this, normale);
    normale = -normale;
    return collision;
}

bool CercleEnglobant::calculerCollision(const CercleEnglobant& rectangle, glm::dvec3& normale) const
{
    return false;
}