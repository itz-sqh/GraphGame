#pragma once
#include<string>
#include<map>


constexpr double PI = 3.141592653589793;
constexpr double E 	= 2.71828182845903;

// function --> argc
const std::map<std::string,int> FUNCTIONS = {
    {"sin",1},{"cos",1},{"tan",1},{"exp",1},{"log",1},{"sqrt",1},{"max",2},{"min",2}
};

const std::map<std::string, int> OPERATOR_PRECEDENCE = {
  {"u-",5},{"u+",5},{"^",4},{"*",3},{"/",3},{"+",2},{"-",2}
};
//u- = unary -

const std::map<std::string,bool> OPERATOR_IS_ASSOCIATIVE = {
        {"^",false},{"*",true},{"/",true},{"+",true},{"-",true}
};
