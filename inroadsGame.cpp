/*
  Inroads
*/

#include <string>

#include "inroadsGame.h"

using namespace std;

// TODO: implement your InroadsGame class constructor and methods here

InroadsGame::InroadsGame(Graph<std::string, bool, int> *graph)
{
  // set our variable called graph to the passed in graph
  this->map = graph;
  // create a copy of graph to run our graph algorithms on
  this->score_map = new AdjacencyListUndirectedGraph<std::string, bool, int>();
  // set score to 0
  this->score = 0;
  // initialize our variables in our struct to 0
  this->turn_data.slibrary = 0;
  this->turn_data.sstores = 0;
  this->turn_data.smedical = 0;
  this->turn_data.sscore = 0;

  // create a vector of the vertices in the graph
  vector<string> vertices = graph->getVertices();
  // get the size of the vertices
  int size = vertices.size();
  // loop through the vector
  for (int i = 0; i < size; i++)
  {
    // add our vertex to our graph
    this->score_map->insertVertex(vertices[i]);

    if (vertices[i][0] == 'R')
    {
      // add our vertex to our vector for residentials if condition is met
      this->residentials.push_back(vertices[i]);
    }
    else if (vertices[i][0] == 'S')
    {
      // add our vertex to our vector for stores if condition is met
      this->stores.push_back(vertices[i]);
    }
    else if (vertices[i][0] == 'L')
    {
      // add our vertex to our vector for libraries if condition is met
      this->libraries.push_back(vertices[i]);
    }
    else if (vertices[i][0] == 'M')
    {
      // add our vertex to our vector for medicals if condition is met
      this->medicals.push_back(vertices[i]);
    }
  }
}

InroadsGame::~InroadsGame()
{
  // delete our graph
  delete this->score_map;
  // set our pointer to passed in graph to nullptr
  this->map = nullptr;
}

void InroadsGame::paveRoad(std::pair<std::string, std::string> road)
{
  // call our method with the passed in road
  updateEdges(road);
  // call method to update score and gui
  calculateTurnSummary();
  return;
}

int InroadsGame::getScore()
{
  // return our variable for score
  return this->score;
}

TurnData InroadsGame::getTurnSummary()
{
  // return our struct containing info for division of score
  return this->turn_data;
}

void InroadsGame::calculateTurnSummary() {
  // declare our variables
  int rsize, ssize, msize, i, j, k, lscore, sscore, mscore;
  // declare our condition 
  bool reach_lib;
  // create a vector of strings
  vector<std::string> path;
  // create a pointer to a dictionary of strings to ints
  Dictionary<std::string, int>* mpath;

  // set our scores to 0
  lscore = 0;
  sscore = 0;
  mscore = 0;

  // get the size of our vectors holding the amount of residentials, stores, etc
  rsize = this->residentials.size();
  ssize = this->stores.size();
  msize = this->medicals.size();

  // set our condition to be true
  bool first = true;

  // loop through the size of our hospitals in our graph
  for (k = 0; k<msize; k++) {
    // set mpath to be the shortest path to our medical
    mpath = singleSourceShortestPath(this->medicals[k], this->score_map);

    // loop through the size of residentials
    for (i = 0; i<rsize; i++) {
      // if first is true we enter our condition
      if (first) {
        // check to see if our library can reach our current residential vertex
        reach_lib = reachableDFS(this->libraries[0], this->residentials[i], this->score_map);

        // if the condition is true we update our score by 15
        if (reach_lib) {
          lscore += 15;
        }
        // loop through the size of vectors of stores
        for (j = 0; j<ssize; j++) {
          // first try to get a path
          try {
            path = shortestLengthPathBFS(this->residentials[i], this->stores[j], this->score_map);

            // udpdate our store score if size is less then 3 including our 
            //start position
            if (path.size() <= 3) {
              sscore += 10;
            }
          }
          // catch error and do nothing
          catch (runtime_error) {}
        }

        // set our flag to be false after first run through
        if (i == (rsize-1)) {
          first = false;
        }
      }
      
      // check to see if medical path includes our residence
      if (mpath->contains(residentials[i])) {
        // update score
        mscore += (420)/(mpath->get(residentials[i]));
      }
    }
    // delete path
    delete mpath;
  }


  // set our score to be the sum of all scores
  this->score += lscore + sscore + mscore;

  // update the variables in our struct
  this->turn_data.slibrary = lscore;
  this->turn_data.sstores = sscore;
  this->turn_data.smedical = mscore;
  this->turn_data.sscore = lscore + sscore + mscore;

  return;
}

void InroadsGame::updateEdges(std::pair<std::string, std::string> road) {
  // declare an int for weight
  int weight;
  // set weight to be the weight of the edge
  weight = this->map->getEdge(road.first, road.second).getWeight();
  // remove the edge from the map
  this->map->removeEdge(road.first, road.second);
  // readd the edge with updated label to true
  this->map->insertEdge(road.first, road.second, true, weight);
  // add the edge to our copy graph
  this->score_map->insertEdge(road.first, road.second, true, weight);
  return;
}

bool InroadsGame::checkEdge(std::pair<std::string, std::string> road) {
  // use copy of our graph to check if the edge was already clicked on
  return this->score_map->containsEdge(road.first, road.second);
}