#include <cmath>

#include "particle.hpp"

void Impulse::Print() const {
  std::cout << " Impulse:  (" << fPx << ", " << fPy << ", " << fPz << " ) \n";
}

double Impulse::SquaredNorm() const {
  return fPx * fPx + fPy * fPy + fPz * fPz;
}

Impulse operator+(const Impulse& p1, const Impulse& p2) {
  Impulse pTot;

  pTot.fPx = p1.fPx + p2.fPx;
  pTot.fPy = p1.fPy + p2.fPy;
  pTot.fPz = p1.fPz + p2.fPz;

  return pTot;
}

namespace pt {

const int Particle::fMaxNumParticleType = 10;

std::unique_ptr<std::unique_ptr<ParticleType>[]> Particle::fParticleTypes = std::make_unique<std::unique_ptr<ParticleType>[]>(Particle::fMaxNumParticleType);

// Public Methods

Particle::Particle(char* name, Impulse P) : fIndex(FindParticle(name)), fP(P) {
  if (fIndex == fNParticleType) throw std::runtime_error("Particle not found");
}

const int Particle::GetIndex() const { return fIndex; }

void Particle::AddParticleType(char* name, double mass, int charge,
                               double width) {
  if (FindParticle(name) == fNParticleType &&
      FindParticle(name) < fMaxNumParticleType) {
    (width == 0.) ? fParticleTypes[FindParticle(name)] =
                        new ParticleType(name, mass, charge)
                  : fParticleTypes[FindParticle(name)] =
                        new ResonanceType(name, mass, charge, width);

    ++fNParticleType;
  } else {
    std::cout << " Particle already exists \n";
  }
};

void Particle::SetIndex(int index) {
  if (index >= 0 && index < fNParticleType) fIndex = index;
}

void Particle::SetIndex(char* name) {
  if (FindParticle(name) >= 0 && FindParticle(name) < fNParticleType)
    fIndex = FindParticle(name);
}

void Particle::PrintParticleTypes() {
  for (int i = 0; i < fMaxNumParticleType; ++i) {
    fParticleTypes[i]->Print();
  }
}

void Particle::Print() const {
  std::cout << "\n PARTICLE DATA \n\n -------------- \n\n"
            << " Index: " << std::setw(8) << fIndex
            << "\n Name: " << std::setw(8) << fParticleTypes[fIndex]->GetName()
            << "\n";
  fP.Print();
}

double Particle::GetPx() const { return fP.fPx; }

double Particle::GetPy() const { return fP.fPy; }

double Particle::GetPz() const { return fP.fPz; }

double Particle::GetMass() const { return fParticleTypes[fIndex]->GetMass(); }

double Particle::GetEnergy() const {
  return sqrt(GetMass() * GetMass() + fP.SquaredNorm());
}

double Particle::InvMass(Particle& p) const {
  double TotEnergy = GetEnergy() + p.GetEnergy();
  Impulse TotImpulse = fP + p.fP;

  return sqrt((TotEnergy * TotEnergy) - TotImpulse.SquaredNorm());
}

void Particle::SetP(double px, double py, double pz) {
  fP.fPx = px;
  fP.fPy = py;
  fP.fPz = pz;
}

void Particle::SetP(Impulse const& p) { fP = p; }

// Private Methods

int Particle::fNParticleType = 0;

int Particle::FindParticle(char* name) {
  int i{0};

  for (; i < fNParticleType; ++i) {
    if (fParticleTypes[i]->GetName() == name) {
      break;
    }
  }

  if (i != fMaxNumParticleType) {
    return i;
  } else {
    std::cout << "Particle not found \n";
    return fNParticleType;
  }
}

}  // namespace pt
