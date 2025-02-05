#ifndef EPUP_PARSER_H
#define EPUP_PARSER_H
#include <string>
#include <sstream>
#include <vector>

class EPUP_parser {
    std::string content;
    public:
        EPUP_parser(std::string content) : content(content) {}
        ~EPUP_parser();
    private:

};

class P_object {
    public:
        P_object(std::string content) {
            parse_content(content);
        }
        ~P_object();

        std::vector<std::string> get_content() {
            return content;
        }

    private:
    std::vector<std::string> content;

    void parse_content(std::string temp_content) {
        // Parse content
        
        // Variables we will need
        std::vector<std::string> new_content;
        std::istringstream stream(temp_content);
        std::string line;
        
        

        this->content = new_content;
    }

};

#endif