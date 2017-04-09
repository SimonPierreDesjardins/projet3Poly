///////////////////////////////////////////////////////////////////////////////
/// @file NoeudLigneArrivee.cpp
/// @author Simon-Pierre Desjardins
/// @date 2017-03-08
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudLigneArrivee.h"
#include "Utilitaire.h"

#include "GL/glew.h"
#include <cmath>
#include <iostream>

#include "Modele3D.h"
#include "OpenGL_VBO.h"

#include "VisiteurAbstrait.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudLigneArrivee::NoeudLigneArrivee(uint32_t id, const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud et le id du noeud
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudLigneArrivee::NoeudLigneArrivee(uint32_t id, const std::string& typeNoeud)
	: NoeudLigneCourseAbstrait{ id, typeNoeud }
{
	type_ = FINISHLINE_ENTITY;
}




////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudLigneArrivee::~NoeudLigneArrivee()
///
/// Ce destructeur désallouee la liste d'affichage de la ligne darrivee.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudLigneArrivee::~NoeudLigneArrivee()
{

}



///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////