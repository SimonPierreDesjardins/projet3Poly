# Permettre d'inclure des fichiers d'entêtes des librairies externes sans spécifier le path complet
include_directories(
    ${CMAKE_SOURCE_DIR}/ext/asio-1.10.8/include
	${CMAKE_SOURCE_DIR}/ext/Eigen/include
    ${CMAKE_SOURCE_DIR}/src/app/networkUtils/include
	chat-management
	map-management
	map-management/map-rooms
	map-management/entities
	UserManagement
	message-dispatcher
	.
)

set(USER_MANAGEMENT_SRC
	UserManagement/User.h
	UserManagement/User.cpp
	UserManagement/UserAuthLobby.h
	UserManagement/UserAuthLobby.cpp
)
source_group("user-management" FILES ${USER_MANAGEMENT_SRC})

set(CHAT_MANAGEMENT_SRC
	chat-management/ChatManager.h
	chat-management/ChatManager.cpp
)
source_group("chat-management" FILES ${CHAT_MANAGEMENT_SRC})

set(ENTITIES_SRC
	map-management/entities/Entity.h
	map-management/entities/Entity.cpp
	map-management/entities/EntityTree.h
	map-management/entities/EntityTree.cpp
)
source_group("map-management\\entities" FILES ${ENTITIES_SRC})

set(MAP_ROOMS_SRC
	map-management/map-rooms/SimulationRoom.h
	map-management/map-rooms/SimulationRoom.cpp
	map-management/map-rooms/EditionRoom.h
	map-management/map-rooms/EditionRoom.cpp
	map-management/map-rooms/AbstractMapRoom.h
	map-management/map-rooms/AbstractMapRoom.cpp
)
source_group("map-management\\map-rooms" FILES ${MAP_ROOMS_SRC})

set(MAP_MANAGEMENT_SRC
	map-management/MapRoomManager.h
	map-management/MapRoomManager.cpp
)
source_group("map-management" FILES ${MAP_MANAGEMENT_SRC})

set(MESSAGE_DISPATCHER_SRC
	message-dispatcher/Observer.h
	message-dispatcher/Observer.cpp
	message-dispatcher/Observable.h
	message-dispatcher/Observable.cpp
)
source_group("message-dispatcher" FILES ${MESSAGE_DISPATCHER_SRC})

set(SERVER_SRC
	ServerStarter.cpp
	MultiUserSession.h
	MultiUserSession.cpp
	CMakeLists.txt
)
source_group("" FILES ${SERVER_SRC})

add_executable(Server
	${MESSAGE_DISPATCHER_SRC}
	${USER_MANAGEMENT_SRC}
	${CHAT_MANAGEMENT_SRC}
	${MAP_MANAGEMENT_SRC}
	${MAP_ROOMS_SRC}
	${ENTITIES_SRC}
	${SERVER_SRC}
)
target_link_libraries(Server PRIVATE networkUtils)

set_property(TARGET Server PROPERTY FOLDER "app/server")

target_compile_definitions(Server
	PRIVATE
    ASIO_STANDALONE
	_WIN32_WINNT=0x0501
    _WINSOCK_DEPRECATED_NO_WARNINGS
)