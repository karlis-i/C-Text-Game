// Game-Just-Walk.cpp

#include <iostream>
#include <string>
#include <map>
#include <vector>

// class for each area/room
class Area
{
    public:
        // everybody knows what id, name and description are
        int id;
        std::string name;
        std::string description;

        // flags for the first and last areas
        bool isStart;
        bool isFinish;

        // pointers to connected areas
        int north, east, south, west;
        
        // empty constructor, apparently required
        Area() {
            this->id = NULL;
            this->name = "";
            this->description = "";

            this->isStart = false;
            this->isFinish = false;

            this->north = NULL;
            this->east = NULL;
            this->south = NULL;
            this->west = NULL;
        }

        // constructor
        Area(int id, std::string name, std::string description, bool isStart, bool isFinish, int north, int east, int south, int west) {
            this->id = id;
            this->name = name;
            this->description = description;

            this->isStart = isStart;
            this->isFinish = isFinish;

            this->north = north;
            this->east = east;
            this->south = south;
            this->west = west;
        }
};

// joins vector of strings
std::string join(std::vector<std::string> vector) {

    // start with empty string
    std::string result = "";

    // loop over vector
    for (int i = 0; i < vector.size(); i++) {
        
        if (i == 0) {
            // place first vector item at beginning of string
            result = vector[i];
        }
        else {
            // add subsequent vector items, separated by comma
            result = result + ", " + vector[i];
        }

    }

    // return string
    return result;
}

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


    // world - map of areas
    // @todo turn into JSON
    std::map<int, Area> world;
    world.emplace(1, Area(1, "meadow", "", true, false, NULL, 5, NULL, 3));
    world.emplace(2, Area(2, "the valley overlook", "", false, true, NULL, NULL, NULL, NULL));
    world.emplace(3, Area(3, "trail leading into forest", "", false, false, NULL, 4, 1, NULL));
    world.emplace(4, Area(4, "forest trail", "", false, false, 7, NULL, NULL, 3));
    world.emplace(5, Area(5, "sunny forest trail", "", false, false, 8, NULL, 1, NULL));
    world.emplace(6, Area(6, "dark forest trail", "", false, false, 9, 7, NULL, NULL));
    world.emplace(7, Area(7, "the great clearing", "", false, false, 10, 8, 4, 6));
    world.emplace(8, Area(8, "quiet forest trail", "", false, false, NULL, NULL, 5, 7));
    world.emplace(9, Area(9, "the witches lair", "", false, false, NULL, NULL, 6, NULL));
    world.emplace(10, Area(10, "wide forest trail", "", false, false, 2, 11, 7, NULL));
    world.emplace(11, Area(11, "winding forest trail", "", false, false, 2, NULL, NULL, 10));


    // somehow come back here after user enters "again"

    // game setup
    bool gameStarted = false;
    bool gameRunning = false;
    bool gameWon = false;
    bool gameFinished = false;
    int moveCount = 0;
    

    // home - info window and "enter start to begin"
    std::cout << "Welcome to Forest Walker!\n\n"
        << "this is a game\n\n"
        << "move around the world by entering commands like \"" << kCommandNorth << "\" and \"" << kCommandWest << "\"\n\n"
        << "at any time you can ask for help by entering the \"" << kCommandHelp << "\" command\n\n"
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
    int areaNumber = 1; // damn problem with 0, false and NULL...

    // game loop
    while (gameRunning) {

        // get area
        Area currentArea = world[areaNumber];

        // display area info
        std::cout << "You are at " << currentArea.name << "\n";
        //std::cout << "You see {THINGS}\n";
        // print area description, if present
        if (currentArea.description.size() > 0) {
            std::cout << currentArea.description << "\n";
        }


        // winning the game - reaching the finish area
        if (currentArea.isFinish) {
            gameWon = true;
            gameRunning = false;
            break;
        }


        // display possible directions
        std::vector <std::string> directions;
        if (currentArea.north != NULL) { directions.push_back("North"); }
        if (currentArea.east != NULL) { directions.push_back("East"); }
        if (currentArea.south != NULL) { directions.push_back("South"); }
        if (currentArea.west != NULL) { directions.push_back("West"); }
        std::cout << "You can go " << join(directions) << "\n\n";

        //std::cout << "Enter \"go north/east/south/west\" to move!\n";

        // wait until valid route found
        bool validRouteFound = false;

        while (!validRouteFound && gameRunning) {

            // read user input
            std::string gameInput{};
            std::getline(std::cin, gameInput);

            // process user input
            if (gameInput == kCommandNorth) {
                // if can go north
                if (currentArea.north != NULL) {
                    // set next area ID
                    areaNumber = currentArea.north;
                    // increase move count
                    moveCount++;
                    // repeat game loop
                    validRouteFound = true;
                }
                else {
                    std::cout << "Can't go North!\n";
                }
            }
            else if (gameInput == kCommandEast) {
                if (currentArea.east != NULL) {
                    areaNumber = currentArea.east;
                    moveCount++;
                    validRouteFound = true;
                }
                else {
                    std::cout << "Can't go East!\n";
                }
            }
            else if (gameInput == kCommandSouth) {
                if (currentArea.south != NULL) {
                    areaNumber = currentArea.south;
                    moveCount++;
                    validRouteFound = true;
                }
                else {
                    std::cout << "Can't go South!\n";
                }
            }
            else if (gameInput == kCommandWest) {
                if (currentArea.west != NULL) {
                    areaNumber = currentArea.west;
                    moveCount++;
                    validRouteFound = true;
                }
                else {
                    std::cout << "Can't go West!\n";
                }
            }
            else if (gameInput == kCommandHelp) {
                // help command
                //std::cout << "Help\n";
                std::cout << "- enter \"" << kCommandNorth << "\" to travel North\n";
                std::cout << "- enter \"" << kCommandEast << "\" to travel East\n";
                std::cout << "- enter \"" << kCommandSouth << "\" to travel South\n";
                std::cout << "- enter \"" << kCommandWest << "\" to travel West\n";
                std::cout << "- enter \"" << kCommandStop << "\" to stop playing\n";
                std::cout << "\n";
            }
            else if (gameInput == kCommandStop) {
                // stop game
                // confirmation?

                std::cout << "Sorry to see you go!\n";
                std::cout << "Come back soon!\n\n";

                gameRunning = false;
            }
            else {
                // invalid command
                std::cout << "Unrecognized command\n";
                std::cout << "Enter \"" << kCommandHelp << "\" to get help!\n\n";
            }

        }
    }
    //
    // END OF GAME LOOP
    //



    // end screen - enter "again" to play again, or "quit" to exit
    if (gameWon) {
        std::cout << "Congratulations!\n";
        std::cout << "You have won!\n";
    }
    else {
        std::cout << "Tough luck, You didn't win...\n";
    }

    std::cout << "You made " << moveCount << " moves\n\n";

    // quit or repeat
    std::cout << "Enter \"" << kCommandAgain << "\" to play again or \"" << kCommandQuit << "\" to end game!\n";
    std::string endInput{};
    std::getline(std::cin, endInput);

    if (endInput == kCommandAgain) {
        std::cout << "This feature isn't developed yet, press any key to end program!\n";
        return 0;
    }
    else if (endInput == kCommandQuit) {
        return 0;
    }
    else {
        // @todo repeat message
        std::cout << "Unrecognized command, press any key to end program!\n";
        return 0;
    }
}
