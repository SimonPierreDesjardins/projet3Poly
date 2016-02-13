///////////////////////////////////////////////////////////////////////////////
/// @file NoeudMur.cpp
/// @author Philippe Marcotte et Camille Gendreau
/// @date 2011-05-19
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudMur.h"
#include "Utilitaire.h"

#include "GL/glew.h"
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_VBO.h"

#include "VisiteurAbstrait.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudMur::NoeudMur(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par défaut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudMur::NoeudMur(const std::string& typeNoeud)
	: NoeudAbstrait{ typeNoeud }
{
	angleRotation_ = 0;
	facteurMiseAEchelle_ = 1;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudMur::~NoeudMur()
///
/// Ce destructeur désallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudMur::~NoeudMur()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudMur::afficherConcret() const
///
/// Cette fonction effectue le véritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudMur::afficherConcret() const
{
	// Sauvegarde de la matrice.
	glPushMatrix();

	if (estSelectionne())
	{
		glColor4f(1.0, 0.2, 0.0, 1.0);
	}
	else
	{
		glColor4f(0.0, 0.0, 0.0, 1.0);
	}


	//Ajustement du mur avant la création
	glRotated(angleRotation_, 0, 0, 1);
	
	glScaled(facteurMiseAEchelle_, 1.0, 1.0);

	// Affichage du modèle.
	vbo_->dessiner();


	// Restauration de la matrice.
	glPopMatrix();
}


void NoeudMur::mettreAJourQuadEnglobantConcret(const glm::dvec3& positionRelative)
{
	// Mettre à jour la position en x des coins avec le facteur de mise à échelle.
	glm::dvec3 tmp;
	for (int i = 0; i < 4; i++)
	{
		quadEnglobant_.coins[i].x *= facteurMiseAEchelle_;
		tmp = quadEnglobant_.coins[i];
		utilitaire::calculerPositionApresRotation(tmp, quadEnglobant_.coins[i], angleRotation_);
		quadEnglobant_.coins[i] += positionRelative_ + positionRelative;
	}
}

void NoeudMur::accepterVisiteur(VisiteurAbstrait* visiteur)
{
	visiteur->visiter(this);
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////

