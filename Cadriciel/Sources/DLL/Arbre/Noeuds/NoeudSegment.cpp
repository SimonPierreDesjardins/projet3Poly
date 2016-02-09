#include "NoeudSegment.h"
#include "Utilitaire.h"

#include "GL/glew.h"
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_VBO.h"


NoeudSegment::NoeudSegment(const std::string& typeNoeud)
	: NoeudAbstrait(typeNoeud)
{
}


NoeudSegment::~NoeudSegment()
{
}

void NoeudSegment::afficherConcret() const
{
	// Sauvegarde de la matrice.
	glPushMatrix();
	if (estSelectionne())
	{
		glColor4f(1.0, 0.0, 0.0, 1.0);
	}
	else
		glColor4f(0.0, 0.0, 0.0, 1.0);

	//Ajustement du mur avant la création
	glRotated(angleRotation_, 0, 0, 1);

	if (estSelectionne())
	{
		glColor4f(1.0, 0.0, 0.0, 1.0);
	}
	else
	{
		glColor4f(0.0, 0.0, 0.0, 1.0);
	}
	glScaled(facteurMiseAEchelle_, 1, 1);

	// Affichage du modèle.
	vbo_->dessiner();
	// Restauration de la matrice.
	glPopMatrix();
}