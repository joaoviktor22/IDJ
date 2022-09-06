//
// Created by DELL on 02/09/2022.
//

#include <SDL_ttf.h>
#include "Component.h"
#include "Timer.h"

class Text : public Component{
public:
    enum TextStyle{
        SOLID,
        SHADED,
        BLENDED
    };
    Text(GameObject& associated, std::string fontFile, int fontSize,
         TextStyle style, std::string text, SDL_Color color, int blinkPeriod = 0);
    ~Text();
    void Update(float dt);
    void Render();
    bool Is(std::string type);
    void SetText(std::string text);
    void SetColor(SDL_Color color);
    void SetStyle(TextStyle style);
    static void SetFontFile(std::string fontFile);
    void SetFontSize(int fontSize);

private:
    void RemakeTexture();
    std::shared_ptr<TTF_Font> font;
    SDL_Texture* texture;
    std::string text;
    TextStyle style;
    std::string fontFile;
    int fontSize;
    SDL_Color color;
};
