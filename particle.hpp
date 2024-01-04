#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <cmath>
#include <memory>

#include "resonanceType.hpp"

// struct for the 3D impulse vector
struct Impulse {
  // components
  double fPx{0};
  double fPy{0};
  double fPz{0};

  // Print method
  void Print() const;

  // method to compute squared norm
  double SquaredNorm() const;
};

// sum operator overload
Impulse operator+(const Impulse& p1, const Impulse& p2);

namespace pt {

class Particle {
 public:
  // constructors
  Particle(std::string const& name, Impulse P);
  Particle() = default;

  // getters
  int GetIndex() const;

  double GetPx() const;
  double GetPy() const;
  double GetPz() const;

  double GetCharge() const;

  double GetMass() const;
  double GetEnergy() const;

  // setters

  void SetIndex(int index);
  void SetIndex(std::string const& name);

  void SetP(double px, double py, double pz);
  void SetP(Impulse const& p);

  // add new particle / resonance type
  static void AddParticleType(std::string const& name, double mass, int charge,
                              double width = 0.);

  // compute invariant mass of two particles
  double InvMass(Particle const& p) const;

  // simulate decay of a particle into two daughters
  int Decay2body(Particle& dau1, Particle& dau2) const;

  // print methods
  static void PrintParticleTypes();
  void Print() const;

 private:
  static const int fMaxNumParticleType;
  static std::unique_ptr<std::unique_ptr<ParticleType>[]> fParticleTypes;
  static int fNParticleType;
  int fIndex;
  Impulse fP;

  // find particle type index
  static int FindParticle(std::string const& name);

  // apply Lorentz transformation
  void Boost(double bx, double by, double bz);
};
}  // namespace pt

#endif