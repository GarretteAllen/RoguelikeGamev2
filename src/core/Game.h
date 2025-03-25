#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <memory>
#include <vector>
#include <string>
#include "../scenes/Scene.h"
#include "../ui/Card.h"
#include "../entities/Enemy.h"
#include "../systems/TextureManager.h"

class GameScene; // Forward declaration

class Game {
public:
    enum class GameState { MENU, DECK_SELECTION, GAME, BATTLE, REWARD };
    enum class DeckType { DAMAGE, BALANCED, ELEMENTAL, DEFENSE };
    enum class CardRarity { Common, Rare, Epic };

    Game();
    ~Game();
    bool init(const char* title, int width, int height);
    void handleEvents();
    void render();
    void clean();
    bool running() const { return isRunning; }

    void setState(GameState newState);
    void selectDeck(DeckType deck);
    void startBattle(const std::string& enemyName, int enemyHP, int enemyDamage);
    void endBattle(bool won);
    const std::vector<Card>& getSelectedDeck() const { return selectedDeck; }

    int currentNodeIndex;
    std::vector<bool> completedNodes;
    std::unique_ptr<GameScene> gameScene;

    int getWindowWidth() const { return WINDOW_WIDTH; }
    int getWindowHeight() const { return WINDOW_HEIGHT; }
    void addCardToDeck(const Card& card);
    std::vector<Card> getRewardCards(CardRarity maxRarity, int count = 1);

    void handleBattleCompletion(bool won);

    SDL_Renderer* renderer;
    TTF_Font* font;
    Scene* currentScene;
    GameState currentState;

    void setRewardScene(std::unique_ptr<Scene> newRewardScene) { rewardScene = std::move(newRewardScene); }

private:
    bool isRunning;
    bool isCleaned;
    SDL_Window* window;
    DeckType selectedDeckType;
    std::vector<Card> selectedDeck;

    static const int WINDOW_WIDTH = 800;
    static const int WINDOW_HEIGHT = 600;

    std::vector<Card> allCards;
    void initializeCards();

    // Helper unique_ptrs to manage ownership of other scenes
    std::unique_ptr<Scene> menuScene;
    std::unique_ptr<Scene> deckSelectionScene;
    std::unique_ptr<Scene> battleScene;
    std::unique_ptr<Scene> rewardScene;

    TextureManager textureManager;
};

#endif