#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;
// store movie data
class Movie {
    public:
        int year;
        string genre;
        string title;
        string language;
    private:
    Movie(int _year, string _genre, string _title, string _language);
};
// read in from csv file
vector<Movie obj> readCSV() {
    ifstream file("IMDb_movies.csv");
    string genre, title, skipline, imdb_title, year, language;
    vector<Movie obj> inputs;
    if(file.is_open()) {
        getline(file, skipline);

        while (file.good()) {
            getline(file, imdb_title, ',');
            getline(file, title, ',');
            getline(file, year, ',');
            getline(file, genre, ',');
            getline(file, language);
            Movie obj = new obj(stoi(year), genre, title, language);
            inputs.push_back(obj);
        }
    }
    return inputs;
}
// determine whether or not there is going to be a connection between the movies
    // we decided to base this off of if genre of movie 1 == genre of movie 2, and also if abs(year of movie 1 - year of movie 2) <= 3, they are connected (there is an edge)
bool isEdge(Movie obj1, Movie obj2) {
    return true;
    return false;
}

int main() {
    vector<Movie obj> movies = readCSV();
    // for every movie that is read in from the csv
    for (int i = 0; i < movies.size(); i++) {
        // find if it will be connected to any other movie
        for (int j = i; j < movies.size(); j++) {
            if(isEdge(movies[i], movies[j])) {
                
            }
        }
    }
    return 0;
}