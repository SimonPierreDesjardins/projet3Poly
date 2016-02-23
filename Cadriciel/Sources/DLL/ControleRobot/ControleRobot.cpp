///////////////////////////////////////////////////////////////////////////////
/// @file ControleRobot.cpp
/// @author Olivier St-Amour
/// @date 20016-02-22
/// @version 2.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "ControleRobot.h"
#include "CommandeRobot.h"
#include "NoeudRobot.h"
#include "FacadeModele.h"
#include "ArbreRenduINF2990.h"
////////////////////////////////////////////////////////////////////////
///
/// @fn ControleRobot::ControleRobot()
///
/// Constructeur
///
/// @param[in] Aucun
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
ControleRobot::ControleRobot()
{
	ArbreRendu* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
	NoeudAbstrait* table = arbre->chercher(0);
	std::shared_ptr<NoeudAbstrait> robot = arbre->creerNoeud(ArbreRenduINF2990::NOM_ROBOT);
	table->ajouter(robot);
	robot_ = std::static_pointer_cast<NoeudRobot>(robot).get();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ControleRobot::~ControleRobot()
///
/// Destructeur
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
ControleRobot::~ControleRobot()
{
}

void ControleRobot::traiterCommande(CommandeRobot* commande)
{

}

///////////////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////////////
