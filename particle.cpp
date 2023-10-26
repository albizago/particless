#include "particle.hpp"

namespace pt {

int Particle::fNParticleType = 0;

Particle::Particle(char* name, Impulse P) : fIndex(FindParticle(name)), fP(P) {
  if (fIndex == fNParticleType) throw std::runtime_error("Particle not found");
}

int Particle::FindParticle(char* name) {
  int i{0};

  for (; i < fNParticleType; ++i) {
    if (fParticleType[i]->getName() == name) {
      break;
    }
  }

  if (i != fMaxNumParticleType) {
    return i;
  } else {
    std::cout << "Particle not found \n";
    return fNParticleType;
  }
}

const int Particle::getIndex() const { return fIndex; }

// AGGIUNGE E BBASTA
void Particle::AddParticleType(char* name, double mass, int charge,
                               double width = 0.) {
  if (FindParticle(name) == fNParticleType &&
      FindParticle(name) < fMaxNumParticleType) {
    (width == 0.) ? fParticleType[FindParticle(name)] =
                        new ParticleType(name, mass, charge)
                  : fParticleType[FindParticle(name)] =
                        new ResonanceType(name, mass, charge, width);

    ++fNParticleType;
  }
};

void Particle::PrintParticleTypes() {
  for (int i = 0; i < fMaxNumParticleType; ++i) {
    fParticleType[i]->Print();
  }
}

void Particle::setIndex(int index) {
  if (index >= 0 && index < fNParticleType) fIndex = index;
}

void Particle::setIndex(char* name) {
   if (FindParticle(name) >= 0 && FindParticle(name) < fNParticleType) fIndex = FindParticle(name);
}

}  // namespace pt
