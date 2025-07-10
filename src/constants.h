#pragma once
#include<unordered_set>
#include<string>
#include<map>


constexpr double PI = 3.141592653589793;
constexpr double E 	= 2.71828182845903;

const std::unordered_set<std::string> FUNCTIONS = {
    "sin","cos","tan","exp","log","sqrt"
};

const std::map<std::string, int> OPERATOR_PRECEDENCE = {
  {"^",4},{"*",3},{"/",3},{"+",2},{"-",2}
};

const std::map<std::string,bool> OPERATOR_IS_ASSOCIATIVE = {
    {"^",false},{"*",true},{"/",true},{"+",true},{"-",true}
};
