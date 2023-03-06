/*
  Inroads
*/

#pragma once
#include "adjacencyListUndirectedGraph.h"
#include "graphAlgorithms.h"

struct TurnData {
      int slibrary;
      int sstores;
      int smedical;
      int sscore;
    };

/**
 * An instance of this class represents a single game of Inroads.  An object of
 * type InroadsGame does not represent the user interface, but does represent
 * the idea of a game of Inroads, including the state of the board and all of
 * the information pertaining to the player.  It also includes the logic for
 * making moves in the game and enforces the game's rules.
 */
class InroadsGame {
  public:
    // TODO: write your InroadsGame constructor and method declarations here
     /**
     * Creates a new Inroads game to interact with. 
     * @param Graph The graph object which holds data
     *              to interact with our methods.
     */
    InroadsGame(Graph<std::string, bool, int>* graph);

     /**
     * Destroys the InroadsGame object.
     */
    ~InroadsGame();

     /**
     * Calls other functions in order to properly maintain rules of the game
     * @param road A pair of strings to create the edge between
     */
    void paveRoad(std::pair<std::string, std::string> road);

     /**
     * Returns the score of the current turn.
     */
    int getScore();
     /**
     * Returns an array a of size 4 containing info about the division of 
     * points for the current turn.
     */

    TurnData getTurnSummary();
    /**
    * Returns true if the edge already exists in our graph
    */
    bool checkEdge(std::pair<std::string, std::string> road);

  private:
    // TODO: write your InroadsGame fields here
    TurnData turn_data;

    Graph<std::string, bool, int>* map;
    Graph<std::string, bool, int>* score_map;
    int score;

    vector<std::string> residentials;
    vector<std::string> libraries;
    vector<std::string> stores;
    vector<std::string> medicals;

     /**
     * Calculates and updates the array a so each index properly holds what
     * is responsible for the different points that add up to the final score.
     */
    void calculateTurnSummary();

    /**
     * Sets the label of the edge between the two strings to be True
     * and creates the edge in the score graph 
     * @param road A pair of strings to create the edge between
     */
    void updateEdges(std::pair<std::string, std::string> road);

    // You can safely ignore the following code.  This eliminates some default
    // class routines, preventing you from using them accidentally.
    // Specifically, we are disabling the use of the copy constructor and the
    // copy assignment operator.  You can read more here:
    //   http://www.cplusplus.com/articles/y8hv0pDG/
  private:
    InroadsGame(const InroadsGame& other) = delete;
    InroadsGame& operator=(const InroadsGame& other) = delete;
};
