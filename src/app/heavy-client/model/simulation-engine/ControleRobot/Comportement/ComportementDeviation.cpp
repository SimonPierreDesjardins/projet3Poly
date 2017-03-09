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
#include "ControleRobot.h"
#include "CommandeRobot.h"
#include "NoeudRobot.h"
#include "rapidjson\filewritestream.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementDeviation::ComportementDeviation()
///
/// Constructeur
///
/// @param[in] controleRobot: Pointeur vers le controleur du robot auquel le comportement est assigné
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
	this->maxAngle_ = angleMax;
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
	NoeudRobot* noeud = controleRobot_->obtenirNoeud();
	if (noeud != nullptr){
		angleCible_ = noeud->obtenirAngleRotation() + maxAngle_;
	}
	gauche = maxAngle_ >= 0;
	ignorerLigne_ = true;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementDeviation::mettreAJour()
///
/// Vérifie si le comportement doit changer ou procéder à une prochaine action sur sa liste.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ComportementDeviation::mettreAJour(){
	if (controleRobot_ != nullptr){
		//Implémentation de l'exception Rapport d'élicitation p.22
		if (controleRobot_->ligneDetectee()){
			if (!ignorerLigne_){
				controleRobot_->assignerComportement(SUIVIDELIGNE, L"Ligne détectée");
			}
		}
		else{
			ignorerLigne_ = false;
		}

		bool angleAtteinte = false;

		NoeudRobot* noeud = controleRobot_->obtenirNoeud();
		// Rotation du robot
		if (noeud != nullptr){
			if (gauche){
				// Dévier à gauche et vérifier angle
				controleRobot_->traiterCommande(&CommandeRobot(DEVIATION_GAUCHE), false);
				angleAtteinte = noeud->obtenirAngleRotation() > angleCible_;
			}
			else{
				// Dévier à droite et vérifier angle
				controleRobot_->traiterCommande(&CommandeRobot(DEVIATION_DROITE), false);
				angleAtteinte = noeud->obtenirAngleRotation() < angleCible_;
			}
		}
		if (angleAtteinte){
			controleRobot_->assignerComportement(comportementSuivant_, L"Deviation terminée");
		}
	}
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
void ComportementDeviation::fromJson(const rapidjson::Value& comportementJSON){
	ComportementAbstrait::fromJson(comportementJSON);
	rapidjson::Value::ConstMemberIterator itr = comportementJSON.MemberBegin() + 1;
	maxAngle_ = itr->value.GetDouble();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementDeviation::setAngleMaxRotation(double angle)
///
/// Ajuste l'angle pour la déviation
///
/// @param[in] angle: l'angle à partir duquel on change de comportement. negatif implique une deviation vers la droite.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ComportementDeviation::setAngleMaxRotation(double angle){
	maxAngle_ = angle;
}
///////////////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////////////
