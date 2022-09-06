//
// Created by DELL on 17/06/2022.
//

#include "Music.h"
#include "StageState.h"
#include "TileSet.h"
#include "TileMap.h"
#include "Camera.h"
#include "InputManager.h"
#include "CameraFollower.h"
#include "Alien.h"
#include "PenguinBody.h"
#include "Collider.h"
#include "Collision.h"
#include "Game.h"
#include "EndState.h"
#include "GameData.h"
#include "TitleState.h"

StageState::StageState() : State(){
    quitRequested = false;
    started = false;
    auto gameObject = new GameObject();

    // Adds Sprite
    auto sprite = new Sprite(*gameObject, R"(D:\IDJ\JogoClion\img\ocean.jpg)");
    //sprite->SetClip(0, 0, 1024, 600);
    gameObject->AddComponent(sprite);
    gameObject->AddComponent(new CameraFollower(*gameObject));
    objectArray.emplace_back(gameObject);

    auto MapGameObject(new GameObject);
    MapGameObject->box.W = 1024;
    MapGameObject->box.H = 600;

    tileSet = new TileSet(64, 64, R"(D:\IDJ\JogoClion\img\tileset.png)");
    TileMap *tileMap = new TileMap(*MapGameObject, R"(D:\IDJ\JogoClion\map\tileMap.txt)", tileSet);
    MapGameObject->AddComponent(tileMap);
    objectArray.emplace_back(MapGameObject);

    auto penguinBodyGO(new GameObject());
    penguinBodyGO->box.X = 704;
    penguinBodyGO->box.Y = 640;
    penguinBodyGO->AddComponent(new PenguinBody(*penguinBodyGO));
    Camera::Follow(penguinBodyGO);
    objectArray.emplace_back(penguinBodyGO);

    auto *alien = new GameObject();
    Alien *behaviour = new Alien(*alien, 6, 3);
    alien->AddComponent(behaviour);
    alien->box.X = 512;
    alien->box.Y = 300;
    objectArray.emplace_back(alien);

    auto *alien2 = new GameObject();
    Alien *behaviour2 = new Alien(*alien2, 4, 0);
    alien2->AddComponent(behaviour2);
    alien2->box.X = 1024;
    alien2->box.Y = 600;
    objectArray.emplace_back(alien2);

    auto *alien3 = new GameObject();
    Alien *behaviour3 = new Alien(*alien3, 2, 6);
    alien3->AddComponent(behaviour3);
    alien3->box.X = 256;
    alien3->box.Y = 900;
    objectArray.emplace_back(alien3);

    music = Music(R"(D:\IDJ\JogoClion\audio\stageState.ogg)");
    music.Play(-1);
}

void StageState::LoadAssets() {
}

//bool StageState::QuitRequested() const {
//    return quitRequested;
//}

void StageState::Update(float dt) {

    Camera::Update(dt);
    auto& manager = InputManager::GetInstance();
    quitRequested = manager.QuitRequested();
    if (InputManager::GetInstance().KeyPress(SDLK_ESCAPE)){
        TitleState* title = new TitleState();
        Game::GetInstance().Push(title);
        popRequested = true;
    }
    if (Alien::alienCount == 0){
        GameData::playerVictory = true;
        EndState *end = new EndState();
        Game::GetInstance().Push(end);
        popRequested = true;
    }
    if (PenguinBody::player == nullptr){
        GameData::playerVictory = false;
        EndState* end = new EndState();
        Game::GetInstance().Push(end);
        popRequested = true;
    }

    UpdateArray(dt);

    for (int i = objectArray.size() - 1 ; i >= 0; i--) {
        if (objectArray[i] -> IsDead()) {
            objectArray.erase(objectArray.begin() + i);
        }
    }

    for (int i = 0; i < objectArray.size(); i++) {
        for(int j = i+1; j < objectArray.size(); j++){
            auto &objA = objectArray[i];
            auto &objB = objectArray[j];

            Collider *colliderA = (Collider*) objA->GetComponent("Collider");
            Collider *colliderB = (Collider*) objB->GetComponent("Collider");
            if(colliderA && colliderB){
                auto boxA = colliderA->box;
                auto boxB = colliderB->box;

                auto angleOfA = (float)(objA->angleDeg);
                auto angleOfB = (float)(objB->angleDeg);

                if (Collision::IsColliding(boxA, boxB, angleOfA, angleOfB)) {
                    objA->NotifyCollision(*objB);
                    objB->NotifyCollision(*objA);
                }
            }
        }
    }
}

void StageState::Render() {
    //bg.Render(0, 0);
    RenderArray();
}

StageState::~StageState() {
    objectArray.clear();
}

//void StageState::Input() {
//    //SDL_Event event;
//    //int mouseX, mouseY;
//
//    // Obtenha as coordenadas do mouse
//    //SDL_GetMouseState(&mouseX, &mouseY);
//
//    // SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
//   // while (SDL_PollEvent(&event)) {
//
//        // Se o evento for quit, setar a flag para terminação
//        //if(event.type == SDL_QUIT) {
//        //    quitRequested = true;
//       // }
//
//        // Se o evento for clique...
//        //if(event.type == SDL_MOUSEBUTTONDOWN) {
//
//            // Percorrer de trás pra frente pra sempre clicar no objeto mais de cima
//            //for(int i = objectArray.size() - 1; i >= 0; --i) {
//                // Obtem o ponteiro e casta pra Face.
//                //auto* go = (GameObject*) objectArray[i].get();
//                // Nota: Desencapsular o ponteiro é algo que devemos evitar ao máximo.
//                // O propósito do unique_ptr é manter apenas uma cópia daquele ponteiro,
//                // ao usar get(), violamos esse princípio e estamos menos seguros.
//                // Esse código, assim como a classe Face, é provisório. Futuramente, para
//                // chamar funções de GameObjects, use objectArray[i]->função() direto.
//
//                //if(go->box.IsInside( {(float)mouseX, (float)mouseY} ) ) {
//                  //  Face* face = (Face*)go->GetComponent( "Face" );
//                  //  if ( nullptr != face ) {
//                  //      // Aplica dano
//                  //      face->Damage(std::rand() % 10 + 10);
//                 //       // Sai do loop (só queremos acertar um)
//                //        break;
//              //      }
//            //    }
//           // }
//
//        //}
//        //if( event.type == SDL_KEYDOWN ) {
//            // Se a tecla for ESC, setar a flag de quit
//            //if( event.key.keysym.sym == SDLK_ESCAPE ) {
//              //  quitRequested = true;
//            //}
//                // Se não, crie um objeto
//            //else {
//               // Vec2 objPos = Vec2( 200, 0 );
//               // objPos.Rotate( -PI + PI*(rand() % 1001)/500.0 );
//               // objPos = objPos + Vec2( mouseX, mouseY );
//               // AddObject((int)objPos.X, (int)objPos.Y);
//           // }
//        //}
//    //}
//}

void StageState::Start() {
    LoadAssets();
    StartArray();
}

void StageState::Pause() {

}

void StageState::Resume() {

}

//std::weak_ptr<GameObject> StageState::AddObject(GameObject* go) {
//    std::shared_ptr<GameObject> gameObject(go);
//    objectArray.push_back(gameObject);
//    if(started){
//        gameObject->Start();
//    }
//    return std::weak_ptr<GameObject>(gameObject);
//}
//
//std::weak_ptr<GameObject> StageState::GetObjectPtr(GameObject *go) {
//    for (auto &i : objectArray) {
//        if(i.get() == go){
//            return std::weak_ptr<GameObject>(i);
//        }
//    }
//    return std::weak_ptr<GameObject>();
//}
