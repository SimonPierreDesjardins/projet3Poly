///////////////////////////////////////////////////////////////////////////////
/// @file NoeudAbstrait.h
/// @author DGI-INF2990
/// @date 2007-01-24
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#ifndef __ARBRE_NOEUDS_NOEUDABSTRAIT_H__
#define __ARBRE_NOEUDS_NOEUDABSTRAIT_H__

#include "GL/glew.h"
#include <string>
#include <memory>
#include <iterator>

#include "Utilitaire.h"
#include "glm\glm.hpp"
#include "rapidjson\writer.h"
#include "rapidjson\document.h"

#include "PhysicsComponent.h"
#include "RectangleEnglobant.h"

/// D�clarations avanc�es pour contenir un pointeur vers un mod�le3D et son storage

namespace modele {
	class Modele3D;
}
namespace opengl {
	class VBO;
}

namespace rapidjson {
	class FileWriteStream;
}

class VisiteurAbstrait;

class FormeEnglobanteAbstraite;

enum EntityType
{
	TABLE_ENTITY,
	START_ENTITY,
	DUPLICATION_ENTITY,
	POST_ENTITY,
	WALL_ENTITY,
	BLACK_LINE_ENTITY,
	SEGMENT_ENTITY,
	JUNCTION_ENTITY,
	WHEEL_ENTITY,
	ROBOT_ENTITY,
	F1_ENTITY,
	TRUCK_ENTITY,
	VOLKS_ENTITY,
	AUDI_ENTITY,
	TELEPORT_ENTITY
};

///////////////////////////////////////////////////////////////////////////
/// @class NoeudAbstrait
/// @brief Classe de base du patron composite utilis�e pour cr�er l'arbre
///        de rendu.
///
///        Cette classe abstraite comprend l'interface de base que doivent
///        implanter tous les noeuds pouvant �tre pr�sent dans l'arbre de
///        rendu.
///
/// @author DGI-2990
/// @date 2007-01-24
///////////////////////////////////////////////////////////////////////////
class NoeudAbstrait
{
public:
	/// Constructeur.
	NoeudAbstrait(uint32_t localId, const std::string& type = std::string{ "" });
	/// Destructeur.
	virtual ~NoeudAbstrait();

	/// Obtient le parent de ce noeud.
	inline NoeudAbstrait* obtenirParent();
	/// Obtient le parent de ce noeud (version constante).
	inline const NoeudAbstrait* obtenirParent() const;
	/// Assigne le parent de ce noeud.
	inline void assignerParent(NoeudAbstrait* parent);

	inline PhysicsComponent& getPhysicsComponent();

	/*	
	/// Obtient la position relative du noeud.
	inline const glm::dvec3& obtenirPositionRelative() const;
	/// Assigne la position relative du noeud.
	inline void assignerPositionRelative(const glm::dvec3& positionRelative);	
    /// Obtient la position courante du noeud.
    inline const glm::dvec3& obtenirPositionCourante() const;
    /// Assigne la position courante du noeud.
    inline void assignerPositionCourante(const glm::dvec3& positionRelative);
	/// Obtient l'angle de rotation du noeud.
	inline double obtenirAngleRotation() const;
	/// Assigne l'angle de rotation du noeud par rapport au plan xy.
	inline void assignerAngleRotation(const double& angleRotation);
	/// Obtient le facteur de dimension du noeud.
	inline double obtenirFacteurMiseAEchelle() const;
	/// Assigne le facteur de dimension
	inline void assignerFacteurMiseAEchelle(const double& facteurDimension);
	*/

	// Obtenir l'identifiant local.
	inline uint32_t getId() const;
	// Assigner l'identificant distant.
	inline void setId(uint32_t serverId);

	/// Obtient le quadrilat�re englobant du noeud.
    inline const utilitaire::BoiteEnglobante& obtenirBoiteEnglobanteModele() const;

    virtual FormeEnglobanteAbstraite* obtenirFormeEnglobante();
    virtual const FormeEnglobanteAbstraite* obtenirFormeEnglobante() const;
    virtual void mettreAJourFormeEnglobante();

	/// Obtient le type du noeud.
	inline const std::string& obtenirNom() const;
	inline EntityType getType() const;

	inline void setSelectionColor(const glm::vec4& color);
	inline uint32_t getOwnerId() const;
	inline void setOwnerId(uint32_t userId);

	/// �crit l'�tat de l'affichage du du noeud.
	inline void assignerAffiche(bool affiche);
	/// V�rifie si le noeud se fait afficher.
	inline bool estAffiche() const;
	/// �crit l'�tat de la s�lection du noeud.
	inline void assignerSelection(bool selectionne);
	/// V�rifie si le noeud est s�lectionn�.
	inline bool estSelectionne() const;
	/// �crit si le noeud peut �tre s�lectionn� ou non.
	inline void assignerEstSelectionnable(bool selectionnable);
	/// V�rifie si le noeud est s�lectionnable.
	inline bool estSelectionnable() const;
	/// �crit si le noeud peut �tre enregistr� ou non.
	inline void assignerEstEnregistrable(bool enregistrable);
	/// V�rifie si le noeud est enregistrable.
	inline bool estEnregistrable() const;
	/// �crit si le noeud peut �tre enregistr� ou non.
	inline bool assignerEstDuplicable(bool estDuplicable);
	/// V�rifie si l'objet peut �tre dupliqu�.
	inline bool estDuplicable() const;

	inline bool isErasable() const;
	inline void setIsErasable(bool isErasable);

	/// Assigne le mod�le3D et la liste d'affichage du noeud courant
	void assignerObjetRendu(modele::Modele3D const* modele, opengl::VBO const* liste);

	// Interface d'un noeud

	/// Calcule la profondeur de l'arbre sous le noeud courant.
	virtual unsigned int calculerProfondeur() const;

	/// Vide le noeud de ses enfants.
	virtual void vider();
	/// Efface le noeud pass� en param�tre.
	virtual void effacer(const NoeudAbstrait* noeud);

	/// Cherche un noeud par le type (sur un noeud constant).
	virtual const NoeudAbstrait* chercher(const std::string& typeNoeud) const;
	/// Cherche un noeud par le type.
	virtual NoeudAbstrait* chercher(const std::string& typeNoeud);
	/// Cherche un noeud enfant selon l'indice (sur un noeud constant).
	virtual const NoeudAbstrait* chercher(unsigned int indice) const;
	/// Cherche un noeud enfant selon l'indice.
	virtual NoeudAbstrait* chercher(unsigned int indice);
	/// Ajoute un noeud enfant.
	virtual bool ajouter(std::shared_ptr<NoeudAbstrait> enfant);
	/// Obtient le nombre d'enfants du noeud.
	virtual unsigned int obtenirNombreEnfants() const;

	/// Changer la s�lection du noeud.
	virtual void inverserSelection();
	/// Efface les enfants s�lectionn�s.
	virtual void effacerSelection();
	/// S�lectionne tous les enfants de m�me que le noeud.
	virtual void selectionnerTout();
	/// D�s�lectionne tous les enfants de m�me que le noeud.
	virtual void deselectionnerTout();
	/// V�rifier si le noeud ou un de ses enfants est s�lectionn�.
	virtual bool selectionExiste() const;

	/// Change le mode d'affichage des polygones.
	virtual void changerModePolygones(bool estForce);
	/// Assigne le mode d'affichage des polygones.
	virtual void assignerModePolygones(GLenum modePolygones);
	/// Affiche le noeud.
	virtual void afficher(const int& index) const;
	/// Affiche le noeud de mani�re concr�te.
	virtual void afficherConcret() const;
	/// Anime le noeud.
	virtual void animer(float dt);

	/// Accepter un visiteur.
	virtual void accepterVisiteur(VisiteurAbstrait* visiteur) = 0;

	/// Retourne le mod�le
	virtual modele::Modele3D const* getModele();


	virtual bool obtenirEnCreation() { return enCreation_; };
	virtual void assignerEnCreation(bool enCreation) { enCreation_ = enCreation; };

	/// convertit un noeud en JSON
	void toJson(rapidjson::Writer<rapidjson::FileWriteStream>& writer);

	/// assigne les attributs d'un noeud � partir d'un JSON
	void fromJson(rapidjson::Value::ConstValueIterator noeudJSON);

	virtual void assignerCouleurs(int modele, int a, int r, int g, int b) {};

	virtual void assignerMode(int mode) {};

	virtual void assignerTeleporteur(NoeudAbstrait* teleporteur) {};

	virtual void setCouleurDefault(int piece,bool default) {};

protected:
	///Si l'objet est en train de se faire cr�er
	bool enCreation_		{ false };

	// Le type du noeud.
	EntityType	            type_;
	
	/// Nom du noeud.
	std::string				name_;

	// Id du noeud
	uint32_t	            id_;

	uint32_t				ownerId_{ 0 };

	glm::vec4				selectionColor_;

	/// Mode d'affichage des polygones.
	GLenum					modePolygones_{ GL_FILL };

	PhysicsComponent		physics_;

    /// La boite englobante du mod�le.
    utilitaire::BoiteEnglobante boiteEnglobanteModele_;

	/// Vrai si on doit afficher le noeud.
	bool					affiche_{ true };

	/// S�lection du noeud.
	bool					selectionne_{ false };

	/// Vrai si le noeud est s�lectionnable.
	bool					selectionnable_{ true };

	/// D�termine si l'objet peut �tre sauvegard� en XML.
	bool					enregistrable_{ true };

	/// D�termine si l'objet peut �tre dupliqu�
	bool				    estDuplicable_{ true };

	bool                    isErasable_{ true };
	/// Pointeur vers le parent.
	NoeudAbstrait* parent_{ nullptr };

	/// Mod�le 3D correspondant � ce noeud.
	modele::Modele3D const* modele_{ nullptr };

	/// Storage pour le dessin du mod�le
	opengl::VBO const*		vbo_{ nullptr };
};




////////////////////////////////////////////////////////////////////////
///
/// @fn inline shared_ptr<NoeudAbstrait> NoeudAbstrait::obtenirParent()
///
/// Cette fonction retourne le pointeur vers le parent de ce noeud.
///
/// @return Le pointeur vers le parent.
///
////////////////////////////////////////////////////////////////////////
inline NoeudAbstrait* NoeudAbstrait::obtenirParent()
{
	return parent_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline const shared_ptr<NoeudAbstrait> NoeudAbstrait::obtenirParent() const
///
/// Cette fonction retourne le pointeur constant vers le parent de ce noeud.
///
/// @return Le pointeur constant vers le parent.
///
////////////////////////////////////////////////////////////////////////
inline const NoeudAbstrait* NoeudAbstrait::obtenirParent() const
{
	return parent_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerParent( shared_ptr<NoeudAbstrait> parent )
///
/// Cette fonction assigne le parent du noeud afin qu'il soit possible
/// de remonter dans l'arbre.
///
/// @param[in] parent : Le parent du noeud.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerParent(NoeudAbstrait* parent)
{
	parent_ = parent;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline PhysicsComponent& NoeudAbstrait::getPhysicsComponent()
///
/// Cette fonction retourne une r�f�rence sur la composante physique.
///
/// @return Une r�f�rence sur la composante physique du noeud.
///
////////////////////////////////////////////////////////////////////////
inline PhysicsComponent& NoeudAbstrait::getPhysicsComponent()
{
	return physics_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline const utilitaire::BoiteEnglobante& NoeudAbstrait::obtenirBoiteEnglobanteModele() const
///
/// Cette fonction permet d'obtenir la boite englobante du modele.
///
/// @return La boite englobante du modele.
///
////////////////////////////////////////////////////////////////////////
inline const utilitaire::BoiteEnglobante& NoeudAbstrait::obtenirBoiteEnglobanteModele() const
{
    return boiteEnglobanteModele_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline const std::string& NoeudAbstrait::obtenirType() const
///
/// Cette fonction retourne une cha�ne repr�sentante le type du noeud.
///
/// @return Le type du noeud.
///
////////////////////////////////////////////////////////////////////////
inline const std::string& NoeudAbstrait::obtenirNom() const
{
	return name_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline const std::string& NoeudAbstrait::obtenirType() const
///
/// Cette fonction retourne une cha�ne repr�sentante le type du noeud.
///
/// @return Le type du noeud.
///
////////////////////////////////////////////////////////////////////////
inline EntityType NoeudAbstrait::getType() const
{
	return type_;
}

inline void NoeudAbstrait::setSelectionColor(const glm::vec4& color)
{
	selectionColor_ = color;
}

inline uint32_t NoeudAbstrait::getOwnerId() const
{
	return ownerId_;
}

inline void NoeudAbstrait::setOwnerId(uint32_t userId)
{
	ownerId_ = userId;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerAffiche( bool affiche )
///
/// Cette fonction permet d'assigner si le noeud se fait afficher ou
/// non lorsque l'arbre de rendu se fait afficher.  Elle permet donc
/// de temporairement suspendre ou activer l'affichage d'un noeud.
///
/// @param affiche : L'�tat affich� ou non.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerAffiche(bool affiche)
{
	affiche_ = affiche;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline bool NoeudAbstrait::estAffiche() const
///
/// Cette fonction retourne l'�tat que le noeud se fait afficher ou non.
///
/// @return L'�tat affich� ou non.
///
////////////////////////////////////////////////////////////////////////
inline bool NoeudAbstrait::estAffiche() const
{
	return affiche_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerSelection( bool selectionne )
///
/// Cette fonction permet d'assigner l'�tat d'�tre s�lectionn� ou non du noeud.
///
/// @param selectionne : L'�tat s�lectionn� ou non.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerSelection(bool selectionne)
{
	// Un objet non s�lectionnable n'est jamais s�lectionn�.
	selectionne_ = (selectionne && selectionnable_);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline bool NoeudAbstrait::estSelectionne() const
///
/// Cette fonction retourne l'�tat d'�tre s�lectionn� ou non du noeud.
///
/// @return L'�tat s�lectionn� ou non.
///
////////////////////////////////////////////////////////////////////////
inline bool NoeudAbstrait::estSelectionne() const
{
	// Un objet non s�lectionnable n'est jamais s�lectionn�.
	return (selectionne_ && selectionnable_);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerEstSelectionnable( bool selectionnable )
///
/// Cette fonction permet d'assigner l'�tat d'�tre s�lectionnable ou non du noeud.
///
/// @param selectionnable : L'�tat s�lectionnable ou non.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerEstSelectionnable(bool selectionnable)
{
	selectionnable_ = selectionnable;
	selectionne_ = selectionne_ && selectionnable_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline bool NoeudAbstrait::estSelectionnable() const
///
/// Cette fonction retourne l'�tat d'�tre s�lectionnable ou non du noeud.
///
/// @return L'�tat s�lectionnable ou non.
///
////////////////////////////////////////////////////////////////////////
inline bool NoeudAbstrait::estSelectionnable() const
{
	return selectionnable_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerEstEnregistrable( bool enregistrable )
///
/// Cette fonction permet d'assigner l'�tat d'�tre entregistrable ou non du noeud.
///
/// @param enregistrable : L'�tat enregistrable ou non.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerEstEnregistrable(bool enregistrable)
{
	enregistrable_ = enregistrable;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline bool NoeudAbstrait::estEnregistrable() const
///
/// Cette fonction retourne l'�tat d'�tre enregistrable en XML ou non du
/// noeud.
///
/// @return L'�tat enregistrable ou non.
///
////////////////////////////////////////////////////////////////////////
inline bool NoeudAbstrait::estEnregistrable() const
{
	return enregistrable_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline bool NoeudAbstrait::assignerEstDuplicable( bool estDuplicable)
///
/// Cette m�thode permet d'assigner l'�tat d'�tre duplicable ou non du noeud.
///
/// @return L'�tat enregistrable ou non.
///
////////////////////////////////////////////////////////////////////////
inline bool NoeudAbstrait::assignerEstDuplicable(bool estDuplicable)
{
	estDuplicable_ = estDuplicable;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline bool NoeudAbstrait::estDuplicable() const
///
/// Cette m�thode retourne si oui ou non le Noeud est duplicable.
///
/// @return L'�tat enregistrable ou non.
///
////////////////////////////////////////////////////////////////////////
inline bool NoeudAbstrait::estDuplicable() const
{
	return estDuplicable_;
}

inline bool NoeudAbstrait::isErasable() const
{
	return isErasable_;
}

inline void NoeudAbstrait::setIsErasable(bool isErasable)
{
	isErasable_ = isErasable;
}

////////////////////////////////////////////////////////////////////////
//
// @fn inline int NoeudAbstrait::getId() const
//
// Cette m�thode retourne l'identifiant du noeud.
//
// @return L'identifiant du noeud.
//
////////////////////////////////////////////////////////////////////////
inline uint32_t NoeudAbstrait::getId() const
{
	return id_;
}

////////////////////////////////////////////////////////////////////////
//
// @fn inline bool NoeudAbstrait::setId(int id) const
//
// Cette m�thode assigne l'identifiant d'un noeud
//
// @param[in] id : l'identifiant du noeud.
//
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::setId(uint32_t id)
{
	id_ = id;
}

#endif // __ARBRE_NOEUDS_NOEUDABSTRAIT_H__

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
