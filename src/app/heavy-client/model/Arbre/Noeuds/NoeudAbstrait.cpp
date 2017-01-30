////////////////////////////////////////////////
/// @file   NoeudAbstrait.cpp
/// @author DGI-2990
/// @date   2007-01-24
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////

#include "NoeudAbstrait.h"
#include "Utilitaire.h"
#include "rapidjson\filewritestream.h"
#include <iterator>
#include <iostream>
#include "FormeEnglobanteAbstraite.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait::NoeudAbstrait(const std::string& type)
///
/// Ne fait qu'initialiser les variables membres de la classe.
///
/// @param[in] type               : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait::NoeudAbstrait(
	const std::string& type //= std::string{ "" }
	) :
	type_( type )
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait::~NoeudAbstrait()
///
/// Destructeur vide d�clar� virtuel pour les classes d�riv�es.  La
/// lib�ration des afficheurs n'est pas la responsabilit� de cette
/// classe.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait::~NoeudAbstrait()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn FormeEnglobanteAbstraite* NoeudAbstrait::obtenirFormeEnglobante()
///
/// Cette fonction permet d'obtenir la forme englobante pour le noeud.
///
/// @return Pointeur sur une forme englobante abstraite(nullptr ici).
///
////////////////////////////////////////////////////////////////////////
FormeEnglobanteAbstraite* NoeudAbstrait::obtenirFormeEnglobante()
{
    return nullptr;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn const FormeEnglobanteAbstraite* NoeudAbstrait::obtenirFormeEnglobante() const
///
/// Cette fonction permet d'obtenir la forme englobante pour le noeud.
///
/// @return Pointeur const sur une forme englobante abstraite(nullptr ici).
///
////////////////////////////////////////////////////////////////////////
const FormeEnglobanteAbstraite* NoeudAbstrait::obtenirFormeEnglobante() const
{
    return nullptr;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::mettreAJourFormeEnglobante()
///
/// Cette fonction permet de mettre a jour la forme englobante du noeud
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::mettreAJourFormeEnglobante()
{
    
}

////////////////////////////////////////////////////////////////////////
///
/// @fn unsigned int NoeudAbstrait::calculerProfondeur() const
///
/// Cette fonction calcule la profondeur de l'arbre incluant le noeud
/// courant ainsi que tous ses enfants.
///
/// Cette fonction retourne toujours 1 pour un noeud sans enfant.
///
/// @return La profondeur de l'arbre sous ce noeud, donc toujours 1.
///
////////////////////////////////////////////////////////////////////////
unsigned int NoeudAbstrait::calculerProfondeur() const
{
	return 1;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::vider()
///
/// Cette fonction vide le noeud de tous ses enfants.
///
/// Cette fonction ne fait rien pour un noeud sans enfant, elle ne fait
/// donc rien dans cette implantation par d�faut de la classe de base.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::vider()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::effacer( const shared_ptr<NoeudAbstrait> noeud )
///
/// Cette fonction efface le noeud s'il fait partie des enfants de
/// ce noeud.
///
/// Cette fonction ne fait rien pour un noeud sans enfant, elle ne fait
/// donc rien dans cette implantation par d�faut de la classe de base.
///
/// @param[in] noeud : Le noeud � effacer.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::effacer(const NoeudAbstrait* noeud)
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn const shared_ptr<NoeudAbstrait> NoeudAbstrait::chercher( const std::string& typeNoeud ) const
///
/// Cette fonction cherche un noeud d'un type donn� parmi le noeud
/// lui-m�me et ses enfants.
///
/// Elle retourne donc le noeud lui-m�me si son type est celui pass� en
/// param�tre, ou 0 sinon.
///
/// @param[in] typeNoeud : Le type du noeud � trouver.
///
/// @return Le pointeur vers le noeud s'il est trouv�.
///
////////////////////////////////////////////////////////////////////////
const NoeudAbstrait* NoeudAbstrait::chercher(const std::string& typeNoeud) const
{
	if (typeNoeud == type_)
		return this;
	else
		return nullptr;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn shared_ptr<NoeudAbstrait> NoeudAbstrait::chercher( const std::string& typeNoeud )
///
/// Cette fonction cherche un noeud d'un type donn� parmi le noeud
/// lui-m�me et ses enfants.
///
/// Elle retourne donc le noeud lui-m�me si son type est celui pass� en
/// param�tre, ou 0 sinon.
///
/// @param[in] typeNoeud : Le type du noeud � trouver.
///
/// @return Le pointeur vers le noeud s'il est trouv�.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* NoeudAbstrait::chercher(const std::string& typeNoeud)
{
	if (typeNoeud == type_)
		return this;
	else
		return nullptr;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn const shared_ptr<NoeudAbstrait> NoeudAbstrait::chercher( unsigned int indice ) const
///
/// Cette fonction cherche le i-�me enfant d'un noeud.
///
/// Elle retourne toujours 0 pour la classe de base, car cette
/// derni�re ne poss�de pas d'enfant.
///
/// @param[in] indice : L'indice du noeud � trouver.
///
/// @return Le pointeur vers le noeud s'il est trouv�.
///
////////////////////////////////////////////////////////////////////////
const NoeudAbstrait* NoeudAbstrait::chercher(unsigned int indice) const
{
	return nullptr;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn shared_ptr<NoeudAbstrait> NoeudAbstrait::chercher( unsigned int indice )
///
/// Cette fonction cherche le i-�me enfant d'un noeud.
///
/// Elle retourne toujours 0 pour la classe de base, car cette
/// derni�re ne poss�de pas d'enfant.
///
/// @param[in] indice : L'indice du noeud � trouver.
///
/// @return Le pointeur vers le noeud s'il est trouv�.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* NoeudAbstrait::chercher(unsigned int indice)
{
	return nullptr;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudAbstrait::ajouter(shared_ptr<NoeudAbstrait> enfant)
///
/// Cette fonction ajoute un enfant � ce noeud.
///
/// Elle retourne toujours faux et ne fait rien, car ce type de noeud
/// abstrait ne peut pas avoir d'enfant.
///
/// @param[in] enfant: Le noeud � ajouter.
///
/// @return Vrai si l'ajout a bien �t� effectu�, faux autrement.
///
////////////////////////////////////////////////////////////////////////
bool NoeudAbstrait::ajouter(std::shared_ptr<NoeudAbstrait> enfant)
{
	return false;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn unsigned int NoeudAbstrait::obtenirNombreEnfants() const
///
/// Cette fonction retourne le nombre d'enfants de ce noeud.
///
/// Elle retourne toujours 0, car ce type de noeud abstrait ne peut pas
/// avoir d'enfant.
///
/// @return Le nombre d'enfants que poss�de le noeud.
///
////////////////////////////////////////////////////////////////////////
unsigned int NoeudAbstrait::obtenirNombreEnfants() const
{
	return 0;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::inverserSelection()
///
/// Cette fonction inverse l'�tat de s�lection de ce noeud.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::inverserSelection()
{
	selectionne_ = !selectionne_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::effacerSelection()
///
/// Cette fonction efface les noeuds qui sont s�lectionn�s parmi les
/// enfants de ce noeud.
///
/// Elle ne fait rien, car ce type de noeud abstrait ne peut pas avoir
/// d'enfant.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::effacerSelection()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::selectionnerTout()
///
/// Cette fonction s�lectionne le noeud et ses enfants.
///
/// Elle ne fait que s�lectionner le noeud pour cette classe, car ce
/// type de noeud abstrait ne peut pas avoir d'enfants.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::selectionnerTout()
{
	assignerSelection(true);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::deselectionnerTout()
///
/// Cette fonction d�s�lectionne le noeud et ses enfants.
///
/// Elle ne fait que d�s�lectionner le noeud pour cette classe, car ce
/// type de noeud abstrait ne peut pas avoir d'enfants.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::deselectionnerTout()
{
	selectionne_ = false;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudAbstrait::selectionExiste() const
///
/// Cette fonction v�rifie si le noeud ou un de ses enfants est
/// s�lectionn�.
///
/// Elle ne fait que regarder si le noeud est s�lectionn�, car ce type
/// de noeud abstrait ne peut pas avoir d'enfants.
///
/// @return Vrai s'il existe un noeud s�lectionn�, faux autrement.
///
////////////////////////////////////////////////////////////////////////
bool NoeudAbstrait::selectionExiste() const
{
	return selectionne_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::changerModePolygones( bool estForce )
///
/// Cette fonction change le mode de rendu des polygones du noeud s'il
/// est s�lectionn� ou si on le force.
///
/// @param[in] estForce: Vrai si on veut changer le mode m�me si le
///                      noeud n'est pas s�lectionn�.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::changerModePolygones(bool estForce)
{
	if ((estForce) || (estSelectionne())) {
		if (modePolygones_ == GL_FILL)
			modePolygones_ = GL_LINE;
		else if (modePolygones_ == GL_LINE)
			modePolygones_ = GL_POINT;
		else
			modePolygones_ = GL_FILL;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::assignerModePolygones( GLenum modePolygones )
///
/// Cette fonction assigne le mode de rendu des polygones du noeud.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::assignerModePolygones(GLenum modePolygones)
{
	// Le mode par d�faut si on passe une mauvaise valeur est GL_FILL
	if ((modePolygones != GL_FILL) &&
		(modePolygones != GL_LINE) &&
		(modePolygones != GL_POINT)) {
		modePolygones = GL_FILL;
	}

	modePolygones_ = modePolygones;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::afficher() const
///
/// Cette fonction affiche le noeud comme tel.
///
/// Elle consiste en une template method (dans le sens du patron de
/// conception, et non les template C++) qui effectue ce qui est
/// g�n�ralement � faire pour l'affichage, c'est-�-dire:
/// - Mise en pile de la matrice de transformation
/// - Translation du noeud pour qu'il soit � sa position relative
/// - Utilisation du mode d'affichage des polygones
/// - ...
/// - Restauration de l'�tat.
///
/// L'affichage comme tel est confi� � la fonction afficherConcret(),
/// appel�e par la fonction afficher().
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::afficher(const int& index) const
{
	if (affiche_) 
    {
        glPushName(index);
		glPushMatrix();
		glPushAttrib(GL_CURRENT_BIT | GL_POLYGON_BIT);
        
		// La translation de la position relative		
		glTranslated(
			positionRelative_[0], positionRelative_[1], positionRelative_[2]
			);

		// Assignation du mode d'affichage des polygones
		glPolygonMode(GL_FRONT_AND_BACK, modePolygones_);

		// Affichage concret
		afficherConcret();

		// Restauration
		glPopAttrib();
		glPopMatrix();
        glPopName();
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::afficherConcret() const
///
/// Cette fonction effectue le v�ritable rendu de l'objet.  Elle est
/// appel�e par la template method (dans le sens du patron de conception,
/// et non des template C++) afficher() de la classe de base.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::afficherConcret() const
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::animer( float dt )
///
/// Cette fonction effectue l'animation du noeud pour un certain
/// intervalle de temps.
///
/// Elle ne fait rien pour cette classe et vise � �tre surcharger par
/// les classes d�riv�es.
///
/// @param[in] dt : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::animer(float dt)
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn modele::Modele3D const* NoeudAbstrait::getModele()
///
/// Cette fonction retourne le modele 3D utilis� pour repr�sent� l'instance concr�te du Noeud.
///
/// Elle ne fait rien pour cette classe et vise � �tre surcharger par
/// les classes d�riv�es.
///
/// @return Le mod�le 3D du noeud, null si absent.
///
////////////////////////////////////////////////////////////////////////
modele::Modele3D const* NoeudAbstrait::getModele()
{
	return modele_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::toJson(rapidjson::Writer<rapidjson::FileWriteStream>& writer)
///
/// Cette fonction obtient les valeurs � sauvegarder pour le noeud en JSON
///
/// @param[in] writer : Le stream dans lequel le JSON est �crit
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::toJson(rapidjson::Writer<rapidjson::FileWriteStream>& writer)
{
	writer.Key("type");
	writer.String(obtenirType().c_str());
	writer.Key("posX");
	writer.Double(obtenirPositionRelative().x);
	writer.Key("posY");
	writer.Double(obtenirPositionRelative().y);
	writer.Key("posZ");
	writer.Double(obtenirPositionRelative().z);
	writer.Key("angleRotation");
	writer.Double(obtenirAngleRotation());
	writer.Key("facteurEchelle");
	writer.Double(obtenirFacteurMiseAEchelle());
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::fromJson(rapidjson::Value::ConstValueIterator noeudJSON)
///
/// Cette fonction assigne les valeurs n�cessaires au chargement du noeud � partir du fichier JSOn de sauvegarde.
///
/// @param[in] noeudJSON : Le noeud du fichier JSON contenant les informations de chargement.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::fromJson(rapidjson::Value::ConstValueIterator noeudJSON)
{
	rapidjson::Value::ConstMemberIterator itr = noeudJSON->MemberBegin() + 1;
	double x = itr->value.GetDouble();
	itr++;
	double y = itr->value.GetDouble();
	itr++;
	double z = itr->value.GetDouble();
	itr++;
	positionRelative_ = glm::dvec3(x,y,z);
	assignerAngleRotation(itr->value.GetDouble());
	itr++;
	assignerFacteurMiseAEchelle(itr->value.GetDouble());
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerObjetRendu(modele::Modele3D* modele, modele::opengl_storage::OpenGL_Liste* liste)
///
/// Cette fonction assigne l'objet de rendu au mod�le, c'est-�-dire son
/// mod�le 3D et sa liste d'affichage
///
/// @param modele : le mod�le 3D
/// @param liste : la liste d'affichage OpenGL
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::assignerObjetRendu(modele::Modele3D const* modele, opengl::VBO const* liste)
{
	modele_ = modele;
	vbo_ = liste;
	utilitaire::BoiteEnglobante boiteEnglobanteModele = utilitaire::calculerBoiteEnglobante(*modele_);
    boiteEnglobanteModele_ = utilitaire::calculerBoiteEnglobante(*modele_);

    // Effectuer une mise � jour.
    mettreAJourFormeEnglobante();
}

////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////
