#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <memory>

#include "resonanceType.hpp"

struct Impulse {
  double fPx{0};
  double fPy{0};
  double fPz{0};

  void Print() const;
  double SquaredNorm() const;
};

Impulse operator+(const Impulse& p1, const Impulse& p2);

namespace pt {

class Particle {
 public:
  Particle(char* name, Impulse P);
  const int GetIndex() const;
  static void AddParticleType(char* name, double mass, int charge,
                              double width = 0.);
  void SetIndex(int index);
  void SetIndex(char* name);

  static void PrintParticleTypes();
  void Print() const;

  double GetPx() const;
  double GetPy() const;
  double GetPz() const;

  double GetMass() const;
  double GetEnergy() const;

  double InvMass(Particle& p) const;

  void SetP(double px, double py, double pz);
  void SetP(Impulse const& p);

 private:
  static const int fMaxNumParticleType;
  static std::unique_ptr<std::unique_ptr<ParticleType>[]> fParticleTypes;
  static int fNParticleType;
  int fIndex;
  Impulse fP;

  static int FindParticle(char* name);
};

}  // namespace pt

#endif