#include "resonanceType.hpp"

namespace pt {

ResonanceType::ResonanceType(char* name, double mass, int charge, double width)
    : ParticleType(name, mass, charge), fWidth(width) {}

double ResonanceType::getWidth() const { return fWidth; }

void ResonanceType::Print() const {
  ParticleType::Print();
  std::cout << " Width: " << std::setw(7) << fWidth << '\n';
}

}  // namespace pt