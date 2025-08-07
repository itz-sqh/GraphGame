#include "math/Rng.h"

std::mt19937 Rng::m_gen;
bool Rng::m_initiated = false;

void Rng::init() {
    if (!m_initiated) {
        m_gen.seed(std::chrono::steady_clock::now().time_since_epoch().count());
        m_initiated = true;
    }
}

int Rng::getInt(int min, int max) {
    init();
    std::uniform_int_distribution<> dist(min, max);
    return dist(m_gen);
}

float Rng::getFloat(float min, float max) {
    init();
    std::uniform_real_distribution<float> dist(min, max);
    return dist(m_gen);
}
