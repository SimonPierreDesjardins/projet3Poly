///////////////////////////////////////////////////////////////////////////////
/// @file ComporterDeviation.cpp
/// @author Olivier St-Amour
/// @date 20016-02-16
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "ComportementDeviation.h"
#include "rapidjson\filewritestream.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementDeviation::ComportementDeviation()
///
/// Constructeur
///
/// @param[in] Aucun
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
ComportementDeviation::ComportementDeviation()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementDeviation::ComportementDeviation(TypeComportement prochainComportement)
///
/// Constructeur par paramètre
///
/// @param[in] prochainComportement : le comportement que le robot adopte une fois le comportement actuel terminé
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
ComportementDeviation::ComportementDeviation(TypeComportement prochainComportement) : ComportementAbstrait(prochainComportement){}

////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementDeviation::ComportementDeviation(const rapidjson::Value& comportementJSON)
///
/// Constructeur par paramètre
///
/// @param[in] comportementJSON : le comportement en format JSON
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
ComportementDeviation::ComportementDeviation(const rapidjson::Value& comportementJSON){
	fromJson(comportementJSON);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementDeviation::ComportementDeviation(TypeComportement prochainComportement, double angleMax)
///
/// Constructeur par paramètres
///
/// @param[in] prochaincomportement : le comportement que le robot adopte une fois le comportement actuel terminé
/// @param[in] angleMax : l'angle maximal de déviation
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
ComportementDeviation::ComportementDeviation(TypeComportement prochainComportement, double angleMax) : ComportementAbstrait(prochainComportement){
	this->maxAngle = angleMax;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementDeviation::~ComportementDeviation()
///
/// Destructeur
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
ComportementDeviation::~ComportementDeviation()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementDeviation::initialiser()
///
/// Implementation qui ramene le comportement a son etat initial
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ComportementDeviation::initialiser(){

}

////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementDeviation::mettreAJour()
///
/// Implementation qui ramene le comportement a son etat initial
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ComportementDeviation::mettreAJour(){

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ComportementDeviation::setAngleMaxRotation(double angle)
///
/// Fonction servant à assigner l'angle de rotation maximale
///
/// @param angle : la valeur de l'angle de rotation maximale
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ComportementDeviation::setAngleMaxRotation(double angle){
	maxAngle = angle;
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
void ComportementDeviation::toJSON(rapidjson::Writer<rapidjson::FileWriteStream>& writer){
	ComportementAbstrait::toJSON(writer);
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
void ComportementDeviation::fromJson(const rapidjson::Value& comportementJSON){
	ComportementAbstrait::fromJson(comportementJSON);
	rapidjson::Value::ConstMemberIterator itr = comportementJSON.MemberBegin() + 1;
	maxAngle = itr->value.GetDouble();
}


///////////////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////////////
