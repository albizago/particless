#include <iostream>

#include "TCanvas.h"
#include "TF1.h"
#include "TFile.h"
#include "TH2D.h"
#include "TList.h"
#include "TMath.h"
#include "TROOT.h"
#include "TStyle.h"

void setStyle() {
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(57);
  gStyle->SetOptTitle(0);
}

void analyze_particle_type(TH1I* histo) {
  std::cout << "Analysing particle types\n";
  std::cout << "Entries: " << histo->GetBinContent(1) << " +- "
            << histo->GetBinError(1) << '\n';
  ((histo->GetBinContent(1) - histo->GetBinError(1)) < 0.4 * 1.e7 &&
   0.4 * 1.e7 < (histo->GetBinContent(1) + histo->GetBinError(1)))
      ? std::cout << "Va bene\n\n"
      : std::cout << "Scossa\n\n";

  std::cout << "Entries: " << histo->GetBinContent(2) << " +- "
            << histo->GetBinError(2) << '\n';
  ((histo->GetBinContent(2) - histo->GetBinError(2)) < 0.4 * 1.e7 &&
   0.4 * 1.e7 < (histo->GetBinContent(2) + histo->GetBinError(2)))
      ? std::cout << "Va bene\n\n"
      : std::cout << "Scossa\n\n";

  std::cout << "Entries: " << histo->GetBinContent(3) << " +- "
            << histo->GetBinError(3) << '\n';
  (histo->GetBinContent(3) - histo->GetBinError(3) < 0.05 * 1.e7 &&
   0.05 * 1.e7 < histo->GetBinContent(3) + histo->GetBinError(3))
      ? std::cout << "Va bene\n\n"
      : std::cout << "Scossa\n\n";

  std::cout << "Entries: " << histo->GetBinContent(4) << " +- "
            << histo->GetBinError(4) << '\n';
  (histo->GetBinContent(4) - histo->GetBinError(4) < 0.05 * 1.e7 &&
   0.05 * 1.e7 < histo->GetBinContent(4) + histo->GetBinError(4))
      ? std::cout << "Va bene\n\n"
      : std::cout << "Scossa\n\n";

  std::cout << "Entries: " << histo->GetBinContent(5) << " +- "
            << histo->GetBinError(5) << '\n';
  (histo->GetBinContent(5) - histo->GetBinError(5) < 0.045 * 1.e7 &&
   0.045 * 1.e7 < histo->GetBinContent(5) + histo->GetBinError(5))
      ? std::cout << "Va bene\n\n"
      : std::cout << "Scossa\n\n";

  std::cout << "Entries: " << histo->GetBinContent(6) << " +- "
            << histo->GetBinError(6) << '\n';
  (histo->GetBinContent(6) - histo->GetBinError(6) < 0.045 * 1.e7 &&
   0.045 * 1.e7 < histo->GetBinContent(6) + histo->GetBinError(6))
      ? std::cout << "Va bene\n\n"
      : std::cout << "Scossa\n\n";

  std::cout << "Entries: " << histo->GetBinContent(7) << " +- "
            << histo->GetBinError(7) << '\n';
  (histo->GetBinContent(7) - histo->GetBinError(7) < 0.01 * 1.e7 &&
   0.01 * 1.e7 < histo->GetBinContent(7) + histo->GetBinError(7))
      ? std::cout << "Va bene\n\n"
      : std::cout << "Scossa\n\n";
}

void analyze_histos() {
  TFile* histos_file = new TFile("histos.root", "read");
  bool compliance = true;
  TH1D* histo_ptr = nullptr;

  TH1I* type = histos_file->Get<TH1I>("type");

  analyze_particle_type(type);

  TCanvas* canva_angle =
      new TCanvas("canva_angle", "histo_angles", 200, 10, 600, 400);
  canva_angle->Divide(1, 2);
  canva_angle->cd(1);

  //TH2D* angle_histo = histos_file->Get<TH2D>("angles");
  TF1* uniform_dist = new TF1("unif", "[0]", 0., 2 * TMath::Pi());

  //angle_histo->ProjectionX()->Fit(uniform_dist, "q", "", 0., 2 * TMath::Pi());

  TH1D* phi_histo = histos_file->Get<TH1D>("phi");

  phi_histo->Fit(uniform_dist, "q", "", 0., 2 * TMath::Pi());

  std::cout << "\n AZIMUTHAL ANGLE PHI -- FIT FUNCTION\n";
  std::cout << "\n Parameter (normalization): " << uniform_dist->GetParameter(0)
            << " +- " << uniform_dist->GetParError(0);
  std::cout << "\n Chi square: " << uniform_dist->GetChisquare();
  std::cout << "\n NDF: " << uniform_dist->GetNDF();
  std::cout << "\n Chi/NDF: "
            << uniform_dist->GetChisquare() / uniform_dist->GetNDF();
  std::cout << "\n Probability: " << uniform_dist->GetProb();
  std::cout << "--------------------- \n\n";

  //angle_histo->ProjectionX()->Draw();
  phi_histo->Draw();
  uniform_dist->DrawCopy("SAME");
  canva_angle->cd(2);

  uniform_dist->SetRange(0., TMath::Pi());
  //angle_histo->ProjectionY()->Fit(uniform_dist, "q", "", 0., TMath::Pi());
  
  TH1D* theta_histo = histos_file->Get<TH1D>("theta");

  theta_histo->Fit(uniform_dist, "q", "", 0., TMath::Pi());

  std::cout << "\n POLAR ANGLE THETA -- FIT FUNCTION\n";
  std::cout << "\n Parameter (normalization): " << uniform_dist->GetParameter(0)
            << " +- " << uniform_dist->GetParError(0);
  std::cout << "\n Chi square: " << uniform_dist->GetChisquare();
  std::cout << "\n NDF: " << uniform_dist->GetNDF();
  std::cout << "\n Chi/NDF: "
            << uniform_dist->GetChisquare() / uniform_dist->GetNDF();
  std::cout << "\n Probability: " << uniform_dist->GetProb() << '\n';
  std::cout << "--------------------- \n\n";

  //angle_histo->ProjectionY()->Draw();
  theta_histo->Draw();
  uniform_dist->DrawCopy("SAME");

  // Retrieving impulse histogram

  TCanvas* canva_impulse =
      new TCanvas("canva_mpulse", "impulse_angles", 200, 10, 600, 400);
  canva_impulse->cd();

  TH1D* impulse_histo = histos_file->Get<TH1D>("impulse");
  TF1* exp_dist = new TF1("exp", "expo([0], [1])", 0., 30.);

  impulse_histo->Fit("exp", "q", "", 0., 30.);

  TF1* fit_func = impulse_histo->GetFunction("exp");

  std::cout << "\n IMPULSE -- FIT FUNCTION\n";
  std::cout << "\n Parameter 0 (normalization): " << fit_func->GetParameter(0)
            << " +- " << fit_func->GetParError(0);
  std::cout << "\n Parameter 1 (average): " << fit_func->GetParameter(1)
            << " +- " << fit_func->GetParError(1);
  std::cout << "\n Chi square: " << fit_func->GetChisquare();
  std::cout << "\n NDF: " << fit_func->GetNDF();
  std::cout << "\n Chi/NDF: " << fit_func->GetChisquare() / fit_func->GetNDF();
  std::cout << "\n Probability: " << fit_func->GetProb() << '\n';
  std::cout << "--------------------- \n\n";

  (impulse_histo->GetMean() - impulse_histo->GetMeanError() < 1. &&
   1. < impulse_histo->GetMean() + impulse_histo->GetMeanError())
      ? std::cout << "\n Va bene lo stessoooo \n"
      : std::cout << "\n Problemi con exp \n";

  impulse_histo->Draw();
  fit_func->Draw("SAME");

  // Retrieving invariant masses histograms

  TH1D* disc_histo = histos_file->Get<TH1D>("inv_mass_disc");
  TH1D* conc_histo = histos_file->Get<TH1D>("inv_mass_conc");
  TH1D* disc_pk_histo = histos_file->Get<TH1D>("inv_mass_pk0");
  TH1D* conc_pk_histo = histos_file->Get<TH1D>("inv_mass_pk1");
  TH1D* kstar_histo = histos_file->Get<TH1D>("inv_mass_kstar");

  TCanvas* canva = new TCanvas("canva", "histo_tot", 200, 10, 600, 400);
  canva->Divide(1, 2);
  canva->cd(1);

  // Difference between invariant masses of all particles of opposite charge and
  // all particles of same charge

  TH1D* diff1_histo = new TH1D(*disc_histo);
  diff1_histo->Sumw2();
  diff1_histo->Add(disc_histo, conc_histo, 1., -1.);

  diff1_histo->Draw();
  canva->cd(2);

  // Difference between invariant masses of pions and kaons of opposite charges
  // and of same charges

  TH1D* diff2_histo = new TH1D(*disc_pk_histo);
  diff2_histo->Sumw2();
  diff2_histo->Add(disc_pk_histo, conc_pk_histo, 1., -1.);

  diff2_histo->Draw();
  canva->cd(1);

  // Fitting with gaussian distribution

  TF1* gauss_dist = new TF1("gauss", "gaus([0], [1], [2])", 0., 3.);
  gauss_dist->SetParameters(0.5, 0.8, 0.05);

  diff1_histo->Fit("gauss", "q", "", 0., 3.);

  fit_func = diff1_histo->GetFunction("gauss");
  fit_func->Draw("same");
  canva->cd(2);

  std::cout << "\n ALL PARTICLES DIFFERENCE -- GAUSSIAN FIT FUNCTION\n";
  std::cout << "\n Parameter 0: " << fit_func->GetParameter(0) << " +- "
            << fit_func->GetParError(0);
  std::cout << "\n Parameter 1 (average): " << fit_func->GetParameter(1)
            << " +- " << fit_func->GetParError(1);
  std::cout << "\n Parameter 2 (RMS): " << fit_func->GetParameter(2) << " +- "
            << fit_func->GetParError(2);
  std::cout << "\n Chi square: " << fit_func->GetChisquare();
  std::cout << "\n NDF: " << fit_func->GetNDF();
  std::cout << "\n Chi/NDF: " << fit_func->GetChisquare() / fit_func->GetNDF();
  std::cout << "\n Probability: " << fit_func->GetProb() << '\n';
  std::cout << "--------------------- \n\n";
  //std::cout << gauss_dist->Eval(0.88);

  diff2_histo->Fit("gauss", "q", "", 0., 3.);

  fit_func = diff2_histo->GetFunction("gauss");
  fit_func->Draw("same");

  std::cout << "\n PIONS & KAONS DIFFERENCE -- GAUSSIAN FIT FUNCTION\n";
  std::cout << "\n Parameter 0: " << fit_func->GetParameter(0) << " +- "
            << fit_func->GetParError(0);
  std::cout << "\n Parameter 1 (average): " << fit_func->GetParameter(1)
            << " +- " << fit_func->GetParError(1);
  std::cout << "\n Parameter 2 (RMS): " << fit_func->GetParameter(2) << " +- "
            << fit_func->GetParError(2);
  std::cout << "\n Chi square: " << fit_func->GetChisquare();
  std::cout << "\n NDF: " << fit_func->GetNDF();
  std::cout << "\n Chi/NDF: " << fit_func->GetChisquare() / fit_func->GetNDF();
  std::cout << "\n Probability: " << fit_func->GetProb() << '\n';
  std::cout << "--------------------- \n\n";

  // TFile* data_out = new TFile("data.txt", "recreate");
}