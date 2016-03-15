#include "FormeEnglobanteAbstraite.h"


FormeEnglobanteAbstraite::FormeEnglobanteAbstraite()
{
    positionCentre_ = { 0.0, 0.0, 0.0 };
}

FormeEnglobanteAbstraite::FormeEnglobanteAbstraite(const glm::dvec3& positionCentre) 
    : positionCentre_(positionCentre)
{
}

FormeEnglobanteAbstraite::~FormeEnglobanteAbstraite()
{
}