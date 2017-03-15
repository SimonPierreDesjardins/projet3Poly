



# Permettre d'inclure des fichiers d'entêtes des librairies externes sans spécifier le path complet
include_directories(
    ${CMAKE_SOURCE_DIR}/ext/boost
    ${CMAKE_SOURCE_DIR}/ext/mongo-cxx-3-1-1/include
    ${CMAKE_SOURCE_DIR}/ext/mongo-c-driver/include
    ${CMAKE_SOURCE_DIR}/ext/asio-1.10.8/include
	${CMAKE_SOURCE_DIR}/ext/Eigen/include
	${CMAKE_SOURCE_DIR}/ext/glm/include
    ${CMAKE_SOURCE_DIR}/ext/rapidJSON/include
    ${CMAKE_SOURCE_DIR}/src/app/networkUtils/include
	chat-management
	MapSystem
	MapSystem/map-rooms
	MapSystem/entities
	UserManagement
	message-dispatcher
	.
)

# Trouve les librairies
find_library(libbsoncxx_LIB 
libbsoncxx
${CMAKE_SOURCE_DIR}/ext/mongo-cxx-3-1-1/lib)

find_library(bsoncxx_LIB 
bsoncxx
${CMAKE_SOURCE_DIR}/ext/mongo-cxx-3-1-1/lib)

find_library(libmongocxx_LIB 
libmongocxx
${CMAKE_SOURCE_DIR}/ext/mongo-cxx-3-1-1/lib)

find_library(mongocxx_LIB 
mongocxx
${CMAKE_SOURCE_DIR}/ext/mongo-cxx-3-1-1/lib)

find_library(mongoc_LIB 
mongoc-1.0
${CMAKE_SOURCE_DIR}/ext/mongo-c-driver/lib)

find_library(mongoc_static_LIB
mongoc-static-1.0
${CMAKE_SOURCE_DIR}/ext/mongo-c-driver/lib)

find_library(bson_LIB 
bson-1.0
${CMAKE_SOURCE_DIR}/ext/mongo-c-driver/lib)

find_library(bson_static_LIB
bson-static-1.0
${CMAKE_SOURCE_DIR}/ext/mongo-c-driver/lib)

set(MONGO_LIBS
${bsoncxx_LIB}
${libbsoncxx_LIB}
${libmongocxx_LIB}
${mongocxx_LIB}
${bson_LIB}
${bson_static_LIB}
${mongoc_LIB}
${mongoc_static_LIB}
)


set(USER_MANAGEMENT_SRC
	UserManagement/User.h
	UserManagement/User.cpp
	UserManagement/UserAuthLobby.h
	UserManagement/UserAuthLobby.cpp
	UserManagement/MultiUserSystem.h
	UserManagement/MultiUserSystem.cpp
)
source_group("UserManagement" FILES ${USER_MANAGEMENT_SRC})

set(ENTITIES_SRC
	MapSystem/entities/Entity.h
	MapSystem/entities/Entity.cpp
	MapSystem/entities/EntityTree.h
	MapSystem/entities/EntityTree.cpp
)
source_group("MapSystem\\entities" FILES ${ENTITIES_SRC})

set(MAP_ROOMS_SRC
	MapSystem/map-rooms/SimulationRoom.h
	MapSystem/map-rooms/SimulationRoom.cpp
	MapSystem/map-rooms/EditionRoom.h
	MapSystem/map-rooms/EditionRoom.cpp
	MapSystem/map-rooms/AbstractMapRoom.h
	MapSystem/map-rooms/AbstractMapRoom.cpp
)
source_group("MapSystem\\MapRooms" FILES ${MAP_ROOMS_SRC})

set(MAP_SYST 
	MapSystem/MapSystem.cpp 
	MapSystem/MapSystem.h
)
source_group(MapSystem FILES ${MAP_SYST})

set(MESSAGE_DISPATCHER_SRC
	message-dispatcher/Observer.h
	message-dispatcher/Observer.cpp
	message-dispatcher/Observable.h
	message-dispatcher/Observable.cpp
)
source_group("message-dispatcher" FILES ${MESSAGE_DISPATCHER_SRC})

set(DB 
	Database/Database.h
	Database/Database.cpp
	Database/UserDatabase.h
	Database/UserDatabase.cpp
	Database/MapDatabase.h
	Database/MapDatabase.cpp
	Database/BaseDatalist.h
	Database/BaseDatalist.cpp
	Database/IdGenerator.h
	Database/IdGenerator.cpp
)
source_group(Database FILES ${DB})


set(CHT_SYST 
	ChatSystem/ChatSystem.cpp
	ChatSystem/ChatSystem.h
)
source_group(ChatSystem FILES ${CHT_SYST})

set(SERVER_SRC
	ServerStarter.cpp
	CMakeLists.txt
)
source_group("" FILES ${SERVER_SRC})

add_executable(Server
	${DB}
	${CHT_SYST}
	${MESSAGE_DISPATCHER_SRC}
	${USER_MANAGEMENT_SRC}
	${MAP_ROOMS_SRC}
	${MAP_SYST}
	${ENTITIES_SRC}
	${SERVER_SRC}
)

target_link_libraries(Server 
PRIVATE networkUtils
${MONGO_LIBS}
)


set_property(TARGET Server PROPERTY FOLDER "app/server")

target_compile_definitions(Server
	PRIVATE
    ASIO_STANDALONE
	_WIN32_WINNT=0x0501
    _WINSOCK_DEPRECATED_NO_WARNINGS
	MONGOCXX_STATIC
	BSONCXX_STATIC
)