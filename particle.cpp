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

// --------------- PUBLIC METHODS ---------------

// parametric constructor
Particle::Particle(std::string const& name, Impulse P)
    : fIndex(FindParticle(name)), fP(P) {
  if (fIndex == fNParticleType)
    throw std::runtime_error{" Particle not found \n\n"};
}

// getters
int Particle::GetIndex() const { return fIndex; }

double Particle::GetPx() const { return fP.fPx; }

double Particle::GetPy() const { return fP.fPy; }

double Particle::GetPz() const { return fP.fPz; }

double Particle::GetCharge() const {
  return fParticleTypes[fIndex]->GetCharge();
}

double Particle::GetMass() const { return fParticleTypes[fIndex]->GetMass(); }

double Particle::GetEnergy() const {
  return sqrt(GetMass() * GetMass() + fP.SquaredNorm());
}

// setters
void Particle::SetIndex(int index) {
  if (index >= 0 && index < fNParticleType) fIndex = index;
}

void Particle::SetIndex(std::string const& name) {
  if (FindParticle(name) >= 0 && FindParticle(name) < fNParticleType)
    fIndex = FindParticle(name);
}

void Particle::SetP(double px, double py, double pz) {
  fP.fPx = px;
  fP.fPy = py;
  fP.fPz = pz;
}

void Particle::SetP(Impulse const& p) { fP = p; }

// add new particle / resonance type
void Particle::AddParticleType(std::string const& name, double mass, int charge,
                               double width) {
  // check if particle already exists, proceed if not
  // and array size limit not reached
  if (FindParticle(name) == fNParticleType &&
      FindParticle(name) < fMaxNumParticleType) {
    // add particle or resonance type, depending on width value
    if (width == 0.) {
      // pass the ownership of new ParticleType object
      fParticleTypes[FindParticle(name)] = std::move(
          std::unique_ptr<ParticleType>(new ParticleType(name, mass, charge)));
    } else {
      // pass the ownership of new ResonanceType object
      fParticleTypes[FindParticle(name)] =
          std::move(std::unique_ptr<ParticleType>(
              new ResonanceType(name, mass, charge, width)));
    }
    // increment number of current particle types
    ++fNParticleType;
  } else if (FindParticle(name) == fMaxNumParticleType) {
    throw std::runtime_error{" Array size limit reached \n\n"};
  } else {
    std::cout << " Particle already exists \n\n";
  }
};

// compute invariant mass of two particles
double Particle::InvMass(const Particle& other) const {
  double TotEnergy = GetEnergy() + other.GetEnergy();
  Impulse TotImpulse = fP + other.fP;

  // apply SR formula
  return sqrt((TotEnergy * TotEnergy) - TotImpulse.SquaredNorm());
}

// simulate decay of a particle into two daughters
int Particle::Decay2body(Particle& dau1, Particle& dau2) const {
  if (GetMass() == 0.0) {
    std::cout << "Decayment cannot be preformed if mass is zero\n";
    return 1;
  }

  double massMot = GetMass();
  double massDau1 = dau1.GetMass();
  double massDau2 = dau2.GetMass();

  if (fIndex > -1) {  // add width effect

    // gaussian random numbers

    float x1, x2, w, y1;

    double invnum = 1. / RAND_MAX;
    do {
      x1 = 2.0 * rand() * invnum - 1.0;
      x2 = 2.0 * rand() * invnum - 1.0;
      w = x1 * x1 + x2 * x2;
    } while (w >= 1.0);

    w = sqrt((-2.0 * log(w)) / w);
    y1 = x1 * w;

    massMot += fParticleTypes[fIndex]->GetWidth() * y1;
  }

  if (massMot < massDau1 + massDau2) {
    std::cout << "Decayment cannot be preformed because mass is too low in "
                 "this channel\n";
    return 2;
  }

  double pout =
      sqrt(
          (massMot * massMot - (massDau1 + massDau2) * (massDau1 + massDau2)) *
          (massMot * massMot - (massDau1 - massDau2) * (massDau1 - massDau2))) /
      massMot * 0.5;

  double norm = 2 * M_PI / RAND_MAX;

  double phi = rand() * norm;
  double theta = rand() * norm * 0.5 - M_PI / 2.;
  dau1.SetP(pout * sin(theta) * cos(phi), pout * sin(theta) * sin(phi),
            pout * cos(theta));
  dau2.SetP(-pout * sin(theta) * cos(phi), -pout * sin(theta) * sin(phi),
            -pout * cos(theta));

  double energy = sqrt(fP.SquaredNorm() + massMot * massMot);

  double bx = fP.fPx / energy;
  double by = fP.fPy / energy;
  double bz = fP.fPz / energy;

  dau1.Boost(bx, by, bz);
  dau2.Boost(bx, by, bz);

  return 0;
}


// print methods
void Particle::PrintParticleTypes() {
  for (int i = 0; i < fNParticleType; ++i) {
    fParticleTypes[i]->Print();
  }
  std::cout << '\n';
}

void Particle::Print() const {
  std::cout << "\n PARTICLE DATA \n\n -------------- \n\n"
            << " Index: " << std::setw(8) << fIndex
            << "\n Name: " << std::setw(8) << fParticleTypes[fIndex]->GetName()
            << "\n\n -------------- \n";
  fP.Print();
}

// --------------- STATIC MEMBERS ---------------

const int Particle::fMaxNumParticleType = 10;
int Particle::fNParticleType = 0;

std::unique_ptr<std::unique_ptr<ParticleType>[]> Particle::fParticleTypes =
    std::make_unique<std::unique_ptr<ParticleType>[]>(
        Particle::fMaxNumParticleType);

// --------------- PRIVATE METHODS ---------------

// find particle type index
int Particle::FindParticle(std::string const& name) {
  int i{0};

  for (; i < fNParticleType; ++i) {
    if (fParticleTypes[i]->GetName() == name) {
      break;
    }
  }

  if (i != fNParticleType) {
    return i;
  } else {
    // std::cout << "Particle not found \n";
    return fNParticleType;
  }
}

// apply Lorentz transformation
void Particle::Boost(double bx, double by, double bz) {
  double energy = GetEnergy();

  double b2 = bx * bx + by * by + bz * bz;
  double gamma = 1.0 / sqrt(1.0 - b2);
  double bp = bx * fP.fPx + by * fP.fPy + bz * fP.fPz;
  double gamma2 = b2 > 0 ? (gamma - 1.0) / b2 : 0.0;

  fP.fPx += gamma2 * bp * bx + gamma * bx * energy;
  fP.fPy += gamma2 * bp * by + gamma * by * energy;
  fP.fPz += gamma2 * bp * bz + gamma * bz * energy;
}

}  // namespace pt
