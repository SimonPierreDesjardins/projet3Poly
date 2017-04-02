///////////////////////////////////////////////////////////////////////////////
/// @file ComporterBalayage.cpp
/// @author Olivier St-Amour, Camille Gendreau
/// @date 2016-02-16
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "ComportementBalayage.h"
#include "ControleRobot.h"
#include "NoeudRobot.h"
#include "CommandeRobot.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementBalayage::ComportementBalayage(ControleRobot* controleRobot)
///
/// Constructeur
///
/// @param[in] controleRobot: Pointeur vers le controleur du robot auquel le comportement est assigné
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
/// Constructeur par paramètre
///
/// @param[in] prochainComportement : le comportement que le robot adopte une fois le comportement actuel terminé
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
ComportementBalayage::ComportementBalayage(TypeComportement prochainComportement) : ComportementAbstrait(prochainComportement){}

////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementBalayage::ComportementBalayage(const rapidjson::Value& comportementJSON)
///
/// Constructeur par paramètre
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
void ComportementBalayage::initialiser()
{
	// Nous assignons une cible initiale pour la rotation antihoraire de 90 deg
	etatRotation = 0;
	NoeudRobot* noeud = controleRobot_->obtenirNoeud();
	if (noeud != nullptr)
	{
		angleCible = noeud->getPhysicsComponent().rotation.z + 90;
	}
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
void ComportementBalayage::mettreAJour(){
	if (controleRobot_ != nullptr){
		//Si une ligne est trouvée nous passons à la suivie de ligne
		if (controleRobot_->ligneDetectee()){
			controleRobot_->assignerComportement(SUIVIDELIGNE, L"Ligne détectée");
		}

		NoeudRobot* noeud = controleRobot_->obtenirNoeud();

		if (noeud != nullptr)
		{
			PhysicsComponent& physics = noeud->getPhysicsComponent();
			switch (etatRotation)
			{
				// Nous sommes dans la premiere rotation 90 deg antihoraire
			case 0:
				// Envoie la commande de rotation anti-horaire
				controleRobot_->traiterCommande(&CommandeRobot(ROTATION_GAUCHE), false);
				// si tu atteins l'angle voulu
				if (physics.rotation.z > angleCible)
				{
					//change l'angle cible et l'état
					angleCible = physics.rotation.z - 180;
					etatRotation++;
				}
				break;


				// Nous sommes dans la deuxieme rotation 180 deg horaire
			case 1:
				// Envoie la commande de rotation anti-horaire
				controleRobot_->traiterCommande(&CommandeRobot(ROTATION_DROITE), false);
				// si tu atteins l'angle voulu
				if (physics.rotation.z < angleCible)
				{
					//change l'angle cible et l'état
					angleCible = physics.rotation.z + 90;
					etatRotation++;
				}
				break;

			case 2:
				// Envoie la commande de rotation anti-horaire
				controleRobot_->traiterCommande(&CommandeRobot(ROTATION_GAUCHE), false);
				// si tu atteins l'angle voulu
				if (physics.rotation.z > angleCible)
				{
					controleRobot_->assignerComportement(comportementSuivant_, L"Balayage terminé");
				}
				break;
			}
		}
	}
}
///////////////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////////////