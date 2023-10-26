#ifndef PARTICLETYPE_HPP
#define PARTICLETYPE_HPP

#include <stdexcept>
#include <iostream>

namespace pt{

class ParticleType {
  const char* fName;
  const double fMass;
  const int fCharge;

 public:
  ParticleType(char*, double, int);
  ParticleType() = default;
  char* const& getName() const;
  double getMass() const;
  int getCharge() const;
  virtual void Print() const;
};

}

#endif