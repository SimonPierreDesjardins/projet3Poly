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

glm::ivec2 EtatAbstrait::currentPosition_ = { 0.0, 0.0 };


////////////////////////////////////////////////////////////////////////
///
/// @fn EtatAbstrait::EtatAbstrait()
///
/// Constructeur par d�fault. Assigne arbre_ � arbre courant
///
////////////////////////////////////////////////////////////////////////
EtatAbstrait::EtatAbstrait()
{
	arbre_ = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
	vue_ = FacadeModele::obtenirInstance()->obtenirVue();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn EtatAbstrait::~EtatAbstrait()
///
/// Destructeur par d�fault
///
////////////////////////////////////////////////////////////////////////
EtatAbstrait::~EtatAbstrait()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatAbstrait::gererClicDroitEnfonce(const int& x, const int& y)
///
/// Cette fonction assigne un bool�an � true si le bouton droit de la souris est
/// appuy�.
///
/// @param const int& x: position en x du cursor
/// @param const int& y: position en y du cursor
///
////////////////////////////////////////////////////////////////////////
void EtatAbstrait::gererClicDroitEnfonce(const int& x, const int& y)
{
	clicDroitEnfonce_ = true;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatAbstrait::gererClicDroitRelache(const int& x, const int& y)
///
/// Cette fonction assigne un bool�an � false si le bouton droit de la souris est
/// rel�ch�.
///
/// @param const int& x: position en x du cursor
/// @param const int& y: position en y du cursor
///
////////////////////////////////////////////////////////////////////////
void EtatAbstrait::gererClicDroitRelache(const int& x, const int& y)
{
	clicDroitEnfonce_ = false;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatAbstrait::gererClicGaucheEnfonce(const int& x, const int& y)
///
/// Cette fonction assigne un bool�an � true si le bouton gauche de la souris est
/// appuy� et sauvegarde la position courante.
///
/// @param const int& x: position en x du cursor
/// @param const int& y: position en y du cursor
///
////////////////////////////////////////////////////////////////////////
void EtatAbstrait::gererClicGaucheEnfonce(const int& x, const int& y)
{
	clicGaucheEnfonce_ = true;
	anchor = glm::ivec2(x, y);
	currentPosition_ = anchor;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatAbstrait::gererClicGaucheRelache(const int& x, const int& y)
///
/// Cette fonction assigne un bool�an � false si le bouton gauche de la souris est
/// rel�ch�.
///
/// @param const int& x: position en x du cursor
/// @param const int& y: position en y du cursor
///
////////////////////////////////////////////////////////////////////////
void EtatAbstrait::gererClicGaucheRelache(const int& x, const int& y)
{
	clicGaucheEnfonce_ = false;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatAbstrait::gererMouvementSouris(const int & x, const int& y)
///
/// Cette fonction g�re les mouvements de la souris. Si le clique droit est enfonc�
/// on peux d�placer la cam�ra, sinon rien
///
/// @param const int& x: position en x du cursor
/// @param const int& y: position en y du cursor
///
////////////////////////////////////////////////////////////////////////
void EtatAbstrait::gererMouvementSouris(const int & x, const int& y)
{
	if (clicDroitEnfonce_){
		if (FacadeModele::obtenirInstance()->obtenirVue()->obtenirProjection().estPerspective())
			//TODO
			FacadeModele::obtenirInstance()->obtenirVue()->rotaterXY(NULL, NULL);
		else
			FacadeModele::obtenirInstance()->obtenirVue()->deplacerXY(glm::ivec2(-(x - currentPosition_.x), y - currentPosition_.y));

	}
	currentPosition_ = glm::ivec2(x, y);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool EtatAbstrait::estClickDrag()
///
/// Cette fonction v�rifie si le point d'origine et le point final d'un clique
/// est � plus de trois pixels
///
////////////////////////////////////////////////////////////////////////
bool EtatAbstrait::estClickDrag(){
	return (std::abs(currentPosition_.x - anchor.x) > 3 || std::abs(currentPosition_.y - anchor.y) > 3);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatAbstrait::gererToucheEchappe()
///
/// Cette fonction g�re la touche Escape
///
////////////////////////////////////////////////////////////////////////
void EtatAbstrait::gererToucheEchappe()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatAbstrait::gererToucheControlEnfoncee()
///
/// Cette fonction g�re la touche Control enfoncee
///
////////////////////////////////////////////////////////////////////////
void EtatAbstrait::gererToucheControlEnfoncee()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatAbstrait::gererToucheControlRelachee()
///
/// Cette fonction g�re la touche Control rel�ch�e
///
////////////////////////////////////////////////////////////////////////
void EtatAbstrait::gererToucheControlRelachee()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatAbstrait::gererToucheAltEnfoncee()
///
/// Cette fonction g�re la touche Alt enfoncee
///
////////////////////////////////////////////////////////////////////////
void EtatAbstrait::gererToucheAltEnfoncee()
{
	toucheAltEnfonce_ = true;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatAbstrait::gererToucheAltRelachee()
///
/// Cette fonction g�re la touche Alt rel�ch�e
///
////////////////////////////////////////////////////////////////////////
void EtatAbstrait::gererToucheAltRelachee()
{
	toucheAltEnfonce_ = false;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatAbstrait::gererTouchePlus()
///
/// Cette fonction g�re la touche +=, permet de faire un zoom avec la cam�ra
///
////////////////////////////////////////////////////////////////////////
void EtatAbstrait::gererTouchePlus(){
	if (FacadeModele::obtenirInstance()->obtenirVue()->obtenirProjection().estPerspective())
		//TODO G�rer le zoom plus pour une camera
		;
	else
		FacadeModele::obtenirInstance()->obtenirVue()->zoomerIn();

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatAbstrait::gererTouchePlus()
///
/// Cette fonction g�re la touche +=, permet de faire un zoom avec la cam�ra
///
////////////////////////////////////////////////////////////////////////
void EtatAbstrait::gererToucheMoins(){
	if (FacadeModele::obtenirInstance()->obtenirVue()->obtenirProjection().estPerspective())
		//TODO G�rer le zoom moins pour une camera
		;
	else
		FacadeModele::obtenirInstance()->obtenirVue()->zoomerOut();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatAbstrait::gererMoletteSouris(const int & delta)
///
/// Cette fonction g�re la molette de la souris. Permet d'effecter un zoom
/// avec la cam�ra
///
/// @param const int & delta: la valeur de la molette de la souris
///
////////////////////////////////////////////////////////////////////////
void EtatAbstrait::gererMoletteSouris(const int & delta){
	if (FacadeModele::obtenirInstance()->obtenirVue()->obtenirProjection().estPerspective())
		;
	else{
		if (delta>0)
			FacadeModele::obtenirInstance()->obtenirVue()->zoomerIn();
		else
			FacadeModele::obtenirInstance()->obtenirVue()->zoomerOut();
	}
		
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatAbstrait::gererEstSurTable(const glm::dvec3& position)
///
/// Cette fonction v�rifie que le curseur est sur la table
///
/// @param const glm::dvec3& position: position de la souris
///
////////////////////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatAbstrait::gererEstSurTableConcret(bool positionEstSurTable)
///
/// Cette fonction change l'image du curseur s'il n'est pas sur la table
///
/// @param bool positionEstSurTable: True si la souris est sur la table sinon false
///
////////////////////////////////////////////////////////////////////////
void EtatAbstrait::gererEstSurTableConcret(bool positionEstSurTable)
{
	if (!positionEstSurTable)
	{
		HCURSOR Cursor = LoadCursor(NULL, IDC_NO);
		SetCursor(Cursor);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatAbstrait::assignerSymbolePointeur(bool estSymboleStandard)
///
/// Cette fonction assigne l'image du cursor lorsque ce n'est pas son symbole standard
/// qui est affich�
///
/// @param bool estSymboleStandard: True si la souris est sur la table sinon false
///
////////////////////////////////////////////////////////////////////////
void EtatAbstrait::assignerSymbolePointeur(bool estSymboleStandard)
{
	//Pour forme de cursor voir http://msdn.microsoft.com/en-us/library/ms648391%28v=vs.85%29.aspx
	if (!estSymboleStandard) 
	{
		HCURSOR Cursor = LoadCursor(NULL, IDC_NO);
		SetCursor(Cursor);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatAbstrait::reinitialiser()
///
////////////////////////////////////////////////////////////////////////
void EtatAbstrait::reinitialiser()
{

}
