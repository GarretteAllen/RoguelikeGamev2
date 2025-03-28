#ifndef NODE_H
#define NODE_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <functional>
#include <vector>

enum class NodeType { Fight, Reward };

class Node {
public:
    Node(int x, int y, int size, const std::string& label, float opacity, SDL_Renderer* renderer, TTF_Font* font,
        std::function<void()> onClick, NodeType type = NodeType::Fight, SDL_Color color = { 255, 255, 255, 255 },
        std::vector<int> nextNodes = {});
    ~Node();
    void render() const;
    bool handleEvent(SDL_Event& e);
    void setRenderer(SDL_Renderer* renderer);
    void setFont(TTF_Font* font); // New method

    SDL_Rect rect;
    std::string label;
    float opacity;
    bool isCompleted;
    NodeType type;
    SDL_Color color;
    std::vector<int> nextNodes;

private:
    SDL_Renderer* renderer;
    TTF_Font* font;
    std::function<void()> onClick;
    SDL_Texture* labelTexture; // Removed mutable
    SDL_Rect labelRect; // Removed mutable
    bool needsTextureUpdate; // New flag to defer texture creation
    void createLabelTexture(); // Removed const
};

#endif