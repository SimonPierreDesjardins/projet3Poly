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
/// @param[in] controleRobot: Pointeur vers le controleur du robot auquel le comportement est assign�
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
/// Constructeur par param�tre
///
/// @param[in] prochainComportement : le comportement que le robot adopte une fois le comportement actuel termin�
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
ComportementDeviation::ComportementDeviation(TypeComportement prochainComportement) : ComportementAbstrait(prochainComportement){}

////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementDeviation::ComportementDeviation(const rapidjson::Value& comportementJSON)
///
/// Constructeur par param�tre
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
/// Constructeur par param�tres
///
/// @param[in] prochaincomportement : le comportement que le robot adopte une fois le comportement actuel termin�
/// @param[in] angleMax : l'angle maximal de d�viation
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
/// V�rifie si le comportement doit changer ou proc�der � une prochaine action sur sa liste.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ComportementDeviation::mettreAJour(){
	if (controleRobot_ != nullptr){
		//Impl�mentation de l'exception Rapport d'�licitation p.22
		if (controleRobot_->ligneDetectee()){
			if (!ignorerLigne_){
				controleRobot_->assignerComportement(SUIVIDELIGNE, L"Ligne d�tect�e");
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
				// D�vier � gauche et v�rifier angle
				controleRobot_->traiterCommande(&CommandeRobot(DEVIATION_GAUCHE), false);
				angleAtteinte = noeud->obtenirAngleRotation() > angleCible_;
			}
			else{
				// D�vier � droite et v�rifier angle
				controleRobot_->traiterCommande(&CommandeRobot(DEVIATION_DROITE), false);
				angleAtteinte = noeud->obtenirAngleRotation() < angleCible_;
			}
		}
		if (angleAtteinte){
			controleRobot_->assignerComportement(comportementSuivant_, L"Deviation termin�e");
		}
	}
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
void ComportementDeviation::toJSON(rapidjson::Writer<rapidjson::FileWriteStream>& writer){
	ComportementAbstrait::toJSON(writer);
	writer.Key("maxAngle");
	writer.Double(maxAngle_);
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
void ComportementDeviation::fromJson(const rapidjson::Value& comportementJSON){
	ComportementAbstrait::fromJson(comportementJSON);
	rapidjson::Value::ConstMemberIterator itr = comportementJSON.MemberBegin() + 1;
	maxAngle_ = itr->value.GetDouble();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementDeviation::setAngleMaxRotation(double angle)
///
/// Ajuste l'angle pour la d�viation
///
/// @param[in] angle: l'angle � partir duquel on change de comportement. negatif implique une deviation vers la droite.
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
