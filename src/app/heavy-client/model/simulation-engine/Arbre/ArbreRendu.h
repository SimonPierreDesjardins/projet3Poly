///////////////////////////////////////////////////////////////////////////////
/// @file ArbreRendu.h
/// @author Martin Bisson
/// @date 2007-01-28
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_ARBRERENDU_H__
#define __ARBRE_ARBRERENDU_H__

#include "NoeudComposite.h"

#include <unordered_map>
#include <memory>

#include "UsineNoeud.h"

class NoeudAbstrait;

///////////////////////////////////////////////////////////////////////////
/// @class ArbreRendu
/// @brief Classe d'arbre de rendu qui contient la racine de l'arbre de
///        rendu avec les usines qui permettent d'ajouter des noeuds à
///        cet arbre.
///
///        La profondeur de cet arbre est limitée par la taille de la pile
///        des matrices et la taille de la pile des noms pour la sélection
///        OpenGL, étant donné que chaque niveau de l'arbre effectue un
///        "push" sur chacune de ces piles lors du rendu.  L'arbre ne
///        vérifie pas que la profondeur reste sous la limite, mais il
///        offre des fonctions permettant de le vérifier aisément.
///
/// @author Martin Bisson
/// @date 2007-01-28
///////////////////////////////////////////////////////////////////////////
class ArbreRendu : public NoeudComposite
{
public:
	// Constructeur par défaut.
	ArbreRendu();

	// Destructeur.
	virtual ~ArbreRendu();

	// Ajoute une usine associée à un type de noeud.
	inline void ajouterUsine(EntityType type, const std::string& name, std::unique_ptr<const UsineAbstraite> usine);

    // Crée un nouveau noeud.
    std::shared_ptr<NoeudAbstrait> creerNoeud(const std::string& nomNouveauNoeud) const;
    std::shared_ptr<NoeudAbstrait> creerNoeud(EntityType entityType) const;

    // Crée et ajoute un nouveau noeud à l'arbre.
    std::shared_ptr<NoeudAbstrait> ajouterNouveauNoeud(const std::string& nomParent, const std::string& typeNouveauNoeud);

	// Crée et ajoute un nouveau noeud avec une référence sur le parent.
    std::shared_ptr<NoeudAbstrait> ajouterNouveauNoeud(NoeudAbstrait* parent, const std::string& typeNouveauNoeud);


    /// Calcule la profondeur maximale possible pour l'arbre de rendu.
    static unsigned int calculerProfondeurMaximale();

	/// Accepter un visiteur.
	void accepterVisiteur(VisiteurAbstrait* visiteur);

	/// Assigne le chemin du fichier sélectionné par l'utilisateur
	void assignerCheminFichierZone(std::string chemin);
	
	/// Retourne un pointeur vers le fichier sélectionné par l'utilisateur
	FILE* obtenirFichierZone(std::string mode);

	/// Retourne le chemin vers le fichier de zone de base
	std::string obtenirCheminFichierZoneDefaut();

	// Obtenir le nombre d'objet sélectionné
	int obtenirNombreSelection();

    // Permet de lancer la sélection opengl.
    std::vector<int> chercherSelection(const glm::dvec2&, const double& dx, const double& dy);

	// Obtient l'angle de rotaion du noeud selectionné. 
	double obtenirAngleRotation();
	// Obtient le facteur de mise à échelle du noeud selectionné. 
	double obtenirFacteurMiseAEchelle();
	// Obtient la position relative en X du noeud selectionné.
	double obtenirPositionRelativeX();
	// Obtient la position relative en Y du noeud selectionné.
	double obtenirPositionRelativeY();
	// Assigne l'angle de rotaion du noeud selectionné. 
	void assignerAngleRotation(const double& angle);
	// Assigne le facteur de mise à échelle du noeud selectionné.
	void assignerFacteurMiseAEchelle(const double& facteurMiseAEchelle);
	// Assigne la position relative en x du noeud sélectionné.
	void assignerPositionRelativeX(const double& positionRelativeX);
	// Assigne la position relative en x du noeud sélectionné. 
	void assignerPositionRelativeY(const double& positionRelativeY);

protected:
	// Retourne un pointeur vers le fichier de structure de base
	FILE* obtenirFichierZoneDefaut(std::string mode);

	// Constante représentant l'extension d'un fichier zone
	const std::string EXTENSION_ZONE = ".zone";

	// Constante représentant le fichier zone contenant la structure de base
	const std::string cheminFichierZoneDefaut = "./Zones/defaut" + EXTENSION_ZONE;

	// Chemin vers le fichier de zone sélectionné par l'utilisateur
	std::string cheminFichierZone;



private:
    /// Définition du type pour l'association du nom d'un type vers l'usine
	/// correspondante.
	using RegistreUsines = std::unordered_map<std::string, std::unique_ptr<const UsineAbstraite>>;
	using NameContainer = std::unordered_map<EntityType, std::string>;
	// Les noeuds en fonction de leur identifiant.

	/// Association du nom d'un type vers l'usine correspondante.
	RegistreUsines usines_;   
	NameContainer  names_;
};


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void ArbreRendu::ajouterUsine(const std::string& type, const UsineNoeud* usine)
///
/// Cette fonction permet d'ajouter une usine qui sera ensuite utilisée
/// pour créer de nouveaux noeuds.
///
/// @param[in] type  : La chaîne qui identifie le type de noeuds à créer
///                    avec cette usine.
/// @param[in] usine : L'usine ajoutée.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
inline void ArbreRendu::ajouterUsine(EntityType type, const std::string& name, std::unique_ptr<const UsineAbstraite> usine)
{
   usines_[name].swap(usine);
   names_.insert(std::make_pair(type, name));
}


#endif // __ARBRE_ARBRERENDU_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
