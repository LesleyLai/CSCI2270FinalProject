#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <random>
#include <ctime>

class Rand_double {
public:
    using seed_type = std::default_random_engine::result_type;

    // Creates a random double generation function
    // The range of generated double is (low, high)
    Rand_double(double low, double high)
        :Rand_double(low, high, static_cast<seed_type>(std::time(0))) {
    }

    // Creates a random double generation function from a know seed
    Rand_double(double low, double high, seed_type seed)
        :dis_(low, high),
         engine_(seed) {}

    double operator()() { return dis_(engine_); }
private:
    std::uniform_real_distribution<> dis_;
    std::default_random_engine engine_;
};

#endif // RANDOM_HPP
