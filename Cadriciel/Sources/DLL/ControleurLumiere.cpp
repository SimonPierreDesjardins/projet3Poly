///////////////////////////////////////////////////////////////////////////
/// @file ControleurLumiere.cpp
/// @author Simon-Pierre Desjardins
/// @date 2016-04-1
/// @version 3.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////


#include "ControleurLumiere.h"
#include "FacadeModele.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

////////////////////////////////////////////////////////////////////////
///
/// @fn void AffichageTexte::reinitialiserChrono()
///
/// Fonction qui permet de réinitialiser (0) le chronomètre de l'affichage.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
ControleurLumiere::ControleurLumiere()
{
	
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void AffichageTexte::reinitialiserChrono()
///
/// Fonction qui permet de réinitialiser (0) le chronomètre de l'affichage.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
ControleurLumiere::~ControleurLumiere()
{

}

void ControleurLumiere::afficherLumiereAmbianteGlobale()
{
	if (lumiereAmbiante)
	{
		glm::vec4 ambiant{ 0.2f, 0.2f, 0.2f, 1.0f };
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, glm::value_ptr(ambiant));
	}
	else
	{
		glm::vec4 ambiant{ 0.0f, 0.0f, 0.0f, 1.0f };
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, glm::value_ptr(ambiant));
	}

}