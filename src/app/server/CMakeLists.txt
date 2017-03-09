# Permettre d'inclure des fichiers d'entêtes des librairies externes sans spécifier le path complet
include_directories(
    ${CMAKE_SOURCE_DIR}/ext/asio-1.10.8/include
    ${CMAKE_SOURCE_DIR}/ext/rapidJSON/include
    ${CMAKE_SOURCE_DIR}/src/app/networkUtils/include
)

set(USR_MGMT 
UserManagement/User.h
UserManagement/User.cpp
UserManagement/UserAuthLobby.h
UserManagement/UserAuthLobby.cpp
UserManagement/MultiUserSystem.h
UserManagement/MultiUserSystem.cpp
)
source_group(UserManagement FILES ${USR_MGMT})

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

set(MAP_SYST 
MapSystem/MapEditingSession.cpp
MapSystem/MapEditingSession.h
MapSystem/MapSystem.cpp
MapSystem/MapSystem.h
)
source_group(MapSystem FILES ${MAP_SYST})

set(CHT_SYST 
ChatSystem/ChatSystem.cpp
ChatSystem/ChatSystem.h
)
source_group(ChatSystem FILES ${CHT_SYST})

add_executable(Server
#Map system files
${MAP_SYST}

# User management files
${USR_MGMT}

# Database management files
${DB}

# Chat system files
${CHT_SYST}

ServerStarter.cpp
)

target_link_libraries(Server PRIVATE networkUtils)

set_property(TARGET Server PROPERTY FOLDER "app/server")