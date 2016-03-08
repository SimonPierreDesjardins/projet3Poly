///////////////////////////////////////////////////////////////////////////////
/// @file ComporterAbstrait.cpp
/// @author Olivier St-Amour, Camille Gendreau
/// @date 20016-02-16
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "ComportementAbstrait.h"
#include "ControleRobot.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementAbstrait::ComportementAbstrait(ControleRobot* controleRobot)
///
/// Constructeur
///
/// @param[in] controleRobot: Pointeur vers le controleur du robot auquel le comportement est assigné
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
ComportementAbstrait::ComportementAbstrait(ControleRobot* controleRobot)
{
	controleRobot_ = std::unique_ptr<ControleRobot>(controleRobot);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementAbstrait::~ComportementAbstrait()
///
/// Destructeur
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
ComportementAbstrait::~ComportementAbstrait()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementAbstrait::~ComportementAbstrait()
///
/// Assigne au comportement le comportement qui devrait le suivre lorsque la condition de fin est atteinte.
///
/// @param[in] prochainComportement: Valeur enum indiquant le prochain comportement a adopter.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ComportementAbstrait::assignerComportementSuivant(eComportement comportementSuivant){
	comportementSuivant_ = comportementSuivant;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementAbstrait::~ComportementAbstrait()
///
/// Assigne au comportement le comportement qui devrait le suivre lorsque la condition de fin est atteinte.
///
/// @return le comportement suivant a adopter.
///
////////////////////////////////////////////////////////////////////////
eComportement ComportementAbstrait::obtenirComportementSuivant(){
	return comportementSuivant_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementAbstrait::obtenirNomComportement()
///
/// Retourne le type de comportement en string.
///
/// @return Le string correspondant au nom de classe.
///
////////////////////////////////////////////////////////////////////////
std::string ComportementAbstrait::obtenirNomComportement(){
	return typeid(*this).name();
}

///////////////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////////////