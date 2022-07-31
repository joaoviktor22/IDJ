cmake_minimum_required(VERSION 3.22)
project(JogoCLionv2)

set(CMAKE_CXX_STANDARD 11)

include_directories(C:/SDL2-2.0.22/include/SDL2)
link_directories(C:/SDL2-2.0.22/lib)
link_libraries(Mingw32 SDL2main SDL2_image SDL2_ttf SDL2_mixer SDL2)

add_executable(JogoCLionv2 main.cpp Game.h Game.cpp State.cpp State.h Sprite.cpp Sprite.h Log.cpp Log.h Music.cpp Music.h Component.cpp Component.h Face.cpp Face.h GameObject.cpp GameObject.h Rect.cpp Rect.h Sound.cpp Sound.h Vec2.cpp Vec2.h TileMap.cpp TileMap.h TileSet.cpp TileSet.h Resources.cpp Resources.h InputManager.cpp InputManager.h Camera.cpp Camera.h CameraFollower.cpp CameraFollower.h)
