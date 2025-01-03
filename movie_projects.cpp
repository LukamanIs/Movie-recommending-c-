#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <random>
#include <cctype>

using namespace std;

// Function to shuffle and display matching lines
void shuffleAndDisplay(vector<string>& lines, int max_line) {
    random_device rd;
    mt19937 g(rd());
    shuffle(lines.begin(), lines.end(), g);

    cout << "\nRandomized matching lines:\n";
    for (int i = 0; i < min(max_line, (int)lines.size()); i++) {
        cout << lines[i] << endl;
    }
}

// Convert a string to lowercase for case-insensitive comparison
string toLowerCase(const string& str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

int main() {
    int max_line = 5; // Maximum number of matching lines to display
    int option = 0;
    string search;
    vector<string> matchingLines;

    const int boxWidth = 80; // Total width of the box
    const int innerWidth = boxWidth - 2; // Width for the text inside the box

    // Print top border
    cout << string(boxWidth, '*') << "\n";

    // Print empty lines with borders
    for (int row = 0; row < 3; ++row) {
        cout << "*" << string(innerWidth, ' ') << "*\n";
    }

    // Centered menu messages
    vector<string> messages = {
        "Hello, This Is a Movie Recommendation System",
        "Enter 1 to search for a movie by genre",
        "Enter 2 to shuffle and display previous matches",
        "Enter 3 to clear the screen",
        "Enter 4 to exit"
    };

    for (const auto& msg : messages) {
        int padding = (innerWidth - msg.size()) / 2;
        cout << "*" << string(padding, ' ') << msg << string(innerWidth - padding - msg.size(), ' ') << "*\n";
    }

    // Print empty lines with borders and bottom border
    for (int row = 0; row < 3; ++row) {
        cout << "*" << string(innerWidth, ' ') << "*\n";
    }
    cout << string(boxWidth, '*') << "\n";

    // Main loop for user interaction
    while (true) {
        cout << "\nChoose an option (1-4): ";
        cin >> option;

        if (option == 4) {
            cout << "Exiting the program. Goodbye!\n";
            break;
        }
        else if (option == 1) {
            ifstream myfile("moviesgenre.txt");
            if (!myfile.is_open()) {
                cerr << "Error: Could not open file 'moviesgenre.txt'\n";
                continue;
            }

            cout << "\nEnter the genre you want to search for: ";
            cin >> search;
            search = toLowerCase(search);

            matchingLines.clear(); // Clear previous matches
            string line;
            int total = 0;

            while (getline(myfile, line)) {
                string lowerLine = toLowerCase(line);
                if (lowerLine.find(search) != string::npos) {
                    matchingLines.push_back(line);
                    cout << line << endl;
                    total++;

                    if (total >= max_line) {
                        cout << "Reached the maximum number of matches (" << max_line << ").\n";
                        break;
                    }
                }
            }

            if (matchingLines.empty()) {
                cout << "No matching lines found for genre: " << search << "\n";
            }

            myfile.close();
        }
        else if (option == 2) {
            if (!matchingLines.empty()) {
                shuffleAndDisplay(matchingLines, max_line);
            }
            else {
                cout << "No matching lines to shuffle. Please search first.\n";
            }
        }
        else if (option == 3) {
#ifdef _WIN32
            system("CLS");
#else
            system("clear");
#endif
        }
        else {
            cout << "Invalid option. Please enter a number between 1 and 4.\n";
        }
    }

    return 0;
}
