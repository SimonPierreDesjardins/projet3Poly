#include "NoeudSegment.h"
#include "Utilitaire.h"
#include "VisiteurAbstrait.h"

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

void NoeudSegment::accepterVisiteur(VisiteurAbstrait* visiteur){
	visiteur->visiter(this);
}

void NoeudSegment::afficherConcret() const
{
	// Sauvegarde de la matrice.
	glPushMatrix();

	//Ajustement du mur avant la cr�ation
	glRotated(angleRotation_, 0, 0, 1);
	glScaled(facteurMiseAEchelle_, 1, 1);

	// Affichage du mod�le.
	vbo_->dessiner();
	// Restauration de la matrice.
	glPopMatrix();
}