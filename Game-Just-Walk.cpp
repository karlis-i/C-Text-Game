// Game-Just-Walk.cpp

#include <iostream>
#include <string>

int main()
{
    // allowed commands
    const std::string kCommandStart = "start"; // start the game from start/home screen
    const std::string kCommandStop = "stop"; // end the game and move to final screen
    const std::string kCommandQuit = "quit"; // stop the program
    const std::string kCommandHelp = "help"; // display help
    const std::string kCommandNorth = "go north"; // walking
    const std::string kCommandEast = "go east";
    const std::string kCommandSouth = "go south";
    const std::string kCommandWest = "go west";
    const std::string kCommandInventory = "inventory"; // reserved for later
    const std::string kCommandAgain = "play again"; // reserved for later

    // somehow come back here after user enters "again"

    // misc setup
    bool gameStarted = false;
    bool gameRunning = false;
    bool gameWon = false;
    bool gameFinished = false;
    int moveCount = -1;
    

    // home - info window and "enter start to begin"
    std::cout << "Welcome to Forest Walker!\n\n"
        << "this is a game\n"
        << "type \"" << kCommandStart << "\" to start playing!\n\n";

    // "enter start to play"
    while (!gameStarted) {
        std::string homeInput{};
        std::getline(std::cin, homeInput);

        if (homeInput == kCommandStart) {
            gameStarted = true;
        } else {
            std::cout << "Unrecognized command, please enter \"" << kCommandStart << "\" to play!\n";
        }
    }

    // game setup
    gameRunning = true;

    // game loop
    while (gameRunning) {

        moveCount++;

        // display room info
        std::cout << "You are {AT A LOCATION}\n";
        std::cout << "You see{ THINGS }\n";

        // display possible directions
        std::cout << "You can go{ TO DIRECTIONS }\n\n";

        std::cout << "Enter \"go north/east/south/west\" to move!\n";
        std::string gameInput{};
        std::getline(std::cin, gameInput);

        if (gameInput == kCommandNorth) {}
        else if (gameInput == kCommandEast) {}
        else if (gameInput == kCommandSouth) {}
        else if (gameInput == kCommandWest) {}
        else if (gameInput == kCommandHelp) {
            std::cout << "Help\n";
            std::cout << "- enter \"" << kCommandNorth << "\" to travel North\n";
            std::cout << "- enter \"" << kCommandEast << "\" to travel East\n";
            std::cout << "- enter \"" << kCommandSouth << "\" to travel South\n";
            std::cout << "- enter \"" << kCommandWest << "\" to travel West\n";
            std::cout << "- enter \"" << kCommandStop << "\" to stop playing";
        }
        else if (gameInput == kCommandStop) {
            // confirmation?

            std::cout << "Sorry to see you go!\n";
            std::cout << "Come back soon!\n";

            gameRunning = false;
        }
        else {
            std::cout << "Unrecognized command\n";
            std::cout << "Enter \"" << kCommandHelp << "\" to get help!\n";
        }
    }
    

    // end screen - enter "again" to play again, or "quit" to exit
    if (gameWon) {
        std::cout << "Congratulations!\n";
        std::cout << "You have won!\n";
    }
    else {
        std::cout << "Tough luck, You didn't win...\n";
    }

    std::cout << "You made " << moveCount << " moves\n\n";

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
