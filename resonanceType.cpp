#include "resonanceType.hpp"

namespace pt {

// parametric constructor
ResonanceType::ResonanceType(std::string const& name, double mass, int charge, double width)
    : ParticleType(name, mass, charge), fWidth(width) {}

// default constructor; explicitly defined because of const data members
ResonanceType::ResonanceType() : ParticleType(), fWidth(0.) {}

// returns the resonance width
double ResonanceType::GetWidth() const { return fWidth; }

// prints the resonance type data
void ResonanceType::Print() const {
  ParticleType::Print();
  std::cout << " Width: " << std::setw(7) << fWidth << '\n';
}

}  // namespace pt