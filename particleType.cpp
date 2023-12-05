#include "particleType.hpp"

namespace pt {

// parametric constructor
ParticleType::ParticleType(std::string const& name, double mass, int charge)
    : fName(name), fMass(mass), fCharge(charge) {
  if (mass < 0 || charge < -1 || charge > 1)
    throw std::runtime_error("Invalid input");
}

// default constructor; explicitly defined because of const data members
ParticleType::ParticleType() : fName(""), fMass(0.), fCharge(0) {}

// returns the name of the particle type
std::string const& ParticleType::GetName() const { return fName; }

// returns the mass of the particle type
double ParticleType::GetMass() const { return fMass; }

// returns the charge of the particle type
int ParticleType::GetCharge() const { return fCharge; }

// returns the resonance width (0 for stable particles)
double ParticleType::GetWidth() const { return 0.; }

// prints the particle type data
void ParticleType::Print() const {
  std::cout << "\n PARTICLE TYPE DATA \n\n -------------- \n\n"
            << " Name: " << std::setw(8) << fName << "\n Mass: " << std::setw(8)
            << fMass << "\n Charge: " << std::setw(6) << fCharge << '\n';
}

}  // namespace pt