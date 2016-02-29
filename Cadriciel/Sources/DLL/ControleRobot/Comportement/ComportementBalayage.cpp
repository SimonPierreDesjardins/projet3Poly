///////////////////////////////////////////////////////////////////////////////
/// @file ComporterBalayage.cpp
/// @author Olivier St-Amour
/// @date 20016-02-16
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "ComportementBalayage.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementBalayage::ComportementBalayage()
///
/// Constructeur
///
/// @param[in] Aucun
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
ComportementBalayage::ComportementBalayage()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementBalayage::ComportementBalayage(TypeComportement prochainComportement)
///
/// Constructeur par param�tre
///
/// @param[in] prochainComportement : le comportement que le robot adopte une fois le comportement actuel termin�
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
ComportementBalayage::ComportementBalayage(TypeComportement prochainComportement) : ComportementAbstrait(prochainComportement){}

////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementBalayage::ComportementBalayage(const rapidjson::Value& comportementJSON)
///
/// Constructeur par param�tre
///
/// @param[in] comportementJSON : le comportement en format JSON
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
ComportementBalayage::ComportementBalayage(const rapidjson::Value& comportementJSON) : ComportementAbstrait(comportementJSON){}


////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementBalayage::~ComportementBalayage()
///
/// Destructeur
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
ComportementBalayage::~ComportementBalayage()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementBalayage::initialiser()
///
/// Implementation qui ramene le comportement a son etat initial
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ComportementBalayage::initialiser(){

}

////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementBalayage::mettreAJour()
///
/// Implementation qui ramene le comportement a son etat initial
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ComportementBalayage::mettreAJour(){

}
///////////////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////////////