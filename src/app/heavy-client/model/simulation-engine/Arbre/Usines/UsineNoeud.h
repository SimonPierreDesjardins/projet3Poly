///////////////////////////////////////////////////////////////////////////////
/// @file UsineNoeud.h
/// @author Martin Bisson
/// @date 2007-01-28
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_USINES_USINENOEUD_H__
#define __ARBRE_USINES_USINENOEUD_H__

#include <type_traits>
#include <string>
#include <memory>

#include "Modele3D.h"
#include "OpenGL_VBO.h"

//#include "FacadeModele.h"

class NoeudAbstrait;
class ArbreRendu;

///////////////////////////////////////////////////////////////////////////
/// @class UsineAbstraite
/// @brief Classe de base abstraite des usines qui seront utilis�es pour
///        cr�er les diff�rents noeuds de l'arbre de rendu.
///
/// @author Martin Bisson
/// @date 2001-01-28
///////////////////////////////////////////////////////////////////////////
class UsineAbstraite
{
public:
	virtual std::shared_ptr<NoeudAbstrait> creerNoeud() const = 0;
	virtual ~UsineAbstraite() = default;
protected:
	UsineAbstraite(std::string nom) : nom_(nom) {}

	/// Retourne le nom associ� � l'usine
	inline const std::string& obtenirNom() const;
	
	static uint32_t nextId_;

private:
	/// Le nom associ� � l'usine
	std::string nom_;
};

////////////////////////////////////////////////////////////////////////
///
/// @fn inline const std::string& UsineNoeud::obtenirNom() const
///
/// Cette fonction retourne une cha�ne repr�sentante le nom associ� �
/// l'usine.
///
/// @return Le nom associ� � l'usine.
///
////////////////////////////////////////////////////////////////////////
inline const std::string& UsineAbstraite::obtenirNom() const
{
	return nom_;
}

///////////////////////////////////////////////////////////////////////////
/// @class UsineNoeud
/// @brief Class template permettant de cr�er un type de noeud concret pour
///		   l'arbre de rendu.
///
/// @author Martin Paradis
/// @date 2015-06-24
///////////////////////////////////////////////////////////////////////////
template <typename Noeud>
class UsineNoeud : public UsineAbstraite
{
public:
   /// Destructeur vide d�clar� virtuel pour les classes d�riv�es.
   inline ~UsineNoeud() {
	   vbo_.liberer();
   }

   /// Fonction � surcharger pour la cr�ation d'un noeud.
   virtual std::shared_ptr<NoeudAbstrait> creerNoeud() const override;

   /// Constructeur qui prend le nom associ� � l'usine.
	UsineNoeud(const std::string& nomUsine, const std::string& nomModele, bool withGL) 
		: UsineAbstraite{ nomUsine }
	{
		withGL_ = withGL;
		if (withGL) {
			modele_.charger(nomModele);
			vbo_ = opengl::VBO{ &modele_ };
			vbo_.charger();
		}
	}

protected:
   /// Mod�le 3D correspondant � ce noeud.
   modele::Modele3D modele_;
   /// Storage pour le dessin du mod�le
   opengl::VBO vbo_;

   bool withGL_ = false;
};

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* UsineNoeud::creerNoeud() const
///
/// Cette fonction retourne un noeud nouvellement cr�� du type produit
/// par cette usine.
///
/// @return Le noeud nouvellement cr��.
///
////////////////////////////////////////////////////////////////////////
template <typename T>
std::shared_ptr<NoeudAbstrait> UsineNoeud<T>::creerNoeud() const
{
	static_assert(std::is_base_of<NoeudAbstrait, T>::value, R"(Une usine de noeuds ne peut creer que des types de noeuds d�rivant de NoeudAbstrait.)");
	std::shared_ptr<NoeudAbstrait> noeud = std::make_shared<T>(nextId_, obtenirNom());
	noeud->assignerObjetRendu(&modele_, &vbo_);
	return noeud;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* UsineNoeudRobot::creerNoeud() const
///
/// Cette fonction retourne un noeud nouvellement cr�� du type produit
/// par cette usine.
///
/// @return Le noeud nouvellement cr��.
///
////////////////////////////////////////////////////////////////////////
template <typename Noeud>
class UsineNoeudRobot: public UsineAbstraite{
public:
	UsineNoeudRobot(const std::string& nomUsine, const std::string& nomModele, ArbreRendu* arbre, bool withGL):UsineAbstraite(nomUsine) {
		withGL_ = withGL;
		if (withGL) {
			modele_.charger(nomModele);
			vbo_ = opengl::VBO{ &modele_ };
			vbo_.charger();
		}
		_arbre = arbre;
	}

	virtual std::shared_ptr<NoeudAbstrait> creerNoeud() const override {
		static_assert(std::is_base_of<NoeudAbstrait, Noeud>::value, R"(Une usine de noeuds ne peut creer que des types de noeuds d�rivant de NoeudAbstrait.)");
		std::shared_ptr<NoeudAbstrait> noeud = std::make_shared<Noeud>(nextId_, obtenirNom(), _arbre);
		if (withGL_) {
			noeud->assignerObjetRendu(&modele_, &vbo_);
		}
		return noeud;
	}

protected:
	ArbreRendu* _arbre;
	/// Mod�le 3D correspondant � ce noeud.
	modele::Modele3D modele_;
	/// Storage pour le dessin du mod�le
	opengl::VBO vbo_;
	/// This is a rendered factory
	bool withGL_ = false;
};

#endif // __ARBRE_USINES_USINENOEUD_H__