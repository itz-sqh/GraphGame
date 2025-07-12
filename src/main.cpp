#include <SFML/Graphics.hpp>
#include "FunctionPlotter/FunctionPlotter.h"
#include "ExpressionParser/Expression.h"
#include "ExpressionParser/ExpressionParser.h"
#include"Game.h"


int main()
{
    Game* game = new Game();
    game->run();
    delete game;
}
