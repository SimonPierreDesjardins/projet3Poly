///////////////////////////////////////////////////////////////////////////
/// @file ModeAbstrait.cpp
/// @author Frédéric Grégoire
/// @date 2016-02-02
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#include "ModeAbstrait.h"
#include <math.h>
#include "Utilitaire.h"
#include <iostream>
#include "FacadeModele.h"
#include "Vue.h"
#include "Projection.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn ModeAbstrait::ModeAbstrait()
///
/// Contructeur (vide) par défaut de ModeAbstrait
///
///
///
////////////////////////////////////////////////////////////////////////
ModeAbstrait::ModeAbstrait()
{
	
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ModeAbstrait::~ModeAbstrait()
///
/// Destructeur (vide) par défaut de la classe ModeAbstrait
///
///
////////////////////////////////////////////////////////////////////////
ModeAbstrait::~ModeAbstrait()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeAbstrait::gererTouchePlus()
///
/// Cette fonction permet de gérer la touche + selon le mode dans lequel nous sommes.
///
/// 
/// Il n'y a pas d'implantantion dans cette classe de base.
///
////////////////////////////////////////////////////////////////////////
void ModeAbstrait::gererTouchePlus()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeAbstrait::gererToucheMoins()
///
/// Cette fonction permet de gérer la touche - selon le mode dans lequel nous sommes.
///
/// 
/// Il n'y a pas d'implantantion dans cette classe de base.
///
////////////////////////////////////////////////////////////////////////
void ModeAbstrait::gererToucheMoins()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeAbstrait::gererToucheEchappe()
///
/// Cette fonction permet de gérer la touche echappe selon le mode dans lequel nous sommes.
///
/// 
/// Il n'y a pas d'implantantion dans cette classe de base.
///
////////////////////////////////////////////////////////////////////////
void ModeAbstrait::gererToucheEchappe()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeAbstrait::gererToucheB()
///
/// Cette fonction permet de gérer la touche B selon le mode dans lequel nous sommes.
///
/// 
/// Il n'y a pas d'implantantion dans cette classe de base.
///
////////////////////////////////////////////////////////////////////////
void ModeAbstrait::gererToucheB()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeAbstrait::gererToucheC()
///
/// Cette fonction permet de gérer la touche C selon le mode dans lequel nous sommes.
///
/// 
/// Il n'y a pas d'implantantion dans cette classe de base.
///
////////////////////////////////////////////////////////////////////////
void ModeAbstrait::gererToucheC()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeAbstrait::gererToucheD()
///
/// Cette fonction permet de gérer la touche D selon le mode dans lequel nous sommes.
///
/// 
/// Il n'y a pas d'implantantion dans cette classe de base.
///
////////////////////////////////////////////////////////////////////////
void ModeAbstrait::gererToucheD()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeAbstrait::gererToucheE()
///
/// Cette fonction permet de gérer la touche E selon le mode dans lequel nous sommes.
///
/// 
/// Il n'y a pas d'implantantion dans cette classe de base.
///
////////////////////////////////////////////////////////////////////////
void ModeAbstrait::gererToucheE()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeAbstrait::gererToucheJ()
///
/// Cette fonction permet de gérer la touche J selon le mode dans lequel nous sommes.
///
/// 
/// Il n'y a pas d'implantantion dans cette classe de base.
///
////////////////////////////////////////////////////////////////////////
void ModeAbstrait::gererToucheJ()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeAbstrait::gererToucheK()
///
/// Cette fonction permet de gérer la touche K selon le mode dans lequel nous sommes.
///
/// 
/// Il n'y a pas d'implantantion dans cette classe de base.
///
////////////////////////////////////////////////////////////////////////
void ModeAbstrait::gererToucheK()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeAbstrait::gererToucheL()
///
/// Cette fonction permet de gérer la touche L selon le mode dans lequel nous sommes.
///
/// 
/// Il n'y a pas d'implantantion dans cette classe de base.
///
////////////////////////////////////////////////////////////////////////
void ModeAbstrait::gererToucheL()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeAbstrait::gererToucheR()
///
/// Cette fonction permet de gérer la touche R selon le mode dans lequel nous sommes.
///
/// 
/// Il n'y a pas d'implantantion dans cette classe de base.
///
////////////////////////////////////////////////////////////////////////

void ModeAbstrait::gererToucheR()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeAbstrait::gererToucheS()
///
/// Cette fonction permet de gérer la touche S selon le mode dans lequel nous sommes.
///
/// 
/// Il n'y a pas d'implantantion dans cette classe de base.
///
////////////////////////////////////////////////////////////////////////

void ModeAbstrait::gererToucheS()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeAbstrait::gererToucheT()
///
/// Cette fonction permet de gérer la touche T selon le mode dans lequel nous sommes.
///
/// 
/// Il n'y a pas d'implantantion dans cette classe de base.
///
////////////////////////////////////////////////////////////////////////

void ModeAbstrait::gererToucheT()
{

}
////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeAbstrait::gererToucheZ()
///
/// Cette fonction permet de gérer la touche Z selon le mode dans lequel nous sommes.
///
/// 
/// Il n'y a pas d'implantantion dans cette classe de base.
///
////////////////////////////////////////////////////////////////////////
void ModeAbstrait::gererToucheZ()
{

}
////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeAbstrait::gererToucheCTRLavecS()
///
/// Cette fonction permet de gérer la touche CTRL avec S selon le mode dans lequel nous sommes.
///
/// 
/// Il n'y a pas d'implantantion dans cette classe de base.
///
////////////////////////////////////////////////////////////////////////
void ModeAbstrait::gererToucheCTRLavecS()
{

}
////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeAbstrait::gererToucheCTRLavecN()
///
/// Cette fonction permet de gérer la touche CTRL avec N selon le mode dans lequel nous sommes.
///
/// 
/// Il n'y a pas d'implantantion dans cette classe de base.
///
////////////////////////////////////////////////////////////////////////
void ModeAbstrait::gererToucheCTRLavecN()
{

}
////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeAbstrait::gererToucheCTRLavecO()
///
/// Cette fonction permet de gérer la touche CTRL avec O selon le mode dans lequel nous sommes.
///
/// 
/// Il n'y a pas d'implantantion dans cette classe de base.
///
////////////////////////////////////////////////////////////////////////
void ModeAbstrait::gererToucheCTRLavecO()
{

}
////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeAbstrait::gererTouche1()
///
/// Cette fonction permet de gérer la touche 1 selon le mode dans lequel nous sommes.
///
/// 
/// Il n'y a pas d'implantantion dans cette classe de base.
///
////////////////////////////////////////////////////////////////////////
void ModeAbstrait::gererTouche1()
{

}
////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeAbstrait::gererTouche2()
///
/// Cette fonction permet de gérer la touche 2 selon le mode dans lequel nous sommes.
///
/// 
/// Il n'y a pas d'implantantion dans cette classe de base.
///
////////////////////////////////////////////////////////////////////////
void ModeAbstrait::gererTouche2()
{

}
////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeAbstrait::gererTouche3()
///
/// Cette fonction permet de gérer la touche 3 selon le mode dans lequel nous sommes.
///
/// 
/// Il n'y a pas d'implantantion dans cette classe de base.
///
////////////////////////////////////////////////////////////////////////
void ModeAbstrait::gererTouche3()
{

}
////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeAbstrait::gererFlecheGauche()
///
/// Cette fonction permet de gérer la touche flèche gauche selon le mode dans lequel nous sommes.
///
/// 
/// Il n'y a pas d'implantantion dans cette classe de base.
///
////////////////////////////////////////////////////////////////////////
void ModeAbstrait::gererFlecheGauche()
{

}
////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeAbstrait::gererFlecheBas()
///
/// Cette fonction permet de gérer la touche flèche bas selon le mode dans lequel nous sommes.
///
/// 
/// Il n'y a pas d'implantantion dans cette classe de base.
///
////////////////////////////////////////////////////////////////////////
void ModeAbstrait::gererFlecheBas()
{

}
////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeAbstrait::gererFlecheHaut()
///
/// Cette fonction permet de gérer la touche flèche haut selon le mode dans lequel nous sommes.
///
/// 
/// Il n'y a pas d'implantantion dans cette classe de base.
///
////////////////////////////////////////////////////////////////////////
void ModeAbstrait::gererFlecheHaut()
{
	
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeAbstrait::gererFlecheDroit()
///
/// Cette fonction permet de gérer la touche flèche droit selon le mode dans lequel nous sommes.
///
/// 
/// Il n'y a pas d'implantantion dans cette classe de base.
///
////////////////////////////////////////////////////////////////////////
void ModeAbstrait::gererFlecheDroit()
{

}
////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeAbstrait::gererBarreDespacement()
///
/// Cette fonction permet de gérer la barre d'espacement selon le mode dans lequel nous sommes.
///
/// 
/// Il n'y a pas d'implantantion dans cette classe de base.
///
////////////////////////////////////////////////////////////////////////

void ModeAbstrait::gererBarreDespacement()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeAbstrait::gererToucheArriere()
///
/// Cette fonction permet de gérer la touche arrière selon le mode dans lequel nous sommes.
///
/// 
/// Il n'y a pas d'implantantion dans cette classe de base.
///
////////////////////////////////////////////////////////////////////////

void ModeAbstrait::gererToucheArriere()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeAbstrait::gererToucheControlEnfoncee()
///
/// Cette fonction permet de gérer la touche CTRL enfoncée selon le mode dans lequel nous sommes.
///
/// 
/// Il n'y a pas d'implantantion dans cette classe de base.
///
////////////////////////////////////////////////////////////////////////

void ModeAbstrait::gererToucheControlEnfoncee()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeAbstrait::gererToucheControlRelachee()
///
/// Cette fonction permet de gérer la touche CTRL relachée selon le mode dans lequel nous sommes.
///
/// 
/// Il n'y a pas d'implantantion dans cette classe de base.
///
////////////////////////////////////////////////////////////////////////

void ModeAbstrait::gererToucheControlRelachee()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeAbstrait::sauvegarder()
///
/// Cette fonction permet de gérer la sauvegarde selon le mode dans lequel nous sommes.
///
/// 
/// Il n'y a pas d'implantantion dans cette classe de base.
///
////////////////////////////////////////////////////////////////////////

void ModeAbstrait::sauvegarder(){

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeAbstrait::charger()
///
/// Cette fonction permet de gérer le chargement selon le mode dans lequel nous sommes.
///
/// 
/// Il n'y a pas d'implantantion dans cette classe de base.
///
////////////////////////////////////////////////////////////////////////

void ModeAbstrait::charger(){

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeAbstrait::gererToucheSupprimer()
///
/// Cette fonction permet de gérer la touche supprimer selon le mode dans lequel nous sommes.
///
/// 
/// Il n'y a pas d'implantantion dans cette classe de base.
///
////////////////////////////////////////////////////////////////////////

void ModeAbstrait::gererToucheSupprimer()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeAbstrait::gererClicDroitEnfonce(const int& x, const int& y)
///
/// Cette fonction permet de gérer le clic droit enfonce selon le mode dans lequel nous sommes.
///
/// 
/// Il n'y a pas d'implantantion dans cette classe de base.
///
///@param[in] x : La position en x du curseur de la souris lors d'un clic droit.
///@param[in] y : La position en y du curseur de la souris lors d'un clic droit.
///
////////////////////////////////////////////////////////////////////////


void ModeAbstrait::gererClicDroitEnfonce(const int& x, const int& y){
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeAbstrait::gererClicDroitRelache(const int& x, const int& y)
///
/// Cette fonction permet de gérer le clic droit relache selon le mode dans lequel nous sommes.
///
/// 
/// Il n'y a pas d'implantantion dans cette classe de base.
///
///@param[in] x : La position en x du curseur de la souris lors d'un clic droit.
///@param[in] y : La position en y du curseur de la souris lors d'un clic droit.
///
////////////////////////////////////////////////////////////////////////

void ModeAbstrait::gererClicDroitRelache(const int& x, const int& y){
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeAbstrait::gererClicGaucheEnfonce(const int& x, const int& y)
///
/// Cette fonction permet de gérer le clic gauche enfonce selon le mode dans lequel nous sommes.
///
/// 
/// Il n'y a pas d'implantantion dans cette classe de base.
///
///@param[in] x : La position en x du curseur de la souris lors d'un clic gauche.
///@param[in] y : La position en y du curseur de la souris lors d'un clic gauche.
///
////////////////////////////////////////////////////////////////////////

void ModeAbstrait::gererClicGaucheEnfonce(const int& x, const int& y){
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeAbstrait::gererClicGaucheRelache(const int& x, const int& y)
///
/// Cette fonction permet de gérer le clic gauche relache selon le mode dans lequel nous sommes.
///
/// 
/// Il n'y a pas d'implantantion dans cette classe de base.
///
///@param[in] x : La position en x du curseur de la souris lors d'un clic gauche.
///@param[in] y : La position en y du curseur de la souris lors d'un clic gauche.
///
////////////////////////////////////////////////////////////////////////

void ModeAbstrait::gererClicGaucheRelache(const int& x, const int& y){
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeAbstrait::gererMouvementSouris(const int & x, const int& y)
///
/// Cette fonction permet de gérer le mouvement de la souris selon le mode dans lequel nous sommes.
///
/// 
/// Il n'y a pas d'implantantion dans cette classe de base.
///
///@param[in] x : La position en x du curseur de la souris lors d'un mouvement de souris.
///@param[in] y : La position en y du curseur de la souris lors d'un mouvement de souris.
///
////////////////////////////////////////////////////////////////////////

void ModeAbstrait::gererMouvementSouris(const int & x, const int& y){
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeAbstrait::gererMoletteSouris(const int & delta)
///
/// Cette fonction permet de gérer la molette de le souris selon le mode dans lequel nous sommes.
///
/// 
/// Il n'y a pas d'implantantion dans cette classe de base.
///
///@param[in] delta : La différence entre du mouvement de molette de la souris.
///
////////////////////////////////////////////////////////////////////////
void ModeAbstrait::gererMoletteSouris(const int & delta){
}
