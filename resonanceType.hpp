#ifndef RESONANCETYPE_HPP
#define RESONANCETYPE_HPP

#include "particleType.hpp"

namespace pt {

class ResonanceType : public ParticleType {
 public:
  // constructors
  ResonanceType(std::string const&, double, int, double);
  ResonanceType();

  // getters
  double GetWidth() const;

  // Print member function
  void Print() const;

 private:
  double const fWidth;
};

}  // namespace pt

#endif