#include <ncurses.h>
#include <fstream>
#include <string>

#include "EPUP_parser.h"


// Function prototypes
void init();
std::string read_file(std::string path);
void display_content(std::string content);


// Main function
int main(int arg, char* args[]) {
    init(); // Init ncurses
    std::string content = read_file("src/epup_container/EPUB/c/c5.xhtml"); // Get demo content to read

    P_object test(content); // Create test object
    std::vector<std::string> temp = test.get_content(); // Get content

    // TEST STUFF
    int x, y;
    getmaxyx(stdscr, y, x);
    std::string temp_string;
    
    int temp_x = 0;
    for (int i=0; i<temp.size(); i++) {
        if (temp[i].length() >= x) {
            temp_x += 1;
            temp_string += temp[i];
        } else {
            temp_string += temp[i];
        }
        temp_string += "\n";
        // if (temp_x == y) {
        //     break;
        // }
    }
    // std::cout << temp_string << std::endl;
    // display_content(temp_string);

    WINDOW *win = newwin(y, x, 0, 0);
    box(win, 0, 0);
    wrefresh(win);
    mvwprintw(win, 0, 0, "Hello World!");
    wrefresh(win);
    getch();

    // File output was just to make sure we were actually getting any data

    // std::ofstream file("src/test.txt");
    // file << temp_string;
    // file.close();
    // End ncurses
    endwin();
    return 0;
}

// Initialize ncurses

void init() {
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    cbreak();
    return;
}


void display_content(std::string content) {
    // for(int i=0; i<content.size(); i++) {
    //     mvprintw(i, 0, "%c", content[i]);
    // }
    clear();
    int x, y;
    getmaxyx(stdscr, y, x);
    WINDOW *win = newwin(y, x, 0, 0);
    box(win, 0, 0);
    wrefresh(win);
    mvwprintw(win, 0, 0, content.c_str());
    wrefresh(win);
    getch();
    endwin();
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