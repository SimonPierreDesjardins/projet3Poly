///////////////////////////////////////////////////////////////////////////
/// @file NoeudCheckpoint.h
/// @author Simon-Pierre Desjardins
/// @date 2017-03-08
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef __ARBRE_NOEUDS_NOEUDCHECKPOINT_H__
#define __ARBRE_NOEUDS_NOEUDCHECKPOINT_H__

#include "NoeudLigneCourseAbstrait.h"
#include "CercleEnglobant.h"
#include "RectangleEnglobant.h"
#include "GL/glew.h"
#include "VisiteurAbstrait.h"

///////////////////////////////////////////////////////////////////////////
/// @class NoeudCheckpoint
/// @brief Noeud des checkpoints
///
/// @author Simon-Pierre Desjardins
/// @date 2017-03-08
///////////////////////////////////////////////////////////////////////////
class NoeudCheckpoint : public NoeudLigneCourseAbstrait
{

public:
	/// Constructeur
	NoeudCheckpoint(uint32_t id, const std::string& typeNoeud);
	/// Destructeur.
	~NoeudCheckpoint();




private:

};
 

#endif

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////