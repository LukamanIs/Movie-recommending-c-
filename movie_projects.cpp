#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <cctype>

using namespace std;

// Convert a string to lowercase for case-insensitive comparison
string toLowerCase(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

// Display matching movies, randomized and limited by maxResults
void displayMatches(const vector<string>& matches, int maxResults) {
    if (matches.empty()) {
        cout << "No matches found.\n";
        return;
    }

    // Shuffle the matches
    vector<string> shuffledMatches = matches; // Create a copy to shuffle
    random_device rd;
    mt19937 g(rd());
    shuffle(shuffledMatches.begin(), shuffledMatches.end(), g);

    // Display the matches
    cout << "Movies found (randomized):\n";
    for (int i = 0; i < min(maxResults, (int)shuffledMatches.size()); ++i) {
        cout << shuffledMatches[i] << endl;
    }
}

// Clear the screen
void clearScreen() {
#ifdef _WIN32
    system("CLS"); // Windows
#else
    system("clear"); // Linux/Unix/Mac
#endif
}

int main() {
    vector<string> matchingLines;
    string filename = "moviesgenre.txt";
    int maxResults = 5; // Default max results
    int option = 0;

    // Predefined genres
    vector<string> genres = {
        "Action", "Adventure", "Animation", "Comedy", "Crime",
        "Drama", "Fantasy", "Horror", "Romance", "Sci-Fi", "Thriller"
    };

    while (true) {
        // Display the menu
        cout << "\n===== Movie Recommendation System =====\n";
        cout << "1. Search for a movie by genre\n";
        cout << "2. Show previous matches (randomized)\n";
        cout << "3. Change max results\n";
        cout << "4. Clear the screen\n";
        cout << "5. Exit\n";
        cout << "Choose an option: ";
        cin >> option;

        if (option == 5) {
            cout << "Exiting the program. Goodbye!\n";
            break;
        }
        else if (option == 1) {
            // Display available genres
            cout << "\nAvailable genres:\n";
            for (const auto& genre : genres) {
                cout << "- " << genre << endl;
            }

            // Ask for genre input
            string searchGenre;
            cout << "\nEnter the genre you want to search for: ";
            cin.ignore(); // Clear input buffer
            getline(cin, searchGenre);
            searchGenre = toLowerCase(searchGenre);

            // Open the file and search for matching lines
            ifstream file(filename);
            if (!file.is_open()) {
                cout << "Error: Could not open file '" << filename << "'.\n";
                continue;
            }

            matchingLines.clear();
            string line;
            while (getline(file, line)) {
                if (toLowerCase(line).find(searchGenre) != string::npos) {
                    matchingLines.push_back(line);
                }
            }
            file.close();

            // Display results
            displayMatches(matchingLines, maxResults);
        }
        else if (option == 2) {
            // Show previous matches
            displayMatches(matchingLines, maxResults);
        }
        else if (option == 3) {
            // Change the maximum results
            cout << "Enter the maximum number of results to display: ";
            cin >> maxResults;

            if (cin.fail() || maxResults <= 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Max results must be a positive number.\n";
                maxResults = 5; // Reset to default
            }
            else {
                cout << "Max results updated to " << maxResults << ".\n";
            }
        }
        else if (option == 4) {
            // Clear the screen
            clearScreen();
        }
        else {
            cout << "Invalid option! Please choose a number between 1 and 5.\n";
        }
    }

    return 0;
}
