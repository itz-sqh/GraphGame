#pragma once
#include<random>
#include<chrono>

class Rng {
public:
    static int getInt(int min, int max);
    static float getFloat(float min, float max);

private:
    static std::mt19937 gen;
    static bool initiated;
    static void init();

};