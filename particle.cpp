#include "particle.hpp"

namespace pt{

const int Particle::fMaxNumParticleType = 10;
int Particle::fNParticleType = 0;

Particle::Particle(char* name, Impulse P) : fIndex(FindParticle(name)), fP(P) {}


const int Particle::FindParticle(char* name) const {
  int i{0};

  for (;i < fMaxNumParticleType; ++i) {
    if (fParticleType[i]->getName() == name) {
      break;
    }
  }

  if (i != fMaxNumParticleType) {
    return i;
  } else {
    throw std::runtime_error("Particle not found");
  }
}


const int Particle::getIndex() const {
  return fIndex;
}

// void Particle::AddParticleType(char* name, double mass, int charge, double lenght);

void Particle::PrintParticleTypes(){
  for(int i = 0; i < fMaxNumParticleType; ++i){
    fParticleType[i]->Print();
  }
}

}
