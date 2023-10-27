#include "particle.hpp"
#include "particleType.hpp"
#include "resonanceType.hpp"

int main() {
  try {
    pt::ParticleType* particle_array[2];
    particle_array[0] = new pt::ParticleType("Gino", 130., 0);
    particle_array[1] = new pt::ResonanceType("Paolo", 320., -1, 3.);
    for (pt::ParticleType* ptr : particle_array) {
      ptr->Print();
    }
    std::cout << '\n';

    pt::Particle::AddParticleType("Mesone D aka Piero", 1870., 0);
    pt::Particle::AddParticleType("Kaccone positivo aka Ignazio", 490., 1, 2.);
    pt::Particle::AddParticleType("zio", 1., 1);

    pt::Particle::PrintParticleTypes();

    pt::Particle p("Gino", {1., 2., 3.});
    p.Print();

    pt::Particle g("Azio", {1., 2., 3.});

    // char* provv_name;

    // std::cin >> provv_name;

    // pt::Particle::AddParticleType(provv_name, 3., 25);

  } catch (std::exception& e) {
    std::cerr << e.what();
  } catch (...) {
    std::cerr << "Unknown error";
  }
}