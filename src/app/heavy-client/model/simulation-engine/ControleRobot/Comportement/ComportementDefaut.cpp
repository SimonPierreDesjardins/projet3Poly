///////////////////////////////////////////////////////////////////////////////
/// @file ComporterDefaut.cpp
/// @author Olivier St-Amour, Camille Gendreau
/// @date 20016-02-16
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "ComportementDefaut.h"
#include "ControleRobot.h"
#include "CommandeRobot.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementDefaut::ComportementDefaut(ControleRobot* controleRobot)
///
/// Constructeur
///
/// @param[in] controleRobot: Le controlleur du robot auquel le comportement passera des commandes
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
ComportementDefaut::ComportementDefaut()
{
	comportementSuivant_ = DEFAUT;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementDefaut::ComportementDefaut(TypeComportement prochainComportement)
///
/// Constructeur par param�tre
///
/// @param[in] prochainComportement : le comportement que le robot adopte une fois le comportement actuel termin�
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
ComportementDefaut::ComportementDefaut(TypeComportement prochainComportement) : ComportementAbstrait(prochainComportement){}

////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementDefaut::ComportementDefaut(const rapidjson::Value& comportementJSON)
///
/// Constructeur par param�tre
///
/// @param[in] comportementJSON : le comportement en format JSON
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
ComportementDefaut::ComportementDefaut(const rapidjson::Value& comportementJSON){
	comportementSuivant_ = DEFAUT;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementDefaut::~ComportementDefaut()
///
/// Destructeur
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
ComportementDefaut::~ComportementDefaut()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementDefaut::initialiser()
///
/// Implementation qui ramene le comportement a son etat initial
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ComportementDefaut::initialiser(){

}

////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementDefaut::mettreAJour()
///
/// V�rifie si le comportement doit changer ou proc�der � une prochaine action sur sa liste.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ComportementDefaut::mettreAJour(){
	//Si une ligne est trouv�e nous passons � la suivie de ligne
	if (controleRobot_ != nullptr){
		if (controleRobot_->ligneDetectee()){
			controleRobot_->assignerComportement(SUIVIDELIGNE, L"Ligne d�tect�e");
		}

		controleRobot_->traiterCommande(&CommandeRobot(AVANCER), false);
	}
}

///////////////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////////////