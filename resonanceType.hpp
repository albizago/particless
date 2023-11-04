#ifndef RESONANCETYPE_HPP
#define RESONANCETYPE_HPP

#include "particleType.hpp"

namespace pt {

class ResonanceType : public ParticleType {
 public:
  ResonanceType(std::string const&, double, int, double);
  ResonanceType() = default;

  double GetWidth() const;

  void Print() const;

 private:
  double const fWidth;
};

}  // namespace pt

#endif