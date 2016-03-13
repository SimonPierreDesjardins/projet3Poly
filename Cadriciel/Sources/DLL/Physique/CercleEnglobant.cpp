#include "CercleEnglobant.h"

// Constructeur par défaut.
CercleEnglobant::CercleEnglobant()
{
}
// Constructeur par paramètres.
CercleEnglobant::CercleEnglobant(const glm::dvec3& positionCentre, const double& rayon)
    : FormeEnglobanteAbstraite(positionCentre), rayon_(rayon)
{
}
// Destructeur.
CercleEnglobant::~CercleEnglobant()
{
}

bool CercleEnglobant::calculerPointEstDansForme(const glm::dvec3& point) const
{
    return true;
}


bool CercleEnglobant::calculerIntersection(const CercleEnglobant& cercle) const
{
    return true;
}


bool CercleEnglobant::calculerIntersection(const RectangleEnglobant& rectangle) const
{
    return true;
}


void CercleEnglobant::mettreAJour(const glm::dvec3& positionCentre, 
    const double& rayon)
{
    rayon_ = rayon;
    positionCentre_ = positionCentre;
}

