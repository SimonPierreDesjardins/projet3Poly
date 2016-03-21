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
#include "ControleRobot.h"
#include "NoeudRobot.h"
#include "CommandeRobot.h"
#include "rapidjson\filewritestream.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementEvitement::ComportementEvitement()
///
/// Constructeur
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
ComportementEvitement::ComportementEvitement()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementEvitement::ComportementEvitement(TypeComportement prochainComportement)
///
/// Constructeur par paramètre
///
/// @param[in] prochainComportement : le comportement que le robot adopte une fois le comportement actuel terminé
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
ComportementEvitement::ComportementEvitement(TypeComportement prochainComportement) : ComportementAbstrait(prochainComportement){}

////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementEvitement::ComportementEvitement(const rapidjson::Value& comportementJSON)
///
/// Constructeur par paramètre
///
/// @param[in] comportementJSON : le comportement en format JSON
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
ComportementEvitement::ComportementEvitement(const rapidjson::Value& comportementJSON){
	fromJson(comportementJSON);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementDeviation::ComportementDeviation(TypeComportement prochainComportement, double angleMax)
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
ComportementEvitement::ComportementEvitement(TypeComportement prochainComportement, double maxTemps, double maxAngle) : ComportementAbstrait(prochainComportement){
	this->maxTemps_ = maxTemps;
	this->maxAngle_ = maxAngle;
	comportementSuivant_ = prochainComportement;
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
	startTime_ = time(nullptr);
	NoeudRobot* noeud = controleRobot_->obtenirNoeud();
	if (noeud != nullptr){
		angleCible_ = noeud->obtenirAngleRotation() + maxAngle_;
	}
	gauche = maxAngle_ >= 0;
	ignorerLigne_ = true;

}

////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementDefaut::mettreAJour()
///
/// Vérifie si le comportement doit changer ou procéder à une prochaine action sur sa liste.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ComportementEvitement::mettreAJour(){

	//Implémentation de l'exception Rapport d'élicitation p.22
	if (controleRobot_->ligneDetectee()){
		if (!ignorerLigne_){
			controleRobot_->assignerComportement(SUIVIDELIGNE, L"Ligne détectée");
		}
	}
	else{
		ignorerLigne_ = false;
	}

	// tant que le timer n'est pas expiré, recule, sinon pivoter
	if (difftime(time(nullptr), startTime_) < maxTemps_){
		controleRobot_->traiterCommande(&CommandeRobot(RECULER), false);
	}
	else {

		bool angleAtteinte = false;
		NoeudRobot* noeud = controleRobot_->obtenirNoeud();
		if (noeud != nullptr){
			// Rotation du robot
			if (gauche){
				// Dévier à gauche et vérifier angle
				controleRobot_->traiterCommande(&CommandeRobot(ROTATION_GAUCHE), false);
				angleAtteinte = noeud->obtenirAngleRotation() > angleCible_;
			}
			else{
				// Dévier à droite et vérifier angle
				controleRobot_->traiterCommande(&CommandeRobot(ROTATION_DROITE), false);
				angleAtteinte = controleRobot_->obtenirNoeud()->obtenirAngleRotation() < angleCible_;
			}
		}
		
		if (angleAtteinte){
			controleRobot_->assignerComportement(comportementSuivant_, L"Évitement terminé");
		}
	}

}

////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementEvitement::setAngleMaxRotation(double angle)
///
/// Assigne un nouvel angle relatif a atteindre après le recul avant de changer de comportement.
///
/// @param[in] angle: Le nouvel angle relatif que le comportment doit atteindre.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ComportementEvitement::setAngleMaxRotation(double angle){
	maxAngle_ = angle;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementEvitement::setTempsMaxReculons(double temps)
///
/// Assigne la duree du recul du robot avant de changer son angle.
///
/// @param[in] temps: Le nouvel angle relatif que le comportment doit atteindre.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ComportementEvitement::setTempsMaxReculons(double temps){
	maxTemps_ = temps;
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
	writer.Double(maxTemps_);
	writer.Key("maxAngle");
	writer.Double(maxAngle_);
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
	maxTemps_ = itr->value.GetDouble();
	itr++;
	maxAngle_ = itr->value.GetDouble();
}

///////////////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////////////
