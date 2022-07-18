//
// Created by DELL on 13/07/2022.
//

#include "TileMap.h"
#include "Game.h"

TileMap::TileMap(GameObject &associated, string file, TileSet *tileSet) : Component(associated) {
    Load(file);
    SetTileSet(tileSet);
}

void TileMap::Load(string file) {
    FILE* fp = fopen(file.c_str(),"r");
    if (fp == NULL) {
        printf("Erro ao abrir arquivo %s\n", file.c_str());
        return;
    }
    if (fscanf(fp, "%d,%d,%d", &mapWidth, &mapHeight, &mapDepth) != 3) {
        printf("Erro nas dimensoes %s\n", file.c_str());
        return;
    }
    int scanned;
    fseek(fp, 1, SEEK_CUR);
    while(!feof(fp)){
        fscanf(fp, " %d,", &scanned);
        tileMatrix.push_back(scanned - 1);
    }
}

void TileMap::SetTileSet(TileSet *tileSet) {
    this->tileSet = tileSet;
}

int &TileMap::At(int x, int y, int z) {
    unsigned int index = unsigned (x) + unsigned(mapWidth * unsigned (y)) + unsigned (mapWidth * mapHeight * unsigned (z));
    return tileMatrix[index];
}

void TileMap::Render() {
    for (int z = 0; z < mapDepth; ++z) {
        RenderLayer(z, (int)associated.box.X, (int)associated.box.Y);
    }
}

void TileMap::Update(float dt) {

}

bool TileMap::Is(std::string type) {
    return type == "TileMap";
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY) {
    for (int i = 0; i < mapWidth; i++){
        for (int j = 0; j < mapHeight; ++j){
            int x = i * tileSet->GetTileWidth() - cameraX;
            int y = j * tileSet->GetTileHeight() - cameraY;

            Rect box = associated.box;

            if (x > -tileSet->GetTileWidth() && x < box.W && y > -tileSet->GetTileHeight() && y < box.H) {
                tileSet->RenderTile((unsigned)At(i, j, layer), x, y);
            }
        }
    }
}

int TileMap::GetWidth() {
    return this->mapWidth;
}

int TileMap::GetHeight() {
    return this->mapHeight;
}

int TileMap::GetDepth() {
    return this->mapDepth;
}
