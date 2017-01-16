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
#include "RectangleEnglobant.h"

/// Déclarations avancées pour contenir un pointeur vers un modèle3D et son storage

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

///////////////////////////////////////////////////////////////////////////
/// @class NoeudAbstrait
/// @brief Classe de base du patron composite utilisée pour créer l'arbre
///        de rendu.
///
///        Cette classe abstraite comprend l'interface de base que doivent
///        implanter tous les noeuds pouvant être présent dans l'arbre de
///        rendu.
///
/// @author DGI-2990
/// @date 2007-01-24
///////////////////////////////////////////////////////////////////////////
class NoeudAbstrait 
{
public:
	/// Constructeur.
	NoeudAbstrait(const std::string& type = std::string{ "" });
	/// Destructeur.
	virtual ~NoeudAbstrait();

	/// Obtient le parent de ce noeud.
	inline NoeudAbstrait* obtenirParent();
	/// Obtient le parent de ce noeud (version constante).
	inline const NoeudAbstrait* obtenirParent() const;
	/// Assigne le parent de ce noeud.
	inline void assignerParent(NoeudAbstrait* parent);

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

	/// Obtient le quadrilatère englobant du noeud.
    inline const utilitaire::BoiteEnglobante& obtenirBoiteEnglobanteModele() const;

    virtual FormeEnglobanteAbstraite* obtenirFormeEnglobante();
    virtual const FormeEnglobanteAbstraite* obtenirFormeEnglobante() const;
    virtual void mettreAJourFormeEnglobante();

	/// Obtient le type du noeud.
	inline const std::string& obtenirType() const;

	/// Écrit l'état de l'affichage du du noeud.
	inline void assignerAffiche(bool affiche);
	/// Vérifie si le noeud se fait afficher.
	inline bool estAffiche() const;
	/// Écrit l'état de la sélection du noeud.
	inline void assignerSelection(bool selectionne);
	/// Vérifie si le noeud est sélectionné.
	inline bool estSelectionne() const;
	/// Écrit si le noeud peut être sélectionné ou non.
	inline void assignerEstSelectionnable(bool selectionnable);
	/// Vérifie si le noeud est sélectionnable.
	inline bool estSelectionnable() const;
	/// Écrit si le noeud peut être enregistré ou non.
	inline void assignerEstEnregistrable(bool enregistrable);
	/// Vérifie si le noeud est enregistrable.
	inline bool estEnregistrable() const;
	/// Écrit si le noeud peut être enregistré ou non.
	inline bool assignerEstDuplicable(bool estDuplicable);
	/// Vérifie si l'objet peut être dupliqué.
	inline bool estDuplicable() const;

	/// Assigne le modèle3D et la liste d'affichage du noeud courant
	void assignerObjetRendu(modele::Modele3D const* modele, opengl::VBO const* liste);

	// Interface d'un noeud

	/// Calcule la profondeur de l'arbre sous le noeud courant.
	virtual unsigned int calculerProfondeur() const;

	/// Vide le noeud de ses enfants.
	virtual void vider();
	/// Efface le noeud passé en paramètre.
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

	/// Changer la sélection du noeud.
	virtual void inverserSelection();
	/// Efface les enfants sélectionnés.
	virtual void effacerSelection();
	/// Sélectionne tous les enfants de même que le noeud.
	virtual void selectionnerTout();
	/// Désélectionne tous les enfants de même que le noeud.
	virtual void deselectionnerTout();
	/// Vérifier si le noeud ou un de ses enfants est sélectionné.
	virtual bool selectionExiste() const;

	/// Change le mode d'affichage des polygones.
	virtual void changerModePolygones(bool estForce);
	/// Assigne le mode d'affichage des polygones.
	virtual void assignerModePolygones(GLenum modePolygones);
	/// Affiche le noeud.
	virtual void afficher(const int& index) const;
	/// Affiche le noeud de manière concrète.
	virtual void afficherConcret() const;
	/// Anime le noeud.
	virtual void animer(float dt);

	/// Accepter un visiteur.
	virtual void accepterVisiteur(VisiteurAbstrait* visiteur) = 0;

	/// Retourne le modèle
	virtual modele::Modele3D const* getModele();


	virtual bool obtenirEnCreation() { return enCreation_; };
	virtual void assignerEnCreation(bool enCreation) { enCreation_ = enCreation; };

	/// convertit un noeud en JSON
	void toJson(rapidjson::Writer<rapidjson::FileWriteStream>& writer);

	/// assigne les attributs d'un noeud à partir d'un JSON
	void fromJson(rapidjson::Value::ConstValueIterator noeudJSON);

protected:
	///Si l'objet est en train de se faire créer
	bool enCreation_		{ false };

	/// Type du noeud.
	std::string				type_;

	/// Mode d'affichage des polygones.
	GLenum					modePolygones_{ GL_FILL };

	/// Position relative du noeud à son parent.
	glm::dvec3				positionRelative_{ 0.0, 0.0, 0.0 };

    /// Position courante du noeud dans l'espace virtuel.
    glm::dvec3              positionCourante_{ 0.0, 0.0, 0.0 };

	/// Angle de rotation sur le plan xy
	double					angleRotation_{ 0 };
		
	/// Facteur de dimension sur le plan xy
	double					facteurMiseAEchelle_{ 1 };

    /// La boite englobante du modèle.
    utilitaire::BoiteEnglobante boiteEnglobanteModele_;

	/// Vrai si on doit afficher le noeud.
	bool					affiche_{ true };

	/// Sélection du noeud.
	bool					selectionne_{ false };

	/// Vrai si le noeud est sélectionnable.
	bool					selectionnable_{ true };

	/// Détermine si l'objet peut être sauvegardé en XML.
	bool					enregistrable_{ true };

	/// Détermine si l'objet peut être dupliqué
	bool				    estDuplicable_{ true };
	/// Pointeur vers le parent.
	NoeudAbstrait* parent_{ nullptr };

	/// Modèle 3D correspondant à ce noeud.
	modele::Modele3D const* modele_{ nullptr };

	/// Storage pour le dessin du modèle
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
/// @fn inline const glm::dvec3& NoeudAbstrait::obtenirPositionRelative() const
///
/// Cette fonction retourne la position relative du noeud par rapport
/// à son parent.
///
/// @return La position relative.
///
////////////////////////////////////////////////////////////////////////
inline const glm::dvec3& NoeudAbstrait::obtenirPositionRelative() const
{
	return positionRelative_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerPositionRelative( const glm::dvec3& positionRelative )
///
/// Cette fonction permet d'assigner la position relative du noeud par
/// rapport à son parent.
///
/// @param positionRelative : La position relative.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerPositionRelative(
	const glm::dvec3& positionRelative
	)
{
	positionRelative_ = positionRelative;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline const glm::dvec3& NoeudAbstrait::obtenirPositionRelative() const
///
/// Cette fonction retourne la position courante du noeud dans l'espace virtuel.
///
/// @return La position relative.
///
////////////////////////////////////////////////////////////////////////
inline const glm::dvec3& NoeudAbstrait::obtenirPositionCourante() const
{
    return positionCourante_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerPositionCourante(const glm::dvec3& positionRelative)
///
/// Cette fonction permet d'assigner la position courante du noeud dans l'espace virtuel. 
///
/// @param positionRelative : La position courante.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerPositionCourante(
    const glm::dvec3& positionCourante)
{
    positionCourante_ = positionCourante;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerPositionRelative( const glm::dvec3& positionRelative )
///
/// Cette fonction permet d'obtenir l'angle de rotation affectant présentement ce noeud.
///
/// @return l'angle de rotation en degrees du noeud
///
////////////////////////////////////////////////////////////////////////
inline double NoeudAbstrait::obtenirAngleRotation() const
{
	return angleRotation_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerAngleRotation(const double& angleRotation)
///
/// Cette fonction permet d'assigner un angle de rotation en sens horaire au noeud par rapport à son centre.
///
/// @param angleRotation : Le nouvel angle de rotation de l'objet.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerAngleRotation(const double& angleRotation)
{
	angleRotation_ = angleRotation;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline double NoeudAbstrait::obtenirFacteurMiseAEchelle() const
///
/// Cette fonction permet d'obtenir l'échelle d'agrandissement ou de rapetissement du noeud.
///
/// @return L'échelle de l'objet. 1 étant l'échelle originale.
///
////////////////////////////////////////////////////////////////////////
inline double NoeudAbstrait::obtenirFacteurMiseAEchelle() const
{
	return facteurMiseAEchelle_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerFacteurMiseAEchelle(const double& facteurDimension)
///
/// Cette fonction permet d'assigner une nouvelle échelle d'agrandissement au Noeud.
///
/// @param[in] facteurDimension : Le facteur de redimentionnement de l'objet.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerFacteurMiseAEchelle(const double& facteurDimension)
{
	facteurMiseAEchelle_ = facteurDimension;
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
/// Cette fonction retourne une chaîne représentante le type du noeud.
///
/// @return Le type du noeud.
///
////////////////////////////////////////////////////////////////////////
inline const std::string& NoeudAbstrait::obtenirType() const
{
	return type_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerAffiche( bool affiche )
///
/// Cette fonction permet d'assigner si le noeud se fait afficher ou
/// non lorsque l'arbre de rendu se fait afficher.  Elle permet donc
/// de temporairement suspendre ou activer l'affichage d'un noeud.
///
/// @param affiche : L'état affiché ou non.
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
/// Cette fonction retourne l'état que le noeud se fait afficher ou non.
///
/// @return L'état affiché ou non.
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
/// Cette fonction permet d'assigner l'état d'être sélectionné ou non du noeud.
///
/// @param selectionne : L'état sélectionné ou non.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerSelection(bool selectionne)
{
	// Un objet non sélectionnable n'est jamais sélectionné.
	selectionne_ = (selectionne && selectionnable_);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline bool NoeudAbstrait::estSelectionne() const
///
/// Cette fonction retourne l'état d'être sélectionné ou non du noeud.
///
/// @return L'état sélectionné ou non.
///
////////////////////////////////////////////////////////////////////////
inline bool NoeudAbstrait::estSelectionne() const
{
	// Un objet non sélectionnable n'est jamais sélectionné.
	return (selectionne_ && selectionnable_);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerEstSelectionnable( bool selectionnable )
///
/// Cette fonction permet d'assigner l'état d'être sélectionnable ou non du noeud.
///
/// @param selectionnable : L'état sélectionnable ou non.
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
/// Cette fonction retourne l'état d'être sélectionnable ou non du noeud.
///
/// @return L'état sélectionnable ou non.
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
/// Cette fonction permet d'assigner l'état d'être entregistrable ou non du noeud.
///
/// @param enregistrable : L'état enregistrable ou non.
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
/// Cette fonction retourne l'état d'être enregistrable en XML ou non du
/// noeud.
///
/// @return L'état enregistrable ou non.
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
/// Cette méthode permet d'assigner l'état d'être duplicable ou non du noeud.
///
/// @return L'état enregistrable ou non.
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
/// Cette méthode retourne si oui ou non le Noeud est duplicable.
///
/// @return L'état enregistrable ou non.
///
////////////////////////////////////////////////////////////////////////
inline bool NoeudAbstrait::estDuplicable() const
{
	return estDuplicable_;
}

#endif // __ARBRE_NOEUDS_NOEUDABSTRAIT_H__

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
