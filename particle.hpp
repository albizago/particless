#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include "particleType.hpp"
#include "resonanceType.hpp"

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
                              double width);
  void setIndex(int index);
  void setIndex(char* name);
  static void PrintParticleTypes();

  void Print() const;

 private:
  static const int fMaxNumParticleType = 10;
  static ParticleType* fParticleType[fMaxNumParticleType];
  static int fNParticleType;
  const int fIndex;
  Impulse fP;

  static int FindParticle(char* name);
};

}  // namespace pt

#endif