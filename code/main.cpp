#include <ncurses.h> // Ncurses
#include <fstream> // File input and output
#include <string> // For working with strings
#include <codecvt> // For converting string to wchar_t
#include <locale>
#include <iostream>

#include "EPUP_parser.h"


// Function prototypes
void init();
std::string read_file(std::string path);
void display_content(std::string& content);


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

    

    // printw(temp_string.c_str());
    // getch();

    


    // display_content(content);
    // Displaying with printw seems to print it without extra lines. I think I need to redo the EPUP_Parser file, and if anything get rid of most of it.
    // I just need to get the content, and then file it down to just the stuff in the <p> tags
    
    printw(content.c_str());
    getch();

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

void display_content(std::string& content) {
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

    int start_x = 2;
    int start_y = 2;

    int max_x = x-3;
    int max_y = y-3;

    int cur_x = start_x;
    int cur_y = start_y;

    std::vector<std::string>lines;

    for(int i=0; i<content.length(); i++) {
        std::string temp_content;

        if(content[i] == '\n') {
            lines.push_back("\n");
            continue;
        }
        if(cur_x >= max_x) {
            lines.push_back(temp_content);
            cur_x = start_x;
            continue;
        }
        cur_x ++;
        temp_content += content[i];
    }

    printw("%c", lines[0].c_str());
    getch();

    for(int i=0; i<lines.size(); i++) {
        mvwprintw(win, cur_y, 1, lines[i].c_str());
        cur_y ++;
        // if (cur_y >= max_y) {
        //     break;
        // }
        wrefresh(win);
    }
   mvwprintw(win, 2, 2, "Hello World Part 2"); 

    
    // mvwprintw(win, 0, 0, content.c_str());
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