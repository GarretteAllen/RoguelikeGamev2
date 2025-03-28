#ifndef CARD_H
#define CARD_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <iostream>
#include <memory>
#include "../systems/TextureManager.h"

enum class CardEffectType { None, Armor, Heal, MultiStrike, Weaken, Poison, Thorns, Wet, Lightning, Ice };

struct CardEffect {
    CardEffectType type;
    int value;
    int count;

    CardEffect(CardEffectType t = CardEffectType::None, int v = 0, int c = 0) : type(t), value(v), count(c) {}
};

class Card {
public:
    Card(int x, int y, const std::string& name, int damage, int energyCost, SDL_Renderer* renderer, TTF_Font* font, CardEffect effect = CardEffect());

    // Copy constructor
    Card(const Card& other) = default;

    // Copy assignment operator
    Card& operator=(const Card& other) = default;

    // Destructor
    ~Card() = default;

    void render(SDL_Renderer* renderer, int playerEnergy, int windowWidth, int windowHeight);
    void handleEvent(SDL_Event& e);
    void loadImage(const std::string& path, SDL_Renderer* renderer, TextureManager& textureManager);
    void resetPosition();

    void setPosition(int x, int y) {
        rect.x = x;
        rect.y = y;
        originalRect.x = x;
        originalRect.y = y;
    }

    void setRenderer(SDL_Renderer* renderer);
    void setFont(TTF_Font* font);

    SDL_Rect& getRect() { return rect; }
    SDL_Rect& getOriginalRect() {
        std::cout << "Modifying originalRect for card: " << name << "\n";
        return originalRect;
    }
    std::string getName() const { return name; }
    int getDamage() const { return damage; }
    int getEnergyCost() const { return energyCost; }
    CardEffect getEffect() const { return effect; }

    bool isDragging;
    bool getIsMagnified() const { return isMagnified; }

private:
    SDL_Rect rect;
    SDL_Rect originalRect;
    std::string name;
    int damage;
    int energyCost;
    CardEffect effect;
    SDL_Renderer* renderer;
    TTF_Font* font;
    std::shared_ptr<SDL_Texture> textTexture;
    std::shared_ptr<SDL_Texture> imageTexture;
    bool isHovered;
    Uint32 hoverStartTime;
    static const Uint32 HOVER_DELAY = 2000;
    bool isMagnified;
    bool needsTextTextureUpdate; // Flag to defer text texture creation

    void createTextTexture(); // New method to create the text texture
};

#endif