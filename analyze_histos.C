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

void analyze_particle_type(TH1I* histo, TArrayD* prop_array) {
  std::cout << "Analysing particle types\n";
  Int_t n_types = prop_array->GetSize() - 1;
  Double_t n_generations = 100 * prop_array->At(n_types);

  for (Int_t i = 0; i < n_types; ++i) {
    std::cout << "Entries: " << histo->GetBinContent(i + 1) << " +- "
              << histo->GetBinError(i + 1) << '\n';
    ((histo->GetBinContent(i + 1) - histo->GetBinError(i + 1)) <
         prop_array->At(i) * n_generations &&
     prop_array->At(i) * n_generations <
         (histo->GetBinContent(i + 1) + histo->GetBinError(i + 1)))
        ? std::cout << "Expectation confirmed\n\n"
        : std::cout << "Something went wrong. Check visually\n\n";
  }
}

void analyze_histos() {
  TFile* histos_file = new TFile("histos.root", "read");
  TList* histos_list = histos_file->Get<TList>("list");

  TH1I* type = (TH1I*)histos_list->FindObject("type");
  TArrayD* proportions_array = histos_file->Get<TArrayD>("prop_arr");

  analyze_particle_type(type, proportions_array);

  TCanvas* canva_retrieved = new TCanvas(
      "canva_retrieved", "Types proportions, Impulse and Angles distributions",
      200, 10, 600, 400);
  canva_retrieved->Divide(2, 2);

  canva_retrieved->cd(1);
  type->GetYaxis()->SetTitle("Number of generated particles");
  type->GetXaxis()->SetTitle("Particle type");
  type->GetXaxis()->SetBinLabel(1, "Pions");

  type->Draw();

  canva_retrieved->cd(3);

  TF1* uniform_dist = new TF1("unif", "[0]", 0., 2 * TMath::Pi());

  TH1D* phi_histo = (TH1D*)histos_list->FindObject("phi");
  phi_histo->SetTitle("Azimuthal Angle Distribution");

  phi_histo->GetXaxis()->SetTitle("Azimuthal angle [rad]");
  phi_histo->GetYaxis()->SetTitle("Number of occurrencies");

  phi_histo->Fit(uniform_dist, "q", "", 0., 2 * TMath::Pi());

  std::cout << "\n AZIMUTHAL ANGLE PHI -- FIT FUNCTION\n";
  std::cout << "\n Parameter (normalization): " << uniform_dist->GetParameter(0)
            << " +- " << uniform_dist->GetParError(0);
  std::cout << "\n Chi square: " << uniform_dist->GetChisquare();
  std::cout << "\n NDF: " << uniform_dist->GetNDF();
  std::cout << "\n Chi/NDF: "
            << uniform_dist->GetChisquare() / uniform_dist->GetNDF();
  std::cout << "\n Probability: " << uniform_dist->GetProb();
  std::cout << "\n--------------------- \n\n";

  phi_histo->Draw();
  uniform_dist->Draw("SAME");

  uniform_dist->SetRange(0., TMath::Pi());

  canva_retrieved->cd(4);

  TH1D* theta_histo = (TH1D*)histos_list->FindObject("theta");
  theta_histo->SetTitle("Polar Angle Distribution");

  theta_histo->GetXaxis()->SetTitle("Polar angle [rad]");
  theta_histo->GetYaxis()->SetTitle("Number of occurrencies");

  theta_histo->Fit(uniform_dist, "q", "", 0., TMath::Pi());

  std::cout << "\n POLAR ANGLE THETA -- FIT FUNCTION\n";
  std::cout << "\n Parameter (normalization): " << uniform_dist->GetParameter(0)
            << " +- " << uniform_dist->GetParError(0);
  std::cout << "\n Chi square: " << uniform_dist->GetChisquare();
  std::cout << "\n NDF: " << uniform_dist->GetNDF();
  std::cout << "\n Chi/NDF: "
            << uniform_dist->GetChisquare() / uniform_dist->GetNDF();
  std::cout << "\n Probability: " << uniform_dist->GetProb() << '\n';
  std::cout << "\n--------------------- \n\n";

  theta_histo->Draw();
  uniform_dist->Draw("SAME");

  // Retrieving impulse histogram

  canva_retrieved->cd(2);

  TH1D* impulse_histo = (TH1D*)histos_list->FindObject("impulse");
  impulse_histo->SetTitle("Distribution of particles' impulse");

  impulse_histo->GetXaxis()->SetTitle("Impulse [GeV/c]");
  impulse_histo->GetYaxis()->SetTitle("Number of occurrencies");

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

  // K* RESONANCE

  // Retrieving invariant masses histograms

  TCanvas* canva_k_star =
      new TCanvas("canva_k_star", "K* Resonance Analysis", 200, 10, 600, 400);
  canva_k_star->Divide(1, 3);

  TH1D* disc_histo = (TH1D*)histos_list->FindObject("inv_mass_disc");
  TH1D* conc_histo = (TH1D*)histos_list->FindObject("inv_mass_conc");
  TH1D* disc_pk_histo = (TH1D*)histos_list->FindObject("inv_mass_pk0");
  TH1D* conc_pk_histo = (TH1D*)histos_list->FindObject("inv_mass_pk1");
  TH1D* kstar_histo = (TH1D*)histos_list->FindObject("inv_mass_kstar");

  histos_file->Close();

  canva_k_star->cd(1);

  // Difference between invariant masses of all particles of opposite charge and
  // all particles of same charge

  TH1D* diff1_histo = new TH1D(*disc_histo);
  diff1_histo->SetTitle(
      "Difference between distribution of invariant masses of all particles of "
      "opposite charge and all particles of same charge");
  diff1_histo->Add(disc_histo, conc_histo, 1., -1.);

  diff1_histo->GetXaxis()->SetTitle("Invariant mass [GeV/c^2]");
  diff1_histo->GetYaxis()->SetTitle("Number of occurrencies");

  TF1* gauss_dist = new TF1("gauss", "gaus([0], [1], [2])", 0., 7.);
  gauss_dist->SetParameters(0.5, 0.8, 0.05);

  diff1_histo->Fit("gauss", "q", "", 0., 7.);

  fit_func = diff1_histo->GetFunction("gauss");

  diff1_histo->Draw();
  fit_func->Draw("same");

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
  // std::cout << gauss_dist->Eval(0.88);

  // Difference between invariant masses of pions and kaons of opposite charges
  // and of same charges

  canva_k_star->cd(2);

  TH1D* diff2_histo = new TH1D(*disc_pk_histo);
  diff2_histo->SetTitle(
      "Difference between distribution of invariant masses "
      "of pions and kaons of opposite charges and of same "
      "charges");
  diff2_histo->Add(disc_pk_histo, conc_pk_histo, 1., -1.);

  diff2_histo->GetXaxis()->SetTitle("Invariant mass [GeV/c^2]");
  diff2_histo->GetYaxis()->SetTitle("Number of occurrencies");

  // Fitting with gaussian distribution

  diff2_histo->Fit("gauss", "q", "", 0., 7.);
  fit_func = diff2_histo->GetFunction("gauss");

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

  diff2_histo->Draw();
  fit_func->Draw("same");

  canva_k_star->cd(3);

  kstar_histo->GetXaxis()->SetTitle("Invariant mass [GeV/c^2]");
  kstar_histo->GetYaxis()->SetTitle("Number of occurrencies");

  kstar_histo->Fit("gauss", "q", "", 0., 2.);
  fit_func = kstar_histo->GetFunction("gauss");

  kstar_histo->Draw();
  fit_func->Draw("same");

  // Output files

  TFile* data_out_pdf = new TFile("data.pdf", "recreate");
  canva_retrieved->Write();
  canva_k_star->Write();

  data_out_pdf->Close();

  TFile* data_out_root = new TFile("data.root", "recreate");

  canva_retrieved->Write();
  canva_k_star->Write();

  data_out_root->Close();

  TFile* data_out_c = new TFile("data.C", "recreate");

  canva_retrieved->Write();
  canva_k_star->Write();

  data_out_c->Close();
}