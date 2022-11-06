//
// Created by devla on 2022-11-04.
//

#ifndef KORPG_RESOURCES_H
#define KORPG_RESOURCES_H


#include <string>
#include <vector>

class Resources {
private:
public:
    static std::string resourcePath;
    static std::string resourcePrefix;

    static void init();

    static std::string get(const std::string& path);
    static void parse(std::initializer_list<std::string*> args);
    static void parse(std::string* arg);
    static std::vector<std::string> parse(std::initializer_list<std::string> args);
    static std::string parse(std::string arg);
};


#endif //KORPG_RESOURCES_H
