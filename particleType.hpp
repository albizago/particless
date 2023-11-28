#ifndef PARTICLETYPE_HPP
#define PARTICLETYPE_HPP

#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>

namespace pt {

class ParticleType {
 public:
  ParticleType(std::string const&, double, int);
  ParticleType();

  std::string const& GetName() const;
  double GetMass() const;
  int GetCharge() const;
  virtual double GetWidth() const;
  virtual void Print() const;

 private:
  const std::string fName;
  const double fMass;
  const int fCharge;
};

}  // namespace pt

#endif