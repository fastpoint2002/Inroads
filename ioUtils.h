/*
  Inroads
*/

#pragma once

#include <fstream>
#include <iostream>
#include <stdexcept>

#include "adts/dictionary.h"
#include "adts/edge.h"
#include "adts/graph.h"

using std::string;

/**
 * Reads the contents of an Inroads map file.
 * @param filename The file to read.
 * @return A pair between two pointers.  The first is a pointer to the graph
 *         describing the map.  The second is a pointer to a dictionary mapping
 *         vertex names to GUI positions for visualization purposes.  The caller
 *         becomes the owner of both of these objects.
 * @throws std::exception If an I/O error occurs.
 */
std::pair<Graph<string, bool, int>*,
          Dictionary<std::string, std::pair<int,int>>*>
readInroadsMap(string filename);
