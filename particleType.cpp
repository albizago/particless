#include "particleType.hpp"

namespace pt {

ParticleType::ParticleType(char* name, double mass, int charge)
    : fName(name), fMass(mass), fCharge(charge) {
  if (mass < 0 || (charge < -1 && charge > 1))
    throw std::runtime_error("Invalid input");
}

const char* ParticleType::getName() const { return fName; }

double ParticleType::getMass() const { return fMass; }

int ParticleType::getCharge() const { return fCharge; }

void ParticleType::Print() const {
  std::cout << "\n PARTICLE DATA \n\n -------------- \n\n"
            << " Name: " << std::setw(8) << fName << "\n Mass: " << std::setw(8) << fMass
            << "\n Charge: " << std::setw(6) << fCharge << '\n';
}

}  // namespace pt