//
// Created by devla on 2022-11-04.
//

#include <iostream>
#include <utility>
#include "resources.h"

std::string Resources::resourcePath;
std::string Resources::resourcePrefix;

std::string Resources::get(const std::string& path) {
    return resourcePath + "/" + path;
}

void Resources::parse(std::initializer_list<std::string*> args) {
    for(auto arg : args) {
        if((*arg).rfind(resourcePrefix, 0) == 0) {
            (*arg) = get((*arg).substr(resourcePrefix.length()));
        }
    }
}

void Resources::parse(std::string *arg) {
    parse({ arg });
}

std::vector<std::string> Resources::parse(std::initializer_list<std::string> args) {
    std::vector<std::string> vector;
    for(const auto& arg : args) {
        if(arg.rfind(resourcePrefix, 0) == 0) {
            vector.push_back(get(arg.substr(resourcePrefix.length())));
        }
    }
    return vector;
}

std::string Resources::parse(std::string arg) {
    return parse({ std::move(arg) })[0];
}

void Resources::init() {
    resourcePath = "C:/Users/devla/CLionProjects/KoRPG/resources";
    resourcePrefix = "res://";
}
