cmake_minimum_required(VERSION 3.27)
project(sem)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp
        game/Game.cpp
        game/Game.h
        game/Paddle.cpp
        game/Paddle.h
        game/Ball.cpp
        game/Ball.h
        networking/NetworkManager.cpp
        networking/NetworkManager.h
        ui/Menu.cpp
        ui/Menu.h
        game/Entity.h
        enums/Direction.h
        game/Entity.cpp
        ui/Button.h
        enums/MenuState.h
        game/Multiplayer.cpp
        game/Multiplayer.h
        game/Singleplayer.cpp
        game/Singleplayer.h
        ui/ModeSelect.cpp
        ui/ModeSelect.h
        enums/MultiPlayerGameMode.h
        ui/IpDialog.cpp
        ui/IpDialog.h
        enums/YesNo.h
)

add_executable(sem ${SOURCE_FILES})

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR ./SFML/lib/cmake/SFML)

find_package(SFML COMPONENTS system window graphics network audio REQUIRED)

include_directories(./SFML/include)
target_link_libraries(sem sfml-system sfml-window sfml-graphics sfml-audio sfml-network)