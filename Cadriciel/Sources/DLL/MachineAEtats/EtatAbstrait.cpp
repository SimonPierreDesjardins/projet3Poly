///////////////////////////////////////////////////////////////////////////
/// @file EtatAbstrait.cpp
/// @author 
/// @date 2016-01-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#include "EtatAbstrait.h"
#include <math.h>
#include "Utilitaire.h"
#include <iostream>
#include "FacadeModele.h"
#include "Vue.h"
#include "Projection.h"

EtatAbstrait::EtatAbstrait()
{

}

EtatAbstrait::~EtatAbstrait()
{

}

void EtatAbstrait::gererClicDroitEnfonce(const int& x, const int& y)
{
	clicDroitEnfonce_ = true;
	ancienX_ = x;
	ancienY_ = y;
}

void EtatAbstrait::gererClicDroitRelache(const int& x, const int& y)
{
	clicDroitEnfonce_ = false;
}

void EtatAbstrait::gererClicGaucheEnfonce(const int& x, const int& y)
{
	clicGaucheEnfonce_ = true;
}

void EtatAbstrait::gererClicGaucheRelache(const int& x, const int& y)
{
	clicGaucheEnfonce_ = false;
}

void EtatAbstrait::gererMouvementSouris(const int & x, const int& y)
{
	if (clicDroitEnfonce_){
		if (FacadeModele::obtenirInstance()->obtenirVue()->obtenirProjection().estPerspective())
			//TODO
			FacadeModele::obtenirInstance()->obtenirVue()->rotaterXY(NULL, NULL);
		else
			FacadeModele::obtenirInstance()->obtenirVue()->deplacerXY(glm::ivec2(-(x - ancienX_), y - ancienY_));
		ancienX_ = x;
		ancienY_ = y;
	}

}

void EtatAbstrait::gererToucheEchappe()
{

}

void EtatAbstrait::gererToucheControlEnfoncee()
{

}

void EtatAbstrait::gererToucheControlRelachee()
{

}

void EtatAbstrait::gererTouchePlus(){
	if (FacadeModele::obtenirInstance()->obtenirVue()->obtenirProjection().estPerspective())
		//TODO Gérer le zoom plus pour une camera
		;
	else
		FacadeModele::obtenirInstance()->obtenirVue()->zoomerIn();

}

void EtatAbstrait::gererToucheMoins(){
	if (FacadeModele::obtenirInstance()->obtenirVue()->obtenirProjection().estPerspective())
		//TODO Gérer le zoom moins pour une camera
		;
	else
		FacadeModele::obtenirInstance()->obtenirVue()->zoomerOut();
}

void EtatAbstrait::gererMoletteSouris(const int & delta){
	if (FacadeModele::obtenirInstance()->obtenirVue()->obtenirProjection().estPerspective())
		//TODO Gérer le zoom moins pour une camera
		;
	else{
		if (delta>0)
			FacadeModele::obtenirInstance()->obtenirVue()->zoomerIn();
		else
			FacadeModele::obtenirInstance()->obtenirVue()->zoomerOut();
	}
		
}

void EtatAbstrait::gererEstSurTable(const glm::dvec3& position)
{
	// TODO: Changer les constantes pour les dimensions dynamiques de la table.
	const int MIN_X = -48;
	const int MAX_X =  48;
	const int MIN_Y = -24;
	const int MAX_Y =  24;
	bool positionEstSurTable = (MIN_X <= position[0] && position[0] <= MAX_X && MIN_Y <= position[1] && position[1] <= MAX_Y);
	gererEstSurTableConcret(positionEstSurTable);
}

void EtatAbstrait::gererEstSurTableConcret(bool positionEstSurTable)
{

}

void EtatAbstrait::assignerSymbolePointeur(bool estSymboleStandard)
{
	if (estSymboleStandard) 
	{
		// TODO: Ajouter changement de curseur ici.
		//HCURSOR handle = GetCursor();
		//SetSystemCursor(handle, 32650);
		std::cout << "in" << std::endl;
	} 
	else
	{
		//TODO: Ajouter changement de curseur ici.
		//HCURSOR handle = GetCursor();
		//SetSystemCursor(handle, 32648);
		std::cout << "out" << std::endl;
	}
}
