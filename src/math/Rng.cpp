#include "math/Rng.h"

std::mt19937 Rng::gen_;
bool Rng::initiated_ = false;



void Rng::init() {
    if (!initiated_) {
        gen_.seed(std::chrono::steady_clock::now().time_since_epoch().count());
        initiated_ = true;
    }
}

int Rng::getInt(int min, int max) {
    init();
    std::uniform_int_distribution dist(min, max);
    return dist(gen_);
}

float Rng::getFloat(float min, float max) {
    init();
    std::uniform_real_distribution dist(min, max);
    return dist(gen_);
}
