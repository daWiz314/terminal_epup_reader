#ifndef EPUP_PARSER_H
#define EPUP_PARSER_H

#include <string>
#include <vector>
#include <iostream>

class EPUP_parser {
    std::string content;
    public:
        EPUP_parser(std::string content) : content(content) {}
    private:

};

class P_object {
    public:
        P_object(std::string content) {
            parse_content(content);
        }

        std::vector<std::string> get_content() {
            return content;
        }

        void display_content() {
            std::cout << "Displaying: " << std::endl;
            for(int i=0; i<content.size(); i++) {
                std::cout << content[i] << std::endl;
            }
        }

    private:
    std::vector<std::string> content;

    void parse_content(std::string temp_content) {
        std::cout << "Parsing!" << std::endl;
        // Parse content
        
        // Variables we will need
        std::vector<std::string> new_content;

        int index = 0;
        bool capture = true;

        while (index <= temp_content.length()) {
            switch (temp_content[index]) {
                case '<':
                    capture = false;
                    break;
                case '>':
                    capture = true;
                    index++;
                    continue;
                    break;
                default:
                    break;
            }
            if (capture) {
                new_content.push_back(std::string(1, temp_content[index]));
            }
            index++;
        }
        
        std::vector<std::string> new_temp_content;
        std::string temp;
        for(int i=0; i<new_content.size(); i++) {
            if(new_content[i] == "\n") {
                new_temp_content.push_back(temp);
                temp = "";
            } else {
                temp += new_content[i];
            }
        }
        this->content = new_temp_content;
    }

};

#endif