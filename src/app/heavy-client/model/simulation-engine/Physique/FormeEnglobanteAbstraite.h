///////////////////////////////////////////////////////////////////////////////
/// @file FormeEnglobanteAbstraite.h
/// @author Olivier St-Amour
/// @date 2016-03-02
/// @version 2.4
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#ifndef FORME_ENGLOBANTE_ABSTRAITE_H
#define FORME_ENGLOBANTE_ABSTRAITE_H

#include <glm/glm.hpp> 
#include <vector>

namespace utilitaire
{
    struct BoiteEnglobante;
}

class RectangleEnglobant;
class CercleEnglobant;

///////////////////////////////////////////////////////////////////////////
/// @class FormeEnglobante
/// @brief Classe abstraite d'une forme servant � englober un noeud.
///
///        Cette classe permet de calculer la d�tection de collision 
///        ainsi que la physique.		   
/// 
/// @author Olivier St-Amour
/// @date 2016-02-22
///////////////////////////////////////////////////////////////////////////
class FormeEnglobanteAbstraite
{
public:
    // Constructeur par d�faut.
    FormeEnglobanteAbstraite();
    // Constructeur par param�tres.
    FormeEnglobanteAbstraite(const glm::dvec3& position);
    // Destructeur.
    virtual ~FormeEnglobanteAbstraite() = 0;

    // Initiliser certains attributs de la forme englobante en fonction d'une boite englobante.
    virtual void initialiser(const utilitaire::BoiteEnglobante& boiteEnglobante) = 0;

    // Acc�s � la position du centre de la forme englobante.
    inline void assignerPositionCentre(const glm::dvec3& positionCentre);
    inline const glm::dvec3& obtenirPositionCentre() const;

    // Acc�s � l'attribut qui indique si la forme est en collision.
    inline void assignerEnCollision(const bool& enCollision); 
    inline bool obtenirEnCollision() const;

    virtual bool calculerEstDansLimites(const double& xMin, const double& xMax,
                                        const double& yMin, const double& yMax) const = 0;

    // Permet de calculer si un point se trouve dans une forme englobante.
    virtual bool calculerEstDansForme(const glm::dvec3& point) const = 0;

    // Permet de calculer si une forme est en intersection avec un cercle.
    virtual bool calculerIntersection(const CercleEnglobant& cercle) const = 0;
    // Permet de calculer si une forme est en intersection avec un rectangle.
    virtual bool calculerIntersection(const RectangleEnglobant& rectangle) const = 0;

    virtual glm::dvec3 calculerNormaleCollision(const RectangleEnglobant& rectangle) const = 0;
    virtual glm::dvec3 calculerNormaleCollision(const CercleEnglobant& cercle) const = 0;
    virtual glm::dvec3 calculerNormaleCollision(const glm::dvec3& point) const = 0;

    // Permt d'afficher la forme englobante.
    virtual void afficher(const glm::dvec3& origine) const = 0;
    virtual void afficher() const = 0;
    
protected:
    glm::dvec3 positionCentre_{ 0.0, 0.0, 0.0 };
    bool enCollision_{ false };
};

////////////////////////////////////////////////////////////////////////
///
/// @fn inline void FormeEnglobanteAbstraite::assignerPositionCentre(const glm::dvec3& positionCentre)
///
/// Cette fonction assigne la position du centre de la forme englobante.
///
/// @param[in] positionCentre : Position du centre de la forme en dvec3.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
inline void FormeEnglobanteAbstraite::assignerPositionCentre(const glm::dvec3& positionCentre)
{
    positionCentre_ = positionCentre;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline const glm::dvec3& FormeEnglobanteAbstraite::obtenirPositionCentre() const
///
/// Cette fonction retourne la position du centre de la forme englobante
///
/// @param[in] Aucun.
///
/// @return positionCentre : Position du centre de la forme en dvec3.
///
////////////////////////////////////////////////////////////////////////
inline const glm::dvec3& FormeEnglobanteAbstraite::obtenirPositionCentre() const
{
    return positionCentre_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline void FormeEnglobanteAbstraite::assignerEnCollision(const bool& enCollision)
///
/// Cette fonction assigne si la forme est en collision ou non.
///
/// @param[in] enCollision : Bool�en qui indique si la forme est en collision.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
inline void FormeEnglobanteAbstraite::assignerEnCollision(const bool& enCollision)
{
    enCollision_ = enCollision;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline bool FormeEnglobanteAbstraite::obtenirEnCollision() const
///
/// Cette fonction retourne si la forme est en collision ou non.
///
/// @param[in] Aucun.
///
/// @returnenCollision : Bool�en qui indique si la forme est en collision.
///
////////////////////////////////////////////////////////////////////////
inline bool FormeEnglobanteAbstraite::obtenirEnCollision() const
{
    return enCollision_;
}

#endif // FORME_ENGLOBANTE_ABSTRAITE_H

///////////////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////////////
