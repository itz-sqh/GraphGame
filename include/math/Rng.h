#pragma once
#include<random>
#include<chrono>

class Rng {
public:
    static int getInt(int min, int max);
    static float getFloat(float min, float max);
    static void setSeed(uint32_t seed);

private:
    static std::mt19937 gen_;
    static bool initiated_;
    static void init();

};