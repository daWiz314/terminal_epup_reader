#include <ncurses.h>
#include <fstream>
#include <string>


// Function prototypes
void init();
std::string read_file(std::string path);
void display_content(std::string content);


// Main function
int main(int arg, char* args[]) {
    init(); // Init ncurses
    std::string content = read_file("src/epup_container/EPUB/c/c5.xhtml"); // Get demo content to read
    display_content(content); // Display content
    return 0;
}

// Initialize ncurses

void init() {
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    cbreak();
}

void display_content(std::string content) {
    int max_x, max_y;
    getmaxyx(stdscr, max_y, max_x); // We need full screen size to determine what to print
    // Max content we can print to the screen
    // To get this number, we will need to multiply max_x by max_y
    // Then, we will split the content into lines, and print them to the screen
    // If the content is bigger than the screen, we will need to scroll
    // We will also need to handle the scrolling
    std::string screen_content = content.substr(0, max_x * max_y);
    printw(screen_content.c_str());
    refresh();
    getch();
    return; // pause here
}

// Read file content

std::string read_file(std::string path) {
    std::string content; // Total content
    std::string line; // Line we are on
    std::ifstream file(path); // File stream

    while(getline(file, line)) { // Get line by line
        content += line + "\n"; // And add it to total content
    }
    return content; // Return fill content
}