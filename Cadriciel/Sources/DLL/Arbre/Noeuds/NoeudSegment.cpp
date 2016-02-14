#include "NoeudSegment.h"
#include "Utilitaire.h"
#include "VisiteurAbstrait.h"
#include "GL/glew.h"
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_VBO.h"
#include <iostream>


NoeudSegment::NoeudSegment(const std::string& typeNoeud)
	: NoeudAbstrait(typeNoeud)
{
}


NoeudSegment::~NoeudSegment()
{
}

void NoeudSegment::accepterVisiteur(VisiteurAbstrait* visiteur){
	visiteur->visiter(this);
}

void NoeudSegment::afficherConcret() const
{
	// Sauvegarde de la matrice.
	glPushMatrix();

	//Ajustement du mur avant la création
	glRotated(angleRotation_, 0, 0, 1);
	glScaled(facteurMiseAEchelle_, 1, 1);

	// Affichage du modèle.
	vbo_->dessiner();
	// Restauration de la matrice.
	glPopMatrix();
}

/*
void NoeudSegment::mettreAJourQuadEnglobantConcret(const glm::dvec3& positionRelative)
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
*/