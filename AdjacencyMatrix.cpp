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
        vector<string> genres;
        int insertionPlace;
        Movie(int _year, string _genre, string _title, string _language, vector<string> _genres, int _insertionPlace);
};
// read in from csv file
vector<Movie> readCSV() {
    ifstream file("IMDb_movies_version_1.csv");
    string genre, title, skipline, imdb_title, year, language;
    vector<Movie> inputs;
    int insertion = 0;
    if(file.is_open()) {
        getline(file, skipline);

        while (file.good()) {
            vector<string> genres;
            getline(file, imdb_title, ',');
            getline(file, title, ',');
            getline(file, year, ',');
            getline(file, genre, ',');
            getline(file, language);
            Movie obj = Movie(stoi(year), genre, title, language, genres, insertion);
            inputs.push_back(obj);
            insertion++;
        }
    }
    return inputs;
}
// determine whether or not there is going to be a connection between the movies
//     we decided to base this off of if genre of movie 1 == genre of movie 2, and also if abs(year of movie 1 - year of movie 2) <= 3, they are connected (there is an edge)
bool isEdge(Movie obj1, Movie obj2) {
    bool similarGenre = false;
    for (int i = 0; i < obj1.genres.size(); i++) {
        for(int j = 0; j < obj2.genres.size(); j++) {
            if (obj1.genres[i] == obj2.genres[j]) {
                similarGenre = true;
            }
        }
    }
    if (similarGenre && (abs(obj1.year - obj2.year) <= 3)) {
        return true;
    }
    return false;
}

void processGenres(Movie& obj) {
    int temp = 0;
    for (int i = 0; i < obj.genre.size(); i++) {
        if (obj.genre[i] == ',') {
            obj.genre.substr(temp,i);
            obj.genres.push_back(obj.genre.substr(temp,i));
            temp = i;
        }
    }
}
void printGraph(vector<int> graph[], vector<Movie> movies, Movie obj)
{
    cout << "\n Movies similar to "<< obj.title << "\n head ";
        for (auto x : graph[obj.insertionPlace])
           cout << "-> " << movies.at(x).title;
        printf("\n");
}

int main() {
    readCSV();
    vector<Movie> movies = readCSV();
    int graph[movies.size()][movies.size()];
    // convert the genres string into a vector of substrings to parse the genres into individual ones
    for (int i = 0; i < movies.size(); i++) {
        processGenres(movies[i]);
    }
    // for every movie that is read in from the csv
    for (int i = 0; i < movies.size(); i++) {
        // find if it will be connected to any other movie
        for (int j = i; j < movies.size(); j++) {
            if(isEdge(movies[i], movies[j])) {
                // if they are connected, insert into adjacency matrix
                graph[movies[i].insertionPlace][movies[j].insertionPlace] = 1;
                graph[movies[j].insertionPlace][movies[i].insertionPlace] = 1;
            }
        }
    }
    string userInput;
    cin >> userInput;
    cout << "Movies similar to: " << userInput << endl;
    for (int i = 0; i < movies.size(); i++) {
        if (movies.at(i) == userInput) {
            for (int j = i; j < movies.size(); j++) {
                if (graph[i][j] == 1 && graph[j][i] == 1) {
                    cout << movies.at(j).title << endl;
                }
            }
        }
    }
    return 0;
}