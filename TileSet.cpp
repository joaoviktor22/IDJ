//
// Created by DELL on 13/07/2022.
//

#include "TileSet.h"

TileSet::TileSet(int tileWidth, int tileHeight, string file) : tileSet(*new Sprite(*(new GameObject()),file)), tileWidth(tileWidth), tileHeight(tileHeight) {
    tileSet.Open(file);
    if(tileSet.IsOpen()){
        rows = tileSet.GetHeight() / tileHeight;
        columns = tileSet.GetWidth() / tileWidth;
    }
}

void TileSet::RenderTile(unsigned int index, float x, float y) {
    unsigned int numberOfTiles = columns*rows;

    if (index >= numberOfTiles) {
        return;
    }

    int tileColumn = index%columns;
    int tileRow = index / columns;

    int positionX = tileColumn*tileWidth;
    int positionY = tileRow*tileHeight;

    tileSet.SetClip(positionX, positionY, tileWidth, tileHeight);
    tileSet.Render(x, y);
}

int TileSet::GetTileWidth() const {
    return tileWidth;
}

int TileSet::GetTileHeight() const {
    return tileHeight;
}
