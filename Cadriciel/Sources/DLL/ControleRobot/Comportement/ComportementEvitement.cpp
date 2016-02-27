///////////////////////////////////////////////////////////////////////////////
/// @file ComportementEvitement.cpp
/// @author Olivier St-Amour
/// @date 20016-02-16
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "ComportementEvitement.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementEvitement::ComportementEvitement()
///
/// Constructeur
///
/// @param[in] Aucun
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
ComportementEvitement::ComportementEvitement()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementDeviation::ComportementDeviation(eComportement prochainComportement, double angleMax)
///
/// Constructeur par paramètres
///
/// @param[in] prochaincomportement : le comportement que le robot adopte une fois le comportement actuel terminé
/// @param[in] maxTemps : le temps maximal d'un évitement
/// @param[in] angleMax : l'angle maximal de déviation
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
ComportementEvitement::ComportementEvitement(eComportement prochainComportement, double maxTemps, double maxAngle) : ComportementAbstrait(prochainComportement){
	this->maxTemps = maxTemps;
	this->maxAngle = maxAngle;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementEvitement::~ComportementEvitement()
///
/// Destructeur
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
ComportementEvitement::~ComportementEvitement()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementEvitement::initialiser()
///
/// Implementation qui ramene le comportement a son etat initial
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ComportementEvitement::initialiser(){

}

////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementEvitement::mettreAJour()
///
/// Implementation qui ramene le comportement a son etat initial
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ComportementEvitement::mettreAJour(){

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::toJson(rapidjson::Writer<rapidjson::FileWriteStream>& writer)
///
/// Cette fonction obtient les valeurs à sauvegarder pour le comportement en JSON
///
/// @param[in] writer : Le stream dans lequel le JSON est écrit
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ComportementEvitement::toJSON(rapidjson::Writer<rapidjson::FileWriteStream>& writer){
	ComportementAbstrait::toJSON(writer);
	writer.Key("maxTemps");
	writer.Double(maxTemps);
	writer.Key("maxAngle");
	writer.Double(maxAngle);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::fromJson(rapidjson::Value::ConstValueIterator noeudJSON)
///
/// Cette fonction assigne les valeurs nécessaires au chargement d'un comportement à partir d'un fichier JSON.
///
/// @param[in] comportementJSON : Le comportement du fichier JSON contenant les informations à charger.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ComportementEvitement::fromJson(const rapidjson::Value& comportementJSON){
	ComportementAbstrait::fromJson(comportementJSON);
	rapidjson::Value::ConstMemberIterator itr = comportementJSON.MemberBegin() + 1;
	maxTemps = itr->value.GetDouble();
	itr++;
	maxAngle = itr->value.GetDouble();
}

///////////////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////////////
