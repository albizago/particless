#include "particle.hpp"

const int pt::Particle::fMaxNumParticleType = 10;
int pt::Particle::fNParticleType = 0;

pt::Particle::Particle(char* name, Impulse P)
    : fIndex(FindParticle(name)), fP(P) {
  if (fIndex == -1) throw std::runtime_error("Particle not found");
  ++fNParticleType;
}

int pt::Particle::FindParticle(char* name) {
  int i{0};

  for (; i < fMaxNumParticleType; ++i) {
    if (fParticleType[i]->getName() == name) {
      break;
    }
  }

  if (i != fMaxNumParticleType) {
    return i;
  } else {
    std::cout << "Particle not found \n";
    return -1;
  }
}

const int pt::Particle::getIndex() const { return fIndex; }

void pt::Particle::AddParticleType(char* name, double mass, int charge,
                                   double lenght) {
  if (FindParticle(name) == -1 && fNParticleType < fMaxNumParticleType) 
  
  fParticleType[]
  }
