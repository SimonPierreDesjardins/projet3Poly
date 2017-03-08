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
#include "rapidjson\filewritestream.h"
#include <typeinfo>

////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementAbstrait::ComportementAbstrait(ControleRobot* controleRobot)
///
/// Constructeur
///
/// @param[in] controleRobot: Pointeur vers le controleur du robot auquel le comportement est assign�
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
/// Constructeur par param�tre
///
///@param[in] prochaineComportement: le comportement que le robot adopte une fois le comportement actuel termin�
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
/// Constructeur par param�tre
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
/// @fn ComportementAbstrait::assignerRobot(ControleRobot* controleRobot)
///
/// Assigne au comportement le comportement qui devrait le suivre lorsque la condition de fin est atteinte.
///
/// @param[in] controleRobot: Le pointeur au robot auquel le comportement est assign�
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ComportementAbstrait::assignerRobot(ControleRobot* controleRobot){
	controleRobot_ = controleRobot;
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
/// @fn ComportementAbstrait::obtenirNomComportement()
///
/// Retourne le type de comportement en string.
///
/// @return Le string correspondant au nom de classe.
///
////////////////////////////////////////////////////////////////////////
std::wstring ComportementAbstrait::obtenirNomComportement(){

    std::string type = typeid(*this).name();
    std::wstring wType(type.begin(), type.end());
    return wType;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::toJson(rapidjson::Writer<rapidjson::FileWriteStream>& writer)
///
/// Cette fonction obtient les valeurs � sauvegarder pour le comportement en JSON
///
/// @param[in] writer : Le stream dans lequel le JSON est �crit
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
/// Cette fonction assigne les valeurs n�cessaires au chargement d'un comportement � partir d'un fichier JSON.
///
/// @param[in] comportementJSON : Le comportement du fichier JSON contenant les informations � charger.
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