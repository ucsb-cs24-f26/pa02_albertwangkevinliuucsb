#ifndef MOVIES_H
#define MOVIES_H

#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

bool getNextLine(string &line, string &name, double &rating);
bool betterRating(pair<string, double> first, pair<string, double> second);

#endif