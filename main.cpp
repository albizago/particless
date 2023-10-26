#include "particle.hpp"
#include "resonanceType.hpp"

int main() {
  try {
    pt::ParticleType* part_array[2];
    part_array[0] = new pt::ParticleType("Gino", 130., 0);
    part_array[1] = new pt::ResonanceType("Paolo", 320., -1, 3.);
    for (pt::ParticleType* ptr : part_array) {
      ptr->Print();
    }
    std::cout << '\n';
  } catch (std::exception& e) {
    std::cerr << e.what();
  } catch (...) {
    std::cerr << "Unknown error";
  }
}