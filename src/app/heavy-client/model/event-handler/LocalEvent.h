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
	void buildEntityMovedRelativeMessage(int entityId, const glm::vec3& position);
	void buildEntityMovedAbsoluteMessage(int entityId, const glm::vec3& position);
	void buildEntityResizedMessage(int entityId, const glm::vec3& resize);
	void buildEntityRotatedMessage(int entityId, const glm::vec3& rotation);

	void buildEntityCreatedMessage(uint32_t entityId, uint8_t type, uint32_t parentId, const glm::vec3& position);
	void buildEntityDeletedMessage(uint32_t entityId);

private:
	std::string message_;

	void serialize(std::string& message, const glm::vec3& data);
	void serialize(uint32_t data, std::string& message);
	void serialize(uint8_t data, std::string& message);
};

inline const std::string& LocalEvent::getMessage() const
{
	return message_;
}

#endif // LOCAL_EVENT_H
