////////////////////////////////////////////////////////////////////////////////////
/// @file VueOrbite.cpp
/// @author Frédéric Grégoire
/// @date 2016-03-29
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
////////////////////////////////////////////////////////////////////////////////////

#include "Utilitaire.h"
#include "VueOrbite.h"

namespace vue {

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn VueOrbite::VueOrbite(const Camera& camera, int xMinCloture, int xMaxCloture, int yMinCloture, int yMaxCloture, double zAvant, double zArriere, double zoomInMax, double zoomOutMax, double incrementZoom, double xMinFenetre, double xMaxFenetre, double yMinFenetre, double yMaxFenetre)
	///
	/// Constructeur d'une vue orthogonale.  Ne fait que créer les objets
	/// Projection et Camera correspondant.
	///
	/// @param[in] camera        : Caméra à utiliser au départ pour cette vue.
	/// @param[in] xMinCloture   : coordonnée minimale en @a x de la clôture.
	/// @param[in] xMaxCloture   : coordonnée maximale en @a x de la clôture.
	/// @param[in] yMinCloture   : coordonnée minimale en @a y de la clôture.
	/// @param[in] yMaxCloture   : coordonnée maximale en @a y de la clôture.
	/// @param[in] zAvant        : distance du plan avant (en @a z).
	/// @param[in] zArriere      : distance du plan arrière (en @a z).
	/// @param[in] zoomInMax     : facteur de zoom in maximal.
	/// @param[in] zoomOutMax    : facteur de zoom out maximal.
	/// @param[in] incrementZoom : distance du plan arrière (en @a z).
	/// @param[in] xMinFenetre   : coordonnée minimale en @a x de la fenêtre
	///                            virtuelle.
	/// @param[in] xMaxFenetre   : coordonnée maximale en @a x de la fenêtre
	///                            virtuelle.
	/// @param[in] yMinFenetre   : coordonnée minimale en @a y de la fenêtre
	///                            virtuelle.
	/// @param[in] yMaxFenetre   : coordonnée maximale en @a y de la fenêtre
	///                            virtuelle.
	/// 
	/// @return Aucune (constructeur).
	///
	////////////////////////////////////////////////////////////////////////
	VueOrbite::VueOrbite(Camera const& camera, ProjectionPerspective const& projection, bool estPremierePersonne) :
		Vue{ camera },
		projection_{ projection }
	{
		estPremierePersonne_ = estPremierePersonne;
		if (!estPremierePersonne_){
			theta = 90;
			phi = 0;
			rho = 170;
		}	
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn const ProjectionOrtho& VueOrbite::obtenirProjection() const
	///
	/// Retourne la projection perspective associée à cette vue.
	///
	/// @return La projection perspective associée à cette vue.
	///
	////////////////////////////////////////////////////////////////////////
	const ProjectionPerspective& VueOrbite::obtenirProjection() const
	{
		return projection_;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VueOrbite::appliquerProjection() const
	///
	/// Applique la matrice de projection correspondant à cette vue.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VueOrbite::appliquerProjection() const
	{
		projection_.mettreAJourProjection();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VueOrbite::appliquerCamera() const
	///
	/// Applique la matrice correspondant à cette vue selon la position de
	/// la caméra (eventuellement un gluLookAt()).
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VueOrbite::appliquerCamera() const
	{
		camera_.positionner();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VueOrbite::redimensionnerFenetre( const glm::ivec2& coinMin, const glm::ivec2& coinMax )
	///
	/// Permet d'ajuster les coordonnées de la fenêtre virtuelle en fonction
	/// d'un redimensionnement de la fenêtre.
	///
	/// @param[in]  coinMin : Coin contenant les coordonnées minimales de la
	///                       nouvelle clôture.
	/// @param[in]  coinMax : Coin contenant les coordonnées maximales de la
	///                       nouvelle clôture.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VueOrbite::redimensionnerFenetre(const glm::ivec2& coinMin,
		const glm::ivec2& coinMax)
	{
		projection_.redimensionnerFenetre(coinMin, coinMax);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VueOrbite::zoomerIn()
	///
	/// Permet de faire un zoom in selon l'incrément de zoom.
	/// 
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VueOrbite::zoomerIn()
	{
		rho -= 1;

		camera_.assignerPosition(glm::dvec3(
			rho*sin(utilitaire::DEG_TO_RAD(phi))*cos(utilitaire::DEG_TO_RAD(theta)),
			rho*sin(utilitaire::DEG_TO_RAD(phi))*sin(utilitaire::DEG_TO_RAD(theta)),
			rho*cos(utilitaire::DEG_TO_RAD(phi)))
			);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VueOrbite::zoomerOut()
	///
	/// Permet de faire un zoom out selon l'incrément de zoom.
	/// 
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VueOrbite::zoomerOut()
	{
		rho += 1;

		camera_.assignerPosition(glm::dvec3(
			rho*sin(utilitaire::DEG_TO_RAD(phi))*cos(utilitaire::DEG_TO_RAD(theta)),
			rho*sin(utilitaire::DEG_TO_RAD(phi))*sin(utilitaire::DEG_TO_RAD(theta)),
			rho*cos(utilitaire::DEG_TO_RAD(phi)))
			);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VueOrbite::zoomerInElastique(const glm::ivec2& coin1, const glm::ivec2& coin2)
	///
	/// Permet de faire un zoom in élastique.
	/// 
	/// @param[in]  coin1 : Coin contenant les coordonnées du premier coin du
	///                     rectangle.
	/// @param[in]  coin2 : Coin contenant les coordonnées du second coin du
	///                     rectangle.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VueOrbite::zoomerInElastique(const glm::ivec2& coin1, const glm::ivec2& coin2)
	{
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VueOrbite::zoomerOutElastique(const glm::ivec2& coin1, const glm::ivec2& coin2)
	///
	/// Permet de faire un zoom out élastique.
	/// 
	/// @param[in]  coin1 : Coin contenant les coordonnées du premier coin du
	///                     rectangle.
	/// @param[in]  coin2 : Coin contenant les coordonnées du second coin du
	///                     rectangle.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VueOrbite::zoomerOutElastique(const glm::ivec2& coin1, const glm::ivec2& coin2)
	{
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VueOrbite::deplacerXY(double deplacementX, double deplacementY)
	///
	/// @param[in]  deplacementX : Déplacement en pourcentage de la largeur.
	/// @param[in]  deplacementY : Déplacement en pourcentage de la hauteur.
	///
	/// Permet de faire un "pan" d'un certain pourcentage.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VueOrbite::deplacerXY(double deplacementX, double deplacementY)
	{
		theta -= deplacementX*0.1;
		verifierPhi(-deplacementY*0.1);
		glm::dvec3 position{ cos(utilitaire::DEG_TO_RAD(theta)), sin(utilitaire::DEG_TO_RAD(theta)), 0 };
		camera_.assignerDirectionHaut(position);


		camera_.assignerPosition(glm::dvec3(
			rho*sin(utilitaire::DEG_TO_RAD(phi))*cos(utilitaire::DEG_TO_RAD(theta)),
			rho*sin(utilitaire::DEG_TO_RAD(phi))*sin(utilitaire::DEG_TO_RAD(theta)),
			rho*cos(utilitaire::DEG_TO_RAD(phi)))
			);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VueOrbite::deplacerXY(const glm::ivec2& deplacement)
	///
	/// Permet de faire un "pan" équivalent à la distance du déplacement
	/// spécifié en coordonnées de clôture.
	///
	/// @param[in]  deplacement : Déplacement en coordonnées de clôture
	///                           (pixels).
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VueOrbite::deplacerXY(const glm::ivec2& deplacement)
	{
		theta -= deplacement[0];
		verifierPhi(-deplacement[1]);

		glm::dvec3 position{ cos(utilitaire::DEG_TO_RAD(theta)), sin(utilitaire::DEG_TO_RAD(theta)), 0 };
		camera_.assignerDirectionHaut(position);


		camera_.assignerPosition(glm::dvec3(
			rho*sin(utilitaire::DEG_TO_RAD(phi))*cos(utilitaire::DEG_TO_RAD(theta)),
			rho*sin(utilitaire::DEG_TO_RAD(phi))*sin(utilitaire::DEG_TO_RAD(theta)),
			rho*cos(utilitaire::DEG_TO_RAD(phi)))
			);
	}

	double VueOrbite::verifierPhi(double changement){
		phi += changement;
		if (phi > 0)
			phi = 0;
		else if (phi < -89.9)
			phi = -89.9;
		return phi;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VueOrbite::deplacerZ(double deplacement)
	///
	/// Ne fait rien, car se déplacer dans l'axe de la profondeur n'a pas
	/// vraiment de signification avec une vue orthogonale.
	///
	/// @param[in]  deplacement : Déplacement selon l'axe Z.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VueOrbite::deplacerZ(double deplacement)
	{
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VueOrbite::rotaterXY(double rotationX, double rotationY)
	///
	/// Permet de faire une rotation de la caméra autour du point vers
	/// lequel elle regarde en modifiant l'angle de rotation et l'angle
	/// d'élévation.
	///
	/// Une rotation de 100% correspondant à 360 degrés en X (angle de
	/// rotation) ou 180 degrés en Y (angle d'élévation).
	///
	/// @param[in]  rotationX : Rotation en pourcentage de la largeur.
	/// @param[in]  rotationY : Rotation en pourcentage de la hauteur.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VueOrbite::rotaterXY(double rotationX, double rotationY)
	{
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VueOrbite::rotaterXY(const glm::ivec2& rotation)
	///
	/// Permet de faire une rotation de la caméra autour du point vers
	/// lequel elle regarde en modifiant l'angle de rotation et l'angle
	/// d'élévation.
	///
	/// Un déplacement de la taille de la fenêtre correspond à 100%.
	///
	/// @param[in]  rotation : Rotation en coordonnées de clotûre (pixels).
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VueOrbite::rotaterXY(const glm::ivec2& rotation)
	{
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VueOrbite::rotaterZ(double rotation)
	///
	/// Ne fait rien, car tourner autour de l'axe de la profondeur
	/// correspondrait à un rouli et n'est pas souhaitable pour cette vue.
	///
	/// @param[in]  rotation : Rotation selon l'axe Z.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VueOrbite::rotaterZ(double rotation)
	{
	}

}; // Fin du namespace vue.


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
