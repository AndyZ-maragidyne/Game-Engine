#include "DrawComponent.hpp"
#include "GameObject.hpp"


DrawComponent::DrawComponent(GameObject* parent)
    : Component(parent), red(0x00), green(0x00), blue(0x00), alpha(0xFF) {}

DrawComponent::DrawComponent(GameObject* parent, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
    : Component(parent), red(r), green(g), blue(b), alpha(a) {}

DrawComponent::DrawComponent(GameObject* parent, Uint8 r, Uint8 g, Uint8 b)
    : Component(parent), red(r), green(g), blue(b), alpha(0xFF) {}


void DrawComponent::update() {
    
        SDL_Rect fillRect = { parent->getxPosition(), parent->getyPosition(), parent->getWidth(), parent->getHeight() };
        SDL_SetRenderDrawColor(app->renderer, red, green, blue, alpha);
        SDL_RenderFillRect(app->renderer, &fillRect);
    
}

json DrawComponent::toJson() {
    return {
        {"type", "Draw"},
        {"red", red},
        {"green", green},
        {"blue", blue},
        {"alpha", alpha}
    };
}