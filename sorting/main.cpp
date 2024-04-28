#include "header/game.hpp"

int main() 
{
    Game game;
    game.initRectangle(100);

    while (game.running())
    {
        // Update game state if needed
        game.update();

        // Render the scene
        game.render();
    }

    // Wait for the final sorting thread to finish
    if (game.sortingThread.valid()) game.sortingThread.wait();

    return 0;

}
