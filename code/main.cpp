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
        if (temp_x == y) {
            break;
        }
    }

    display_content(temp_string);

   // End ncurses
    endwin();
    return 0;
}

// Initialize ncurses

void init() {
    setlocale(LC_ALL, "en_US.UTF-8");
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    cbreak();
    return;
}

// TO FIX FOR DISPLAY ERRORS WE NEED TO FIX THIS TO PRINT FOR WIDE CHARACTERS

void display_content(std::string content) {
    // for(int i=0; i<content.size(); i++) {
    //     mvprintw(i, 0, "%c", content[i]);
    // }
    clear(); // Clear the screen before we use it
    refresh(); // Refresh the empty screen so we can use newwin
    int x, y; // Max bounds

    // TEST STUFF
    // Set up window
    getmaxyx(stdscr, y, x); 
    WINDOW *win = newwin(y, x, 0, 0);
    box(win, 0, 0);

    // Set up variables
    int max_x = x-3;
    int max_y = y-1;
    int start_x, start_y = 3; 
    int cur_x = start_x;
    int cur_y = start_y;

    // Actually print the content
    for(int i=0; i<content.size(); i++) {
        // if (cur_y >= y-2) {
        //     break;
        // }
        const char * letter; 
        bool assigned_letter = false;
        if (cur_x >= x-4) {
            cur_y += 1;
            cur_x = 2; 
        }
        if (content[i] == '\n') {
            cur_y += 1;
            cur_x = 2;
        } else {
            cur_x += 1;
        }
        if (cur_y >= max_y) {
            break;
        }

        if (content[i] == '\'') {
            letter = "'";
            assigned_letter = true;
        } else if (content[i] == '-') {
            letter = "-";
            assigned_letter = true;
        }

        if (assigned_letter) {
            mvwprintw(win, cur_y, cur_x, "%c", letter);
            // cur_x ++;
        } else {
            mvwprintw(win, cur_y, cur_x, "%c", content[i]);
            // cur_x ++;
        }
        mvwprintw(win, cur_y, cur_x, "%c", content[i]);

    }
    wrefresh(win);
    getch();

    // getmaxyx(stdscr, y, x); 
    // WINDOW *win = newwin(y, x, 0, 0);
    // box(win, 0, 0);
    // mvwprintw(win, 0, 1, content.c_str());
    // wrefresh(win);
    // getch();
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