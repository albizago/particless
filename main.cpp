#include <array>

#include "TApplication.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TH1I.h"
#include "TH2D.h"
#include "TList.h"
#include "TMath.h"
#include "TROOT.h"
#include "TRandom.h"
#include "TArray.h"
#include "particle.hpp"

int main(int argc, char** argv) {
  TApplication app("ROOT Application", &argc, argv);

  std::cout << "Particle Types generation" << '\n';

  pt::Particle::AddParticleType("pion+", 0.13957, 1);
  pt::Particle::AddParticleType("pion-", 0.13957, -1);
  pt::Particle::AddParticleType("kaon+", 0.49367, 1);
  pt::Particle::AddParticleType("kaon-", 0.49367, -1);
  pt::Particle::AddParticleType("proton+", 0.93827, 1);
  pt::Particle::AddParticleType("proton-", 0.93827, -1);
  pt::Particle::AddParticleType("k*", 0.89166, 0, 0.05);

  gRandom->SetSeed();

  std::array<pt::Particle, 130> EventParticles;

  std::cout << " Histogram generation" << '\n';

  // Histo containing the proportions of generated particle TYPES
  TH1I* type_histo = new TH1I("type", "Types of generated particles", 7, 0, 7);

  // 2D Histo containing particle's momentum directions
  TH2D* angle_histo =
      new TH2D("angles", "Azimutal and polar angles of momentum", 360, 0.,
               2 * TMath::Pi(), 180, 0., TMath::Pi());

  // Histo containing momentum modules
  TH1D* impulse_histo = new TH1D("impulse", "Module of momentum", 1000, 0, 30);

  // Histo containing tranverse impulse
  TH1D* transv_impulse_histo =
      new TH1D("t_impulse", "Tranverse impulse", 1000, 0, 30);

  // Histo containing energy of particles
  TH1D* energy_histo =
      new TH1D("energy", "Energy of generated particles", 1000, 0, 50);

  // Histo containing invariant mass of all particles of opposite sign charges
  TH1D* inv_mass_disc_histo =
      new TH1D("inv_mass_disc",
               "Invariant mass of oppositely charged particles", 1000, 0, 1.5);
  inv_mass_disc_histo->Sumw2();

  // Histo containing invariant mass of all particles of same sign charges
  TH1D* inv_mass_conc_histo =
      new TH1D("inv_mass_conc",
               "Invariant mass of identically charged particles", 1000, 0, 1.5);
  inv_mass_conc_histo->Sumw2();

  // Histo containing invariant mass of opposite charge pions and kaons
  TH1D* inv_mass_pk0_histo =
      new TH1D("inv_mass_pk0", "Invariant mass of pi+k- / pi-k+", 1000, 0, 1.5);
  inv_mass_pk0_histo->Sumw2();

  // Histo containing invariant mass of same charge pions and kaons
  TH1D* inv_mass_pk1_histo =
      new TH1D("inv_mass_pk1", "Invariant mass of pi+k+ / pi-k-", 1000, 0, 1.5);
  inv_mass_pk1_histo->Sumw2();

  // Histo containing invariant mass of products of k* decays
  TH1D* inv_mass_kstar_histo = new TH1D(
      "inv_mass_kstar", "Invariant mass of products of K* decay", 1000, 0, 1.5);
  inv_mass_kstar_histo->Sumw2();

  Double_t phi;
  Double_t theta;
  Double_t p_mod;  // modulus
  Impulse p_gen;   // vector

  Double_t rndm_idx;

  std::cout << "Event generation" << '\n';

  for (Int_t i = 0; i < 10000; ++i) {
    Int_t decay_idx = 0;
    for (Int_t j = 0; j < 100; ++j) {
      // random polar variables
      phi = gRandom->Uniform(0., 2 * TMath::Pi());
      theta = gRandom->Uniform(0., TMath::Pi());
      p_mod = gRandom->Exp(1.);
      p_gen.fPx = p_mod * TMath::Sin(theta) * TMath::Cos(phi);
      p_gen.fPy = p_mod * TMath::Sin(theta) * TMath::Sin(phi);
      p_gen.fPz = p_mod * TMath::Cos(theta);

      // fill histos
      angle_histo->Fill(phi, theta);
      impulse_histo->Fill(p_mod);
      transv_impulse_histo->Fill(
          TMath::Sqrt(p_gen.fPx * p_gen.fPx + p_gen.fPy * p_gen.fPy));

      rndm_idx = gRandom->Rndm();

    TArrayD* prop_arr = new TArrayD(7);
    prop_arr->SetAt(0.4, 0);
    prop_arr->SetAt(0.4, 1);
    prop_arr->SetAt(0.05, 2);
    prop_arr->SetAt(0.05, 3);
    prop_arr->SetAt(0.045, 4);
    prop_arr->SetAt(0.045, 5);
    prop_arr->SetAt(0.01, 6);

      // random type assignment
      if (rndm_idx < 0.4) {
        EventParticles[j].SetIndex("pion+");
        EventParticles[j].SetP(p_gen);
      } else if (rndm_idx < 0.8) {
        EventParticles[j].SetIndex("pion-");
        EventParticles[j].SetP(p_gen);
      } else if (rndm_idx < 0.85) {
        EventParticles[j].SetIndex("kaon+");
        EventParticles[j].SetP(p_gen);
      } else if (rndm_idx < 0.9) {
        EventParticles[j].SetIndex("kaon-");
        EventParticles[j].SetP(p_gen);
      } else if (rndm_idx < 0.945) {
        EventParticles[j].SetIndex("proton+");
        EventParticles[j].SetP(p_gen);
      } else if (rndm_idx < 0.99) {
        EventParticles[j].SetIndex("proton-");
        EventParticles[j].SetP(p_gen);
      } else {
        EventParticles[j].SetIndex("k*");
        EventParticles[j].SetP(p_gen);
        rndm_idx = gRandom->Rndm();

        if (rndm_idx < 0.5) {
          EventParticles[100 + decay_idx].SetIndex("pion+");
          EventParticles[101 + decay_idx].SetIndex("kaon-");
          EventParticles[j].Decay2body(EventParticles[100 + decay_idx],
                                       EventParticles[101 + decay_idx]);
        } else {
          EventParticles[100 + decay_idx].SetIndex("pion-");
          EventParticles[101 + decay_idx].SetIndex("kaon+");
          EventParticles[j].Decay2body(EventParticles[100 + decay_idx],
                                       EventParticles[101 + decay_idx]);
        }

        inv_mass_kstar_histo->Fill(EventParticles[100 + decay_idx].InvMass(
            EventParticles[101 + decay_idx]));
        decay_idx += 2;
      }

      // fill type, energy
      type_histo->Fill(EventParticles[j].GetIndex());
      energy_histo->Fill(EventParticles[j].GetEnergy());
    }

    // fill invariant mass histos for opposite / same charge
    for (Int_t a = 0; a < 100 + decay_idx; ++a) {
      for (Int_t b = a + 1; b < 100 + decay_idx; ++b) {
        if (EventParticles[a].GetCharge() * EventParticles[b].GetCharge() < 0) {
          // Fill histo of pions and kaons with opposite charges
          if (EventParticles[a].GetMass() + EventParticles[b].GetMass() <
                  0.633245 &&
              EventParticles[a].GetMass() + EventParticles[b].GetMass() >
                  0.633235) {
            inv_mass_pk0_histo->Fill(
                EventParticles[a].InvMass(EventParticles[b]));
          }

          // Fill histo of invariant mass of opposite sign charges
          inv_mass_disc_histo->Fill(
              EventParticles[a].InvMass(EventParticles[b]));

        } else if (EventParticles[a].GetCharge() *
                       EventParticles[b].GetCharge() >
                   0) {
          if (EventParticles[a].GetMass() + EventParticles[b].GetMass() <
                  0.633245 &&
              EventParticles[a].GetMass() + EventParticles[b].GetMass() >
                  0.633235) {
            // Fill histo of pions and kaons with same charges
            inv_mass_pk1_histo->Fill(
                EventParticles[a].InvMass(EventParticles[b]));
          }
          // Fill histo of invariant mass of same sign charges
          inv_mass_conc_histo->Fill(
              EventParticles[a].InvMass(EventParticles[b]));
        }
      }
    }
  }

  std::cout << "Histos filled" << '\n';

  TList* list = new TList();
  list->Add(type_histo);
  list->Add(angle_histo);
  list->Add(impulse_histo);
  list->Add(transv_impulse_histo);
  list->Add(energy_histo);
  list->Add(inv_mass_disc_histo);
  list->Add(inv_mass_conc_histo);
  list->Add(inv_mass_pk0_histo);
  list->Add(inv_mass_pk1_histo);
  list->Add(inv_mass_kstar_histo);

  TCanvas* canva = new TCanvas("canva", "histo_tot", 200, 10, 600, 400);
  canva->Divide(2, 5);

  std::cout << "Canva created" << '\n';

  for (Int_t canva_idx = 1; canva_idx <= 10; ++canva_idx) {
    canva->cd(canva_idx);
    list->At(canva_idx - 1)->Draw();
  }

  std::cout << "Histos drawn" << '\n';

  TFile* file = new TFile("histos.root", "RECREATE");

  list->Write();
  canva->Write();

  file->Close();

  std::cout << "Histos written to file '' histos.root '' " << '\n';

  app.Run();
  return 0;
}