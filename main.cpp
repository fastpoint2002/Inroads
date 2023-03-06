/*
  Inroads
*/

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

#include "inroadsGUI.h"
#include "ioUtils.h"
#include "inroadsGame.h"

using namespace std;

int main(int argc, char** argv) {
    // Check command line arguments and give up if necessary.
    if (argc != 2) {
        cerr << "Expected one argument: name of map file." << endl;
        return 1;
    }

    // Initialize randomizer.  This should happen before any random numbers are
    // selected.
    srand(time(nullptr));

    // Get command-line argument.
    string mapFilename = string(argv[1]);

    // Read the Inroads map file.
    pair<Graph<string, bool, int>*, Dictionary<string, pair<int, int>>*>
        mapFileContents;
    try {
        mapFileContents = readInroadsMap(mapFilename);
    } catch (exception e) {
        cout << "Could not read Inroads map file " << mapFilename << ": "
             << e.what() << endl;
    }
    // The map file contained the graph representing the map.  It also contained
    // the vertex positions (so we know where each vertex goes on the map).
    Graph<string, bool, int>* graph = mapFileContents.first;
    Dictionary<string, pair<int, int>>* vertexPositions =
        mapFileContents.second;

    // Create the GUI object here.  This is statically allocated, so the GUI
    // will disappear the moment your program leaves the main function.
    // The GUI object should only be used by main, and not by any other function
    // or object; do NOT change the type of this variable.
    InroadsGUI gui(vertexPositions, mapFilename);

    // Tell the GUI about the graph we have.
    gui.updateInroadsMap(graph);
    gui.updateScoreText("Score: 0");
    gui.updateTurnText("Turn: 1");

    // TODO: Write code that runs the game.  You'll want to write most of your
    // game logic into the InroadsGame class and then use an object of that type
    // here to control the game and relay what it says to the GUI.  This
    // assignment is more open-ended than the previous assignments.
    
    // create a pointer of game type
    InroadsGame* game = new InroadsGame(graph);
    // declare a pair of strings 
    pair<string, string> road;
    bool wait_close = false;

    // for loop to run for the correct amount of turns
    for (int turn = 1; turn<=20; turn++) {
        // set exit to false
        bool exit = false;
        // set valid click to true
        bool get_valid_click = true;
        // loop until the user provides a valid click
        while (get_valid_click) {
            // get the users next move and store in our pair
            road = gui.getNextMove();
            // check to see if the user exited the window of our gui
            if (road.first == "") {
                // set exit to true
                exit = true;
                // break loop
                get_valid_click = false;
            }
            // get a click from the user and check to see if the user has
            // already clicked on it
            get_valid_click = game->checkEdge(road);
        }
        // break out of for loop
        if (exit) {
            break;
        }

        // call the pave road function
        game->paveRoad(road);
        // update the graph to include the new edge
        gui.updateInroadsMap(graph); 
        
        // get a pointer to an array of the division of points
        TurnData turn_info = game->getTurnSummary();
        // create a string
        string turn_mes = "Your score this turn: \n";
        // concatenate the string for the makeup of points
        turn_mes += "\t +" + to_string(turn_info.slibrary) + " from the library\n";
        turn_mes += "\t +" + to_string(turn_info.sstores) + " from stores\n";
        turn_mes += "\t +" + to_string(turn_info.smedical) + 
        " from medical access\n";
        turn_mes += "Total points from this turn: " + 
        to_string(turn_info.sscore);

        // create a string to print the score
        string pscore = "Score: " + to_string(game->getScore());
        // call method to display the makeup of points in the GUI
        gui.updateScoreText(pscore);
        // call method to display the makeup of points
        gui.updateMessage(turn_mes);

        // check to see that we still have turns to play
        if (turn != 20) {
            // update turn
            string pturn = "Turn: " + to_string(turn);
            // display the updated turn on the GUI
            gui.updateTurnText(pturn);
        }
        // let the user know the game ended because they ran out of turns
        else {
            // display the message on the GUI
            gui.updateTurnText("Game Over");
            // set our variable to true
            wait_close = true;
        }   
        
    }

    // wait for user to exit through the window instead of closing automatically
    while (wait_close) {
        road = gui.getNextMove();
        if (road.first == "") {
            wait_close = false;
        }
    }
    
    // delete game object
    delete game;


    // TODO: Delete the following code.  It's just here at the start of the
    // assignment to make sure that you can see what the GUI looks like.  If we
    // didn't do something here (like wait for the user to press enter on the
    // console), then the main function would stop and the GUI would instantly
    // vanish.
    //string deleteThisVariable;
    //getline(cin, deleteThisVariable);

    // Finally, clean up and exit successfully.
    delete graph;
    delete vertexPositions;
    return 0;
}
