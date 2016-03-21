///////////////////////////////////////////////////////////////////////////////
/// @file CercleEnglobant.cpp
/// @author Olivier St-Amour
/// @date 2015-02-14
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "CercleEnglobant.h"
#include "GL/glew.h"
#include "Utilitaire.h"
#include "RectangleEnglobant.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn CercleEnglobant::CercleEnglobant()
///
/// Constructeur par défaut de la classe
///
/// @param[in] Aucun.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
CercleEnglobant::CercleEnglobant()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn CercleEnglobant::CercleEnglobant(const glm::dvec3& positionCentre, const double& rayon)
///
/// Constructeur qui initialise les attributs de la classe.
///
/// @param[in]	positionCentre : position centrale du cercle englobant,
///				rayon : rayon du cercle englobant.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
CercleEnglobant::CercleEnglobant(const glm::dvec3& positionCentre, const double& rayon)
    : FormeEnglobanteAbstraite(positionCentre), rayon_(rayon)
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn CercleEnglobant::~CercleEnglobant()
///
/// Destructeur de la classe.
///
/// @param[in]	Aucun.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
CercleEnglobant::~CercleEnglobant()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn CercleEnglobant::initialiser(const utilitaire::BoiteEnglobante& boiteEnglobante)
///
/// Initialise les attributs de la classe selon la boiteEnglobante passée en paramètre.
///
/// @param[in]	boiteEnglobante : la boîte englobante à partir de laquelle on veut créer un cercleEnglobant.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void CercleEnglobant::initialiser(const utilitaire::BoiteEnglobante& boiteEnglobante)
{
    // Calcul des dimensions de la boite englobante.
    double hauteur = glm::abs(boiteEnglobante.coinMax.y - boiteEnglobante.coinMin.y);
    double largeur = glm::abs(boiteEnglobante.coinMax.x - boiteEnglobante.coinMin.x);
    // Le rayon est la dimension la plus grande.
    rayon_ = hauteur > largeur ? hauteur : largeur;
    rayon_ /= 2;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn CercleEnglobant::calculerEstDansLimites(const double& xMin, const double& xMax,
///												const double& yMin, const double& yMax)
///
/// Détermine si le cercle englobant est à l'intérieur de la zone passée en paramètre.
///
/// @param[in]	xMin : la valeur en x du coin minimum de la zone.
///				xMax : la valeur en x du coin maximum de la zone.
///				yMin : la valeur en y du coin minimum de la zone.
///				yMax : la valeur en y du coin maximum de la zone.
///
/// @return bool : indique si le cercle est dans la zone ou non.
///
////////////////////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////////////////////
///
/// @fn CercleEnglobant::mettreAJour(const glm::dvec3& positionCentre, const double& rayon)
///
/// Met à jour les attributs de la classe selon les données passées en paramètres.
///
/// @param[in]	positionCentre : position du centre du cercle englobant.
///				rayon : rayon du cercle englobant.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void CercleEnglobant::mettreAJour(const glm::dvec3& positionCentre, const double& rayon)
{
    positionCentre_ = positionCentre;
    rayon_ = rayon;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn CercleEnglobant::calculerEstDansForme(const glm::dvec3& point)
///
/// Détermine si le point passé en paramètre est dans le cercle englobant.
///
/// @param[in]	point : point dont on veut vérifier la position.
///
/// @return bool : indique si oui ou non le point se trouve dans le cercle englobant.
///
////////////////////////////////////////////////////////////////////////
bool CercleEnglobant::calculerEstDansForme(const glm::dvec3& point) const
{
	double distance = glm::distance(point, positionCentre_);
	return distance <= rayon_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn CercleEnglobant::calculerIntersection(const CercleEnglobant& cercle)
///
/// Détermine s'il y a intersection entre le cercle englobant actuel et celui passé en paramètre.
///
/// @param[in]	cercle : cercle avec lequel on veut vérifier l'intersection.
///
/// @return bool : indique si oui ou non il y a intersection entre les cercles englobants.
///
////////////////////////////////////////////////////////////////////////
bool CercleEnglobant::calculerIntersection(const CercleEnglobant& cercle) const
{
    glm::dvec3 distance = cercle.positionCentre_ - positionCentre_;
    double normeDistance = glm::length(distance);
    return cercle.rayon_ + rayon_ >= normeDistance;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn CercleEnglobant::calculerIntersection(const RectangleEnglobant& rectangle)
///
/// Détermine s'il y a intersection entre le cercle englobant actuel et le rectangle englobant passé en paramètre.
///
/// @param[in]	rectangle : rectangle avec lequel on veut vérifier l'intersection.
///
/// @return bool : indique si oui ou non il y a intersection entre le cercle englobant et le rectangle englobant.
///
////////////////////////////////////////////////////////////////////////
bool CercleEnglobant::calculerIntersection(const RectangleEnglobant& rectangle) const
{
    return false;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn CercleEnglobant::afficher()
///
/// Appelle la fonction afficher avec la table comme origine. 
///
/// @param[in]	Aucun.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void CercleEnglobant::afficher() const
{
    afficher({ 0.0, 0.0, 0.0 });
}

////////////////////////////////////////////////////////////////////////
///
/// @fn CercleEnglobant::afficher(const glm::dvec3& origine)
///
/// Affiche le cercle englobant autour de l'objet.
///
/// @param[in]	origine : point de repère selon lequel le cercle englobant est afficher.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////////////////////
///
/// @fn CercleEnglobant::calculerNormaleCollision(const RectangleEnglobant& rectangle) const
///
/// Calcule la normale de la collision.
///
/// @param[in]	rectangle : rectangle avec lequel la colision a eu lieu.
///
/// @return glm::dvec3 : vecteur qui représente la normale de la collision.
///
////////////////////////////////////////////////////////////////////////
glm::dvec3 CercleEnglobant::calculerNormaleCollision(const RectangleEnglobant& rectangle) const
{
    glm::dvec3 normale = rectangle.calculerNormaleCollision(*this);
    normale = -normale;
    return normale;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn CercleEnglobant::calculerNormaleCollision(const CercleEnglobant& cercle) const
///
/// Calcule la normale de la collision.
///
/// @param[in]	cercle : cercle avec lequel la colision a eu lieu.
///
/// @return glm::dvec3 : vecteur qui représente la normale de la collision.
///
////////////////////////////////////////////////////////////////////////
glm::dvec3 CercleEnglobant::calculerNormaleCollision(const CercleEnglobant& cercle) const
{
    return{ 0.0, 0.0, 0.0 };
}

////////////////////////////////////////////////////////////////////////
///
/// @fn CercleEnglobant::calculerNormaleCollision(const glm::dvec3& point) const
///
/// Calcule la normale de la collision.
///
/// @param[in]	point : point avec lequel la colision a eu lieu.
///
/// @return glm::dvec3 : vecteur qui représente la normale de la collision.
///
////////////////////////////////////////////////////////////////////////
glm::dvec3 CercleEnglobant::calculerNormaleCollision(const glm::dvec3& point) const
{
    return{ 0.0, 0.0, 0.0 };
}