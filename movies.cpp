#include "movies.h"
using namespace std;
bool getNextLine(string &line, string &name, double &rating){
    int comma = line.find_last_of(",");
    // if comma is the index of that, we take everything before for the name
    // and everything after for the rating

    name = line.substr(0,comma);
    rating = stod(line.substr(comma+1)); // convert string to double

    if (name[0] == '"'){
        name = name.substr(1,comma-2); // check if the name is between quotations
    }
    return true;
}

bool betterRating(pair<string, double> first, pair<string, double> second) {
    if (first.second > second.second){
        return true;
    }

    if (first.second < second.second){
        return false;
    }

    return first.first < second.first;
}