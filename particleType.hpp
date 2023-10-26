#ifndef PARTICLETYPE_HPP
#define PARTICLETYPE_HPP

#include <iostream>
#include <stdexcept>
#include <iomanip>

namespace pt {

class ParticleType {
 public:
  ParticleType(char*, double, int);
  ParticleType() = default;
  const char* getName() const;
  double getMass() const;
  int getCharge() const;
  virtual void Print() const;

 private:
  const char* fName;
  const double fMass;
  const int fCharge;
};

}  // namespace pt

#endif