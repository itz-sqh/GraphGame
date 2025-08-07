#pragma once
#include<random>
#include<chrono>

class Rng {
public:
    static int getInt(int min, int max);

    static float getFloat(float min, float max);

private:
    static std::mt19937 m_gen;
    static bool m_initiated;

    static void init();
};
