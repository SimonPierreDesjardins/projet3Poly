///////////////////////////////////////////////////////////////////////////////
/// @file FormeEnglobanteAbstraite.cpp
/// @author Olivier St-Amour
/// @date 2015-02-14
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "FormeEnglobanteAbstraite.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn FormeEnglobanteAbstraite::FormeEnglobanteAbstraite()
///
/// Constructeur par défaut de la classe
///
/// @param[in] Aucun.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
FormeEnglobanteAbstraite::FormeEnglobanteAbstraite()
{
    positionCentre_ = { 0.0, 0.0, 0.0 };
}

////////////////////////////////////////////////////////////////////////
///
/// @fn FormeEnglobanteAbstraite::FormeEnglobanteAbstraite(const glm::dvec3& positionCentre)
///
/// Constructeur qui initialise les attributs de la classe.
///
/// @param[in]	positionCentre : position du centre de la forme englobante.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
FormeEnglobanteAbstraite::FormeEnglobanteAbstraite(const glm::dvec3& positionCentre) 
    : positionCentre_(positionCentre)
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn FormeEnglobanteAbstraite::~FormeEnglobanteAbstraite()
///
/// Destructeur de la classe.
///
/// @param[in]	Aucun.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
FormeEnglobanteAbstraite::~FormeEnglobanteAbstraite()
{
}