///////////////////////////////////////////////////////////////////////////
/// @file ModeEdition.cpp
/// @author Frédéric Grégoire
/// @date 2016-02-02
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#include "ModeEdition.h"
#include <math.h>
#include "Utilitaire.h"
#include <iostream>
#include "FacadeModele.h"
#include "Vue.h"
#include "Projection.h"
#include "VisiteurSauvegarde.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn ModeEdition::ModeEdition()
///
/// Ne fait qu'initialiser les variables membres de la classe.
///
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
ModeEdition::ModeEdition()
{
	FacadeModele::obtenirInstance()->assignerEtat(SELECTION);
	typeMode_ = EDITION;
	visiteurSuppression_ = std::make_unique<VisiteurSuppression>();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ModeEdition::~ModeEdition()
///
/// Destructeur par défaut de la classe ModeEdition
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
ModeEdition::~ModeEdition()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeEdition::gererTouchePlus()
///
/// Cette fonction permet de gérer la touche + dans le modeEdition.
///
/// Si nous ne sommes pas en perspective, la touche plus effectue un zoom in.
///
////////////////////////////////////////////////////////////////////////
void ModeEdition::gererTouchePlus()
{
	if (FacadeModele::obtenirInstance()->obtenirVue()->obtenirProjection().estPerspective()) {

	} 
	else {
		FacadeModele::obtenirInstance()->obtenirVue()->zoomerIn();
	}

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeEdition::gererToucheMoins()
///
/// Cette fonction permet de gérer la touche - dans le modeEdition.
///
/// Si nous ne sommes pas en perspective, la touche plus effectue un zoom out.
///
////////////////////////////////////////////////////////////////////////
void ModeEdition::gererToucheMoins()
{
	if (FacadeModele::obtenirInstance()->obtenirVue()->obtenirProjection().estPerspective()) {

	}
	else {
		FacadeModele::obtenirInstance()->obtenirVue()->zoomerOut();
	}

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeEdition::gererToucheMoins()
///
/// Cette fonction permet de gérer la touche echappe dans le modeEdition.
///
/// Elle appelle la fonction gereToucheEchappe selon l'état obtenu.
///
////////////////////////////////////////////////////////////////////////

void ModeEdition::gererToucheEchappe()
{
	FacadeModele::obtenirInstance()->obtenirEtat()->gererToucheEchappe();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeEdition::gererToucheC()
///
/// Cette fonction permet de gérer la touche C dans le modeEdition.
///
/// Elle assigne l'état DUPLICATION à l'instance obtenue.
///
////////////////////////////////////////////////////////////////////////
void ModeEdition::gererToucheC()
{
	FacadeModele::obtenirInstance()->assignerEtat(DUPLICATION);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeEdition::gererToucheD()
///
/// Cette fonction permet de gérer la touche D dans le modeEdition.
///
/// Elle assigne l'état DEPLACEMENT à l'instance obtenue.
///
////////////////////////////////////////////////////////////////////////
void ModeEdition::gererToucheD()
{
	FacadeModele::obtenirInstance()->assignerEtat(DEPLACEMENT);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeEdition::gererToucheE()
///
/// Cette fonction permet de gérer la touche E dans le modeEdition.
///
/// Elle assigne l'état MISE_A_ECHELLE à l'instance obtenue.
///
////////////////////////////////////////////////////////////////////////
void ModeEdition::gererToucheE()
{
	FacadeModele::obtenirInstance()->assignerEtat(MISE_A_ECHELLE);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeEdition::gererToucheR()
///
/// Cette fonction permet de gérer la touche R dans le modeEdition.
///
/// Elle assigne l'état ROTATION à l'instance obtenue.
///
////////////////////////////////////////////////////////////////////////
void ModeEdition::gererToucheR()
{
	FacadeModele::obtenirInstance()->assignerEtat(ROTATION);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeEdition::gererToucheS()
///
/// Cette fonction permet de gérer la touche S dans le modeEdition.
///
/// Elle assigne l'état SELECTION à l'instance obtenue.
///
////////////////////////////////////////////////////////////////////////
void ModeEdition::gererToucheS()
{
	FacadeModele::obtenirInstance()->assignerEtat(SELECTION);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeEdition::gererToucheT()
///
/// Cette fonction permet de gérer la touche T dans le modeEdition.
///
/// Elle assigne le mode TEST à l'instance obtenue.
///
////////////////////////////////////////////////////////////////////////
void ModeEdition::gererToucheT()
{
	//FacadeModele::obtenirInstance()->assignerMode(TEST);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeEdition::gererToucheZ()
///
/// Cette fonction permet de gérer la touche Z dans le modeEdition.
///
/// Elle assigne l'état ZOOM à l'instance obtenue.
///
////////////////////////////////////////////////////////////////////////
void ModeEdition::gererToucheZ()
{
	FacadeModele::obtenirInstance()->assignerEtat(ZOOM);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeEdition::gererToucheCTRLavecS()
///
/// Cette fonction permet de gérer la touche CTRL avec S dans le modeEdition.
///
/// Ne fait rien dans ce mode.
///
////////////////////////////////////////////////////////////////////////
void ModeEdition::gererToucheCTRLavecS()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeEdition::gererToucheCTRLavecN()
///
/// Cette fonction permet de gérer la touche CTRL avec N dans le modeEdition.
///
/// Ne fait rien dans ce mode.
///
////////////////////////////////////////////////////////////////////////
void ModeEdition::gererToucheCTRLavecN()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeEdition::gererToucheCTRLavecO()
///
/// Cette fonction permet de gérer la touche O dans le modeEdition.
///
/// Ne fait rien dans ce mode.
///
////////////////////////////////////////////////////////////////////////
void ModeEdition::gererToucheCTRLavecO()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeEdition::gererTouche1()
///
/// Cette fonction permet de gérer la touche 1 dans le modeEdition.
///
/// Ne fait rien dans ce mode.
///
////////////////////////////////////////////////////////////////////////
void ModeEdition::gererTouche1()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeEdition::gererTouche2()
///
/// Cette fonction permet de gérer la touche 2 dans le modeEdition.
///
/// Ne fait rien dans ce mode.
///
////////////////////////////////////////////////////////////////////////
void ModeEdition::gererTouche2()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeEdition::gererFlecheGauche()
///
/// Cette fonction permet de gérer la touche flèche gauche dans le modeEdition.
///
/// Fait un déplacement de 10 pixels selon l'axe des x.
///
////////////////////////////////////////////////////////////////////////

void ModeEdition::gererFlecheGauche()
{
	std::cout << "La fleche de gauche est appuyee" << std::endl;
	FacadeModele::obtenirInstance()->obtenirVue()->deplacerXY(10, 0);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeEdition::gererFlecheBas()
///
/// Cette fonction permet de gérer la touche flèche bas dans le modeEdition.
///
/// Fait un déplacement de 10 pixels selon l'axe des y.
///
////////////////////////////////////////////////////////////////////////
void ModeEdition::gererFlecheBas()
{
	std::cout << "La fleche du bas est appuyee" << std::endl;
	FacadeModele::obtenirInstance()->obtenirVue()->deplacerXY(0, 10);
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeEdition::gererFlecheHaut()
///
/// Cette fonction permet de gérer la touche flèche haut dans le modeEdition.
///
/// Fait un déplacement de -10 pixels selon l'axe des y.
///
////////////////////////////////////////////////////////////////////////
void ModeEdition::gererFlecheHaut()
{
	std::cout << "La fleche du haut est appuyee" << std::endl;
	FacadeModele::obtenirInstance()->obtenirVue()->deplacerXY(0, -10);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeEdition::gererFlecheDroit()
///
/// Cette fonction permet de gérer la touche flèche droit dans le modeEdition.
///
/// Fait un déplacement de -10 pixels selon l'axe des x.
///
////////////////////////////////////////////////////////////////////////
void ModeEdition::gererFlecheDroit()
{
	std::cout << "La fleche de droite est appuyee" << std::endl;
	FacadeModele::obtenirInstance()->obtenirVue()->deplacerXY(-10, 0);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeEdition::gererToucheControlEnfoncee()
///
/// Cette fonction permet de gérer la touche CTRL enfoncee dans le modeEdition.
///
/// Elle appelle la fonction gererToucheControlEnfoncee selon l'état obtenu.
///
////////////////////////////////////////////////////////////////////////
void ModeEdition::gererToucheControlEnfoncee()
{
	FacadeModele::obtenirInstance()->obtenirEtat()->gererToucheControlEnfoncee();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeEdition::gererToucheControlRelachee()
///
/// Cette fonction permet de gérer la touche CTRL relachee dans le modeEdition.
///
/// Elle appelle la fonction gererToucheControlRelachee selon l'état obtenu.
///
////////////////////////////////////////////////////////////////////////
void ModeEdition::gererToucheControlRelachee()
{
	FacadeModele::obtenirInstance()->obtenirEtat()->gererToucheControlRelachee();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeEdition::sauvegarder()
///
/// Cette fonction permet de gérer la sauvegarde dans le modeEdition.
///
////////////////////////////////////////////////////////////////////////
void ModeEdition::sauvegarder()
{
	unique_ptr<VisiteurSauvegarde> visiteur = make_unique<VisiteurSauvegarde>();
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepterVisiteur(visiteur.get());
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeEdition::sauvegarder()
///
/// Cette fonction permet de gérer le chargement dans le modeEdition.
///
////////////////////////////////////////////////////////////////////////
void ModeEdition::charger()
{
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chargerZone();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeEdition::gererToucheSupprimer()
///
/// Cette fonction permet de gérer la touche supprimer dans le modeEdition.
///
////////////////////////////////////////////////////////////////////////
void ModeEdition::gererToucheSupprimer()
{
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->chercher("table")->accepterVisiteur(visiteurSuppression_.get());
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeEdition::gererToucheAltEnfoncee()
///
/// Cette fonction permet de gérer la touche ALT enfoncee dans le modeEdition.
/// Elle appelle la fonction gererToucheAltEnfoncee selon l'état obtenu.
///
////////////////////////////////////////////////////////////////////////
void ModeEdition::gererToucheAltEnfoncee()
{
	FacadeModele::obtenirInstance()->obtenirEtat()->gererToucheAltEnfoncee();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeEdition::gererToucheAltRelachee()
///
/// Cette fonction permet de gérer la touche ALT relachee dans le modeEdition.
/// Elle appelle la fonction gererToucheAltRelachee selon l'état obtenu.
///
////////////////////////////////////////////////////////////////////////
void ModeEdition::gererToucheAltRelachee()
{
	FacadeModele::obtenirInstance()->obtenirEtat()->gererToucheAltRelachee();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void  ModeEdition::gererClicDroitEnfonce(const int& x, const int& y)
///
/// Cette fonction permet de gérer le clic droit enfonce dans le modeEdition.
/// Elle appelle la fonction gererClicDroitEnfonce selon l'état obtenu.
///
///@param[in] x : La position en x du curseur de la souris lors d'un clic droit.
///@param[in] y : La position en y du curseur de la souris lors d'un clic droit.
///
////////////////////////////////////////////////////////////////////////
void  ModeEdition::gererClicDroitEnfonce(const int& x, const int& y)
{
	FacadeModele::obtenirInstance()->obtenirEtat()->gererClicDroitEnfonce(x,y);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void  ModeEdition::gererClicDroitRelache(const int& x, const int& y)
///
/// Cette fonction permet de gérer le clic droit relache dans le modeEdition.
/// Elle appelle la fonction gererClicDroitRelache selon l'état obtenu.
///
///@param[in] x : La position en x du curseur de la souris lors d'un clic droit.
///@param[in] y : La position en y du curseur de la souris lors d'un clic droit.
///
////////////////////////////////////////////////////////////////////////
void  ModeEdition::gererClicDroitRelache(const int& x, const int& y)
{
	FacadeModele::obtenirInstance()->obtenirEtat()->gererClicDroitRelache(x,y);;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void  ModeEdition::gererClicGaucheEnfonce(const int& x, const int& y)
///
/// Cette fonction permet de gérer le clic gauche enfonce dans le modeEdition.
/// Elle appelle la fonction gererClicGaucheEnfonce selon l'état obtenu.
///
///@param[in] x : La position en x du curseur de la souris lors d'un clic droit.
///@param[in] y : La position en y du curseur de la souris lors d'un clic droit.
///
////////////////////////////////////////////////////////////////////////
void  ModeEdition::gererClicGaucheEnfonce(const int& x, const int& y)
{
	FacadeModele::obtenirInstance()->obtenirEtat()->gererClicGaucheEnfonce(x,y);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void  ModeEdition::gererClicGaucheRelache(const int& x, const int& y)
///
/// Cette fonction permet de gérer le clic gauche relache dans le modeEdition.
/// Elle appelle la fonction gererClicGaucheRelache selon l'état obtenu.
///
///@param[in] x : La position en x du curseur de la souris lors d'un clic droit.
///@param[in] y : La position en y du curseur de la souris lors d'un clic droit.
///
////////////////////////////////////////////////////////////////////////
void  ModeEdition::gererClicGaucheRelache(const int& x, const int& y)
{
	FacadeModele::obtenirInstance()->obtenirEtat()->gererClicGaucheRelache(x,y);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void  ModeEdition::gererMouvementSouris(const int& x, const int& y)
///
/// Cette fonction permet de gérer le mouvement de souris dans le modeEdition.
/// Elle appelle la fonction gererMouvementSouris selon l'état obtenu.
///
///@param[in] x : La position en x du curseur de la souris lors d'un mouvement de souris.
///@param[in] y : La position en y du curseur de la souris lors d'un mouvement de souris.
///
////////////////////////////////////////////////////////////////////////
void  ModeEdition::gererMouvementSouris(const int& x, const int& y)
{
	FacadeModele::obtenirInstance()->obtenirEtat()->gererMouvementSouris(x,y);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeEdition::gererMoletteSouris(const int & delta)
///
/// Cette fonction permet de gérer la molette de le souris dans le modeEdition.
///
/// Selon le signe du delta, nous ferons un zoom in ou out.
///
///@param[in] delta : La différence entre du mouvement de molette de la souris.
///
////////////////////////////////////////////////////////////////////////
void ModeEdition::gererMoletteSouris(const int& delta)
{
	if (FacadeModele::obtenirInstance()->obtenirVue()->obtenirProjection().estPerspective()) {

	}
	else {
		if (delta > 0) {
			FacadeModele::obtenirInstance()->obtenirVue()->zoomerIn();
		}
		else {
			FacadeModele::obtenirInstance()->obtenirVue()->zoomerOut();
		}
	}
}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////