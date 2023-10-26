#include "particleType.hpp"

namespace pt{

    ParticleType::ParticleType(char* name, double mass, int charge) : fName(name), fMass(mass), fCharge(charge) {
        if(mass < 0 || (charge < -1 && charge > 1) ) throw std::runtime_error("Invalid input");

    }

    char* const& ParticleType::getName() const {
        return fName;
    }

    double ParticleType::getMass() const {
        return fMass;
    }

    int ParticleType::getCharge() const {
        return fCharge;
    }

}