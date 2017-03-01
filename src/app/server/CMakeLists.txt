# Permettre d'inclure des fichiers d'entêtes des librairies externes sans spécifier le path complet
include_directories(
    ${CMAKE_SOURCE_DIR}/ext/asio-1.10.8/include
    ${CMAKE_SOURCE_DIR}/src/app/networkUtils/include
)

add_executable(Server
	UserManagement/User.h
	UserManagement/User.cpp
	UserManagement/UserAuthLobby.h
	UserManagement/UserAuthLobby.cpp
	chat-management/ChatManager.h
	chat-management/ChatManager.cpp
	ServerStarter.cpp
)

target_link_libraries(Server PRIVATE networkUtils)

set_property(TARGET Server PROPERTY FOLDER "app/server")