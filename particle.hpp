#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include "particleType.hpp"

struct Impulse {
  double fPx{0};
  double fPy{0};
  double fPz{0};
};

namespace pt {

class Particle {
 public:
  Particle(char* name, Impulse P);
  const int getIndex() const;
  static void AddParticleType(char* name, double mass, int charge,
                              double lenght);
  void setIndex(int index);
  void setIndex(char* name);
  static void PrintParticleTypes();

  void Print() const;

 private:
  static ParticleType** fParticleType;
  static const int fMaxNumParticleType;
  static int fNParticleType;
  const int fIndex;
  Impulse fP;

  const int FindParticle(char* name) const;
};

}  // namespace pt

#endif