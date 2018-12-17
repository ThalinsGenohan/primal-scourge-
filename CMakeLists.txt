cmake_minimum_required(VERSION 3.0)
project(simple-chat-app VERSION 1.0)

set(BUILD_SHARED_LIBS FALSE)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

option(SERVER_MODE "TRUE if building server, FALSE if building client" OFF)
option(DEBUG_MODE "Turns on Debug mode, letting the console remain open." OFF)
option(STATIC_LIBS "Are SFML and TGUI built statically?" OFF)

set(HEADER_FILES
  src/Channel.h
  src/ChatDisplay.h
  src/Client.h
  src/ClientWindow.h
  src/CONSTANTS.h
  src/discord.h
  src/Message.h
  src/Server.h
  src/ServerPacket.h
  src/ServerUser.h
  src/TextManager.h
  src/User.h
)
set(LANG_HEADERS
  src/lang/lang.h
  src/lang/en_us.h
  src/lang/es.h
  src/lang/ja.h
)
list(APPEND HEADER_FILES ${LANG_HEADERS})

set(SOURCE_FILES
  src/main.cpp
  src/Channel.cpp
  src/ChatDisplay.cpp
  src/Client.cpp
  src/ClientWindow.cpp
  src/discord.cpp
  src/Message.cpp
  src/Server.cpp
  src/ServerPacket.cpp
  src/ServerUser.cpp
  src/TextManager.cpp
  src/User.cpp
)

if(WIN32)
  list(APPEND SOURCE_FILES assets/resources.rc)
endif()

source_group("source" FILES ${SOURCE_FILES} ${HEADER_FILES})

if(MSVC)
  list(APPEND DEFINES _CRT_SECURE_NO_WARNINGS NOMINMAX)
endif()

if(DEBUG_MODE)
  list(APPEND DEFINES _DEBUG)
else()
  list(APPEND DEFINES NDEBUG)
endif()

if (STATIC_LIBS)
  set(SFML_STATIC_LIBRARIES TRUE)
  set(TGUI_STATIC_LIBRARIES TRUE)
endif()

find_package(SFML 2.5 COMPONENTS graphics window network system)
find_package(TGUI 0.8)
set(DISCORDRPC_ROOT "" CACHE PATH "DiscordRPC installation directory")

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")

add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})
target_compile_definitions(${PROJECT_NAME} PRIVATE ${DEFINES})
target_include_directories(${PROJECT_NAME} PRIVATE src ${DISCORDRPC_ROOT}/include)
target_link_libraries(${PROJECT_NAME} tgui sfml-graphics sfml-network ${DISCORDRPC_ROOT}/lib/discord-rpc.lib)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/assets/fonts ${PROJECT_SOURCE_DIR}/assets/themes DESTINATION bin/assets)
