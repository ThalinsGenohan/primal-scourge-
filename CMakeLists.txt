cmake_minimum_required(VERSION 3.0)
project(primal-scourge-tool)

set(BUILD_SHARED_LIBS FALSE)

option(SERVER "Build server? TRUE for Server, FALSE for client" OFF)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(MAIN_HEADERS
  src/CONSTANTS.h
  src/Channel.h
  src/Message.h
  src/ServerPacket.h
  src/ServerUser.h
  src/User.h
)
set(CLIENT_HEADERS
  src/ChatDisplay.h
  src/Client.h
  src/ClientWindow.h
  src/discord.h
  src/TextManager.h

  src/lang/lang.h
)
set(LANG_HEADERS
  src/lang/en_us.h
  src/lang/ja.h
)
list(APPEND CLIENT_HEADERS ${LANG_HEADERS})
set(SERVER_HEADERS
  src/Server.h
)

set(MAIN_SOURCE
  src/main.cpp
  src/Channel.cpp
  src/Message.cpp
  src/ServerPacket.cpp
  src/ServerUser.cpp
  src/User.cpp
)
set(CLIENT_SOURCE
  src/ChatDisplay.cpp
  src/Client.cpp
  src/ClientWindow.cpp
  src/discord.cpp
  src/TextManager.cpp
)
set(SERVER_SOURCE
  src/Server.cpp
)

if(WIN32)
  list(APPEND MAIN_SOURCE assets/resources.rc)
endif()

if(SERVER)
  list(APPEND MAIN_HEADERS ${SERVER_HEADERS})
  list(APPEND MAIN_SOURCE ${SERVER_SOURCE})
  set(DEFINES ${DEFINES} _SERVER)
else(SERVER)
  list(APPEND MAIN_HEADERS ${CLIENT_HEADERS})
  list(APPEND MAIN_SOURCE ${CLIENT_SOURCE})
  set(DEFINES ${DEFINES} _CLIENT)
endif(SERVER)

source_group("source" FILES ${MAIN_SOURCE} ${MAIN_HEADERS})

if(MSVC)
  list(APPEND DEFINES _CRT_SECURE_NO_WARNINGS NOMINMAX)
endif()

set(SFML_STATIC_LIBRARIES TRUE)
set(TGUI_STATIC_LIBRARIES TRUE)

find_package(SFML 2.5 COMPONENTS graphics window network system)
find_package(TGUI 0.8)
set(DISCORDRPC_ROOT "" CACHE PATH "DiscordRPC installation directory")

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")

add_executable(${PROJECT_NAME} ${MAIN_HEADERS} ${MAIN_SOURCE})
target_compile_definitions(${PROJECT_NAME} PRIVATE ${DEFINES})
target_include_directories(${PROJECT_NAME} PRIVATE src ${DISCORDRPC_ROOT}/include)
target_link_libraries(${PROJECT_NAME} tgui sfml-graphics sfml-network ${DISCORDRPC_ROOT}/lib/discord-rpc.lib)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/assets/fonts ${PROJECT_SOURCE_DIR}/assets/themes DESTINATION bin/assets)
