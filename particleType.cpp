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
  std::cout << " PARTICLE DATA \n\n -------------- \n\n"
            << " Name: " << fName << "\n Mass:" << fMass
            << "\n Charge: " << fCharge << "\n ";
}

}  // namespace pt