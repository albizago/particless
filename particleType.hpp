#ifndef PARTICLETYPE_HPP
#define PARTICLETYPE_HPP

#include <iomanip>
#include <iostream>
#include <stdexcept>

namespace pt {

class ParticleType {
 public:
  ParticleType(char*, double, int);
  ParticleType() = default;

  const char* GetName() const;
  double GetMass() const;
  int GetCharge() const;

  virtual void Print() const;

 private:
  const char* fName;
  const double fMass;
  const int fCharge;
};

}  // namespace pt

#endif