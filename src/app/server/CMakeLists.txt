# Permettre d'inclure des fichiers d'entêtes des librairies externes sans spécifier le path complet
include_directories(
    ${CMAKE_SOURCE_DIR}/ext/asio-1.10.8/include
    ${CMAKE_SOURCE_DIR}/ext/rapidJSON/include
    ${CMAKE_SOURCE_DIR}/src/app/networkUtils/include
)

add_executable(Server

# User management files
UserManagement/User.h
UserManagement/User.cpp
UserManagement/UserAuthLobby.h
UserManagement/UserAuthLobby.cpp
UserManagement/MultiUserSystem.h
UserManagement/MultiUserSystem.cpp

# Database management files
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

ServerStarter.cpp
)

target_link_libraries(Server PRIVATE networkUtils)

set_property(TARGET Server PROPERTY FOLDER "app/server")