#include "draw.hpp"
#include "entity.hpp"
#include <vector>
#include <memory>

void prepareScene(void)
{
    //Sets the background to blue
    SDL_SetRenderDrawColor(app->renderer, 96, 128, 255, 255);
    //Clears the renderer
    SDL_RenderClear(app->renderer);
}

void presentScene(void)
{
    //Render the scene 
    SDL_RenderPresent(app->renderer);
}

void drawEntity(std::vector<std::unique_ptr<GameObject>>* entityList) {
    
    for (auto&& e : *entityList) {
        SDL_Rect fillRect = { e->getxPosition(), e->getyPosition(), e->getWidth(), e->getHeight() };
        SDL_SetRenderDrawColor(app->renderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderFillRect(app->renderer, &fillRect);
    }

}