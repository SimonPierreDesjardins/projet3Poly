///////////////////////////////////////////////////////////////////////////////
/// @file ComporterAbstrait.cpp
/// @author Olivier St-Amour
/// @date 20016-02-16
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "ComportementAbstrait.h"
#include "rapidjson\filewritestream.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementAbstrait::ComportementAbstrait()
///
/// Constructeur
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
ComportementAbstrait::ComportementAbstrait()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementAbstrait::ComportementAbstrait(TypeComportement prochainComportement)
///
/// Constructeur par paramètre
///
///@param[in] prochaineComportement: le comportement que le robot adopte une fois le comportement actuel terminé
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
ComportementAbstrait::ComportementAbstrait(TypeComportement prochainComportement){
	this->comportementSuivant_ = prochainComportement;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementAbstrait::ComportementAbstrait(rapidjson::Value::ConstValueIterator comportementJSON)
///
/// Constructeur par paramètre
///
///@param[in] comportementJSON: le comportement en format JSON
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
ComportementAbstrait::ComportementAbstrait(const rapidjson::Value& comportementJSON){
	fromJson(comportementJSON);
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
void ComportementAbstrait::assignerComportementSuivant(TypeComportement comportementSuivant){
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
TypeComportement ComportementAbstrait::obtenirComportementSuivant(){
	return comportementSuivant_;
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
void ComportementAbstrait::toJSON(rapidjson::Writer<rapidjson::FileWriteStream>& writer){
	writer.Key("comportementSuivant");
	writer.Int(comportementSuivant_);
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
void ComportementAbstrait::fromJson(const rapidjson::Value& comportementJSON){
	this->comportementSuivant_ = TypeComportement(comportementJSON.MemberBegin()->value.GetInt());
}

///////////////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////////////