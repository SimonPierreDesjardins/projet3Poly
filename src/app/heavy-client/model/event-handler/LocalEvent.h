///////////////////////////////////////////////////////////////////////////
// @file LocalEvent.h
// @author Olivier St-Amour
// @date 2017-03-07
// @version 1.0
//
// @{
///////////////////////////////////////////////////////////////////////////
#ifndef LOCAL_EVENT_H
#define LOCAL_EVENT_H

#include <string>

#include "glm/glm.hpp"

#include "Serializer.h"

///////////////////////////////////////////////////////////////////////////
/// @class AffichageTexte
/// @brief Classe qui permet de faire l'affichage OpenGL.
///
///        Cette classe permet de faire l'affichage du chronomètre ainsi 
///        que le nom du profil courant.   
///	       
/// 
/// @author Olivier St-Amour
/// @date 2016-03-29
///////////////////////////////////////////////////////////////////////////
class LocalEvent
{
public:
    LocalEvent() = default;
    ~LocalEvent() = default;

	inline const std::string& getMessage() const;

	void buildUserJoinedRoomMessage(uint32_t roomId);

	void buildEntitySelectedMessage(uint32_t entityId);
	void buildUpdateRelativePositionMessage(int entityId, const glm::vec3& position);
	void buildUpdateAbsolutePositionMessage(int entityId, const glm::vec3& position);
	void buildUpdateScaleMessage(int entityId, const glm::vec3& resize);
	void buildUpdateRotationMessage(int entityId, const glm::vec3& rotation);

	void buildEntityCreatedMessage(uint32_t entityId, uint8_t type, uint32_t parentId, const glm::vec3& position);
	void buildEntityDeletedMessage(uint32_t entityId);

private:
	std::string message_;

	client_network::Serializer serializer_;
};

inline const std::string& LocalEvent::getMessage() const
{
	return message_;
}

#endif // LOCAL_EVENT_H
