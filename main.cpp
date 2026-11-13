// Winter'24
// Instructor: Diba Mirza
// Student name: Albert Wang and Kevin Liu
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <cstring>
#include <algorithm>
#include <limits.h>
#include <iomanip>
#include <set>
#include <queue>
#include <map>
#include <sstream>
using namespace std;

#include "utilities.h"
#include "movies.h"

bool parseLine(string &line, string &movieName, double &movieRating);

int main(int argc, char** argv){
    if (argc < 2){
        cerr << "Not enough arguments provided (need at least 1 argument)." << endl;
        cerr << "Usage: " << argv[ 0 ] << " moviesFilename prefixFilename " << endl;
        exit(1);
    }

    ifstream movieFile (argv[1]);
 
    if (movieFile.fail()){
        cerr << "Could not open file " << argv[1];
        exit(1);
    }
  
    // Create an object of a STL data-structure to store all the movies
    map<string, double> data;
    string line, movieName;
    double movieRating;
    // Read each file and store the name and rating
    while (getline (movieFile, line) && parseLine(line, movieName, movieRating)){
            // Use std::string movieName and double movieRating
            // to construct your Movie objects
            // cout << movieName << " has rating " << movieRating << endl;
            // insert elements into your data structure
            if (getNextLine(line, movieName, movieRating)) {
                data[movieName] = movieRating;
            }
    }

    movieFile.close();

    if (argc == 2){
        for (auto movie : data) {
            cout << movie.first << ", " << movie.second << endl;
        }
        return 0;
    }

    ifstream prefixFile (argv[2]);

    if (prefixFile.fail()) {
        cerr << "Could not open file " << argv[2];
        exit(1);
    }

    vector<string> prefixes;
    while (getline (prefixFile, line)) {
        if (!line.empty()) {
            prefixes.push_back(line);
        }
    }


    //  For each prefix,
    //  Find all movies that have that prefix and store them in an appropriate data structure
    //  If no movie with that prefix exists print the following message
    vector<pair<string, pair<string, double>>> highestRated;

    for (string prefix: prefixes){
        vector<pair<string,double>> movies;
        auto it = data.lower_bound(prefix);
        while (it != data.end()){
            string name = it->first;
            if (name.substr(0,prefix.length()) != prefix){
                break;
            }

            movies.push_back(*it);
            ++it;
        }
        sort(movies.begin(), movies.end(), betterRating);

        if (movies.empty()){
            cout << "No movies found with prefix "<<"<replace with prefix>" << endl;
        }
        else{
            for (auto movie : movies){
                cout << movie.first << ", " << movie.second << endl;
            }
            highestRated.push_back({prefix,movies[0]});
        }
        //cout << "Best movie with prefix " << prefix << " is: " << movies[0].first << " with rating " << std::fixed << std::setprecision(1) << movies[0].second << endl;
    }

    for (auto movie : highestRated){
        cout << "Best movie with prefix " << movie.first << " is: " << movie.second.first << " with rating " << std::fixed << std::setprecision(1) << movie.second.second << endl;
    }

    return 0;
}

/* Add your run time analysis for part 3 of the assignment here as commented block*/

bool parseLine(string &line, string &movieName, double &movieRating) {
    int commaIndex = line.find_last_of(",");
    movieName = line.substr(0, commaIndex);
    movieRating = stod(line.substr(commaIndex+1));
    if (movieName[0] == '\"') {
        movieName = movieName.substr(1, movieName.length() - 2);
    }
    return true;
}