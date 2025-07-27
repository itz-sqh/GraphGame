#include "math/Rng.h"

std::mt19937 Rng::gen;
bool Rng::initiated = false;

void Rng::init() {
    if (!initiated) {
        gen.seed(std::chrono::steady_clock::now().time_since_epoch().count());
        initiated = true;
    }
}

int Rng::getInt(int min, int max) {
    init();
    std::uniform_int_distribution<> dist(min, max);
    return dist(gen);
}

float Rng::getFloat(float min, float max) {
    init();
    std::uniform_real_distribution<float> dist(min, max);
    return dist(gen);
}
