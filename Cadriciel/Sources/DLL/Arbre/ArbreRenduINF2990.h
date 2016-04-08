///////////////////////////////////////////////////////////////////////////
/// @file ArbreRenduINF2990.h
/// @author Martin Bisson
/// @date 2007-03-23
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_ARBRERENDUINF2990_H__
#define __ARBRE_ARBRERENDUINF2990_H__


#include "ArbreRendu.h"
#include <map>
#include <string>
#include "rapidjson\document.h"

class VisiteurAbstrait;

///////////////////////////////////////////////////////////////////////////
/// @class ArbreRenduINF2990
/// @brief Classe qui représente l'arbre de rendu spécifique au projet de
///        INF2990.
///
///        Cette classe s'occupe de configurer les usines des noeuds qui
///        seront utilisés par le projet.
///
/// @author Martin Bisson
/// @date 2007-03-23
///////////////////////////////////////////////////////////////////////////
class ArbreRenduINF2990 : public ArbreRendu
{
public:
	/// Constructeur par défaut.
	ArbreRenduINF2990();
	/// Destructeur.
	virtual ~ArbreRenduINF2990();

	/// Initialise l'arbre de rendu à son état initial.
	void initialiser();

	/// Charge le fichier de sauvegarde présentement assigné à l'arbre de rendu
	void chargerZone();

	/// La chaîne représentant le type du robot.
	static const std::string NOM_ROBOT;

	/// La chaîne représentant le type de la table.
	static const std::string NOM_TABLE;

	/// La chaîne représentant le type des poteaux.
	static const std::string NOM_POTEAU;

	/// La chaîne représentant le type des murs.
	static const std::string NOM_MUR;

	/// La chaîne représentant le type des lignes.
	static const std::string NOM_LIGNENOIRE;

	/// La chaîne représentant le type des segments.
	static const std::string NOM_SEGMENT;

	/// La chaîne représentant le type des duplications. 
	static const std::string NOM_DUPLICATION;

	/// La chaîne représentant le type du point de départ. 
	static const std::string NOM_JONCTION;

	/// La chaîne représentant le type du robot.
	static const std::string NOM_ROUES;
   
	/// La chaîne représentant le type du point de départ. 
	static const std::string NOM_DEPART;   

	/// La chaine représentant le type du skybox.
	static const std::string NOM_SKYBOX;

private:
	/// Charge une zone selon le fichier binaire qu'on lui passe en paramètre
	void chargerZone(FILE* fp);

	/// Fonction récursive pour créer tous les noeuds selon l'arbre Json qui se trouve dans le fichier de sauvegarde
	void chargerZone(rapidjson::Value::ConstValueIterator noeudJSON, shared_ptr<NoeudAbstrait> parent);

	/// Charge le fichier zone_par_defaut.json qui contient la structure de base de l'arbre de rendu
	void chargerZoneDefaut();

};

#endif // __ARBRE_ARBRERENDUINF2990_H__

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
