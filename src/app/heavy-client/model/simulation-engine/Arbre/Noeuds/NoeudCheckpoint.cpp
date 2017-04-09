///////////////////////////////////////////////////////////////////////////////
/// @file NoeudCheckpoint.cpp
/// @author Simon-Pierre Desjardins
/// @date 2017-03-08
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudCheckpoint.h"
#include "Utilitaire.h"

#include "GL/glew.h"
#include <cmath>
#include <iostream>

#include "Modele3D.h"
#include "OpenGL_VBO.h"

#include "VisiteurAbstrait.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudCheckpoint::NoeudCheckpoint(uint32_t id, const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud et le id du noeud
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudCheckpoint::NoeudCheckpoint(uint32_t id, const std::string& typeNoeud)
	: NoeudLigneCourseAbstrait{ id, typeNoeud }
{
	type_ = CHECKPOINT_ENTITY;
}



////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudCheckpoint::~NoeudCheckpoint()
///
/// Ce destructeur désallouee la liste d'affichage du checkpoint.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudCheckpoint::~NoeudCheckpoint()
{

}



///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////