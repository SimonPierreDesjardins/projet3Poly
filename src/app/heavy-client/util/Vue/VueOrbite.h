//////////////////////////////////////////////////////////////////////////////
/// @file VueOrbite.h
/// @author Fr�d�ric Gr�goire
/// @date 2016-03-29
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef __UTILITAIRE_VUEORBITE_H__
#define __UTILITAIRE_VUEORBITE_H__


#include "Vue.h"
#include "Camera.h"
#include "ProjectionPerspective.h"

namespace vue {


	////////////////////////////////////////////////////////////////////////
	/// @class VueOrbite
	/// @brief Classe concr�te de vue orbitale et permiere personne.
	///
	/// Cette classe implante le comportement attendu d'une vue avec une projection perspective.
	///
	/// @author Fr�d�ric Gr�goire
	/// @date 2016-03-29
	////////////////////////////////////////////////////////////////////////
	class VueOrbite : public Vue
	{
	public:
		// Constructeur.
		VueOrbite(Camera const& camera, ProjectionPerspective const& projection, bool estPremierePersonne);

		/// Obtention de la projection.
		virtual const ProjectionPerspective& obtenirProjection() const;
		/// Application de la projection.
		virtual void appliquerProjection() const;
		/// Application de la cam�ra.
		virtual void appliquerCamera() const;

		/// Modification de la clot�re.
		virtual void redimensionnerFenetre(const glm::ivec2& coinMin, const glm::ivec2& coinMax);

		/// Zoom in, c'est-�-dire un agrandissement.
		virtual void zoomerIn();
		/// Zoom out, c'est-�-dire un rapetissement.
		virtual void zoomerOut();
		/// Zoom in �lastique.
		virtual void zoomerInElastique(const glm::ivec2& coin1, const glm::ivec2& coin2);
		/// Zoom out �lastique.
		virtual void zoomerOutElastique(const glm::ivec2& coin1, const glm::ivec2& coin2);

		/// D�placement dans le plan XY par rapport � la vue.
		virtual void deplacerXY(double deplacementX, double deplacementY);
		/// D�placement dans le plan XY par rapport � la vue.
		virtual void deplacerXY(const glm::ivec2& deplacement);
		/// D�placement selon l'axe des Z par rapport � la vue.
		virtual void deplacerZ(double deplacement);
		/// Rotation selon les axes des X et des Y par rapport � la vue.
		virtual void rotaterXY(double rotationX, double rotationY);
		/// Rotation selon les axes des X et des Y par rapport � la vue.
		virtual void rotaterXY(const glm::ivec2& rotation);
		/// Rotation selon l'axe des Z par rapport � la vue.
		virtual void rotaterZ(double rotation);

		double verifierPhi(double changement);
		double verifierRho(double changement);

		glm::vec2 obtenirCentreVue();

	private:
		/// Projection utilis�e pour cette vue.
		ProjectionPerspective projection_;

		//Variable pour les coordonn�es sph�rique
		double theta;
		double phi;
		double rho;

	};
}; // Fin de l'espace de nom vue.


#endif // __UTILITAIRE_VUEORBITE_H__


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
