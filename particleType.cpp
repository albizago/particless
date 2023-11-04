#include "particleType.hpp"

namespace pt {

ParticleType::ParticleType(std::string const& name, double mass, int charge)
    : fName(name), fMass(mass), fCharge(charge) {
  if (mass < 0 || charge < -1 || charge > 1)
    throw std::runtime_error("Invalid input");
}

std::string const& ParticleType::GetName() const { return fName; }

double ParticleType::GetMass() const { return fMass; }

int ParticleType::GetCharge() const { return fCharge; }

double ParticleType::GetWidth() const { return 0.; }

void ParticleType::Print() const {
  std::cout << "\n PARTICLE TYPE DATA \n\n -------------- \n\n"
            << " Name: " << std::setw(8) << fName << "\n Mass: " << std::setw(8)
            << fMass << "\n Charge: " << std::setw(6) << fCharge << '\n';
}

}  // namespace pt