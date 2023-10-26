#include "particle.hpp"

const int pt::Particle::fMaxNumParticleType = 10;
int pt::Particle::fNParticleType = 0;

pt::Particle::Particle(char* name, Impulse P) : fIndex(FindParticle(name)), fP(P) {}


const int pt::Particle::FindParticle(char* name) const {
  int i{0};

  for (;i < fMaxNumParticleType; ++i) {
    if (fParticleType[i].getName() == name) {
      break;
    }
  }

  if (i != fMaxNumParticleType) {
    return i;
  } else {
    throw std::runtime_error("Particle not found");
  }
}


const int pt::Particle::getIndex() const {
  return fIndex;
}

static void AddParticleType(char* name, double mass, int charge,
                              double lenght);

