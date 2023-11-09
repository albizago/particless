#include <iostream>

#include "TF1.h"
#include "TFile.h"
#include "TH2D.h"
#include "TList.h"
#include "TMath.h"

void analyze_histos() {
  TFile* data_out = new TFile("data.txt", "recreate");
  TFile* histos_file = new TFile("histos.root", "read");
  TList* list = (TList*)histos_file->Get("list");
  bool compliance = true;
  TH1D* histo_ptr = nullptr;

  for (Int_t idx = 0; idx < 5; ++idx) {
    histo_ptr = (TH1D*)list->At(idx);
    compliance = (TMath::Nint(TMath::Log10(histo_ptr->Integral())) == 7);
    if (!compliance) break;
  }

  (compliance) ? std::cout << "Va bene" : std::cout << "Scossa";

  TH1I* type = (TH1I*)list->FindObject("type");

  (type->GetBinContent(0) - type->GetBinError(0) < 0.4 * 10e7 &&
   0.4 * 10e7 < type->GetBinContent(0) + type->GetBinError(0))
      ? std::cout << "Va bene"
      : std::cout << "Scossa";
  (type->GetBinContent(1) - type->GetBinError(1) < 0.4 * 10e7 &&
   0.4 * 10e7 < type->GetBinContent(1) + type->GetBinError(1))
      ? std::cout << "Va bene"
      : std::cout << "Scossa";

  (type->GetBinContent(2) - type->GetBinError(2) < 0.05 * 10e7 &&
   0.05 * 10e7 < type->GetBinContent(2) + type->GetBinError(2))
      ? std::cout << "Va bene"
      : std::cout << "Scossa";
  (type->GetBinContent(3) - type->GetBinError(3) < 0.05 * 10e7 &&
   0.05 * 10e7 < type->GetBinContent(3) + type->GetBinError(3))
      ? std::cout << "Va bene"
      : std::cout << "Scossa";
  (type->GetBinContent(4) - type->GetBinError(4) < 0.045 * 10e7 &&
   0.045 * 10e7 < type->GetBinContent(4) + type->GetBinError(4))
      ? std::cout << "Va bene"
      : std::cout << "Scossa";
  (type->GetBinContent(5) - type->GetBinError(5) < 0.045 * 10e7 &&
   0.045 * 10e7 < type->GetBinContent(5) + type->GetBinError(5))
      ? std::cout << "Va bene"
      : std::cout << "Scossa";
  (type->GetBinContent(6) - type->GetBinError(6) < 0.01 * 10e7 &&
   0.01 * 10e7 < type->GetBinContent(6) + type->GetBinError(6))
      ? std::cout << "Va bene"
      : std::cout << "Scossa";

  TH2D* angle_histo = (TH2D*)list->FindObject("angles");
  TF1* uniform_dist = new TF1("unif", "[0]", 0., 2 * TMath::Pi());
  angle_histo->ProjectionX()->Fit(uniform_dist, "q", "", 0., 2 * TMath::Pi());

  TF1* fit_func = angle_histo->GetFunction("unif");
  std::cout << "PHI FIT FUNCTION\n";
  std::cout << "Parameter: " << fit_func->GetParameter(0);
  std::cout << "Chi square: " << fit_func->GetChisquare();
  std::cout << "NDF: " << fit_func->GetNDF();
  std::cout << "Chi/NDF: " << fit_func->GetChisquare() / fit_func->GetNDF();
  std::cout << "Probability: " << fit_func->GetProb();

  uniform_dist->SetRange(0., TMath::Pi());
  angle_histo->ProjectionY()->Fit(uniform_dist, "q", "", 0., TMath::Pi());

  fit_func = angle_histo->GetFunction("unif");

  std::cout << "THETA FIT FUNCTION\n";
  std::cout << "Parameter: " << fit_func->GetParameter(0);
  std::cout << "Chi square: " << fit_func->GetChisquare();
  std::cout << "NDF: " << fit_func->GetNDF();
  std::cout << "Chi/NDF: " << fit_func->GetChisquare() / fit_func->GetNDF();
  std::cout << "Probability: " << fit_func->GetProb();

  TH1D* impulse_histo = (TH1D*)list->FindObject("impulse");

  TF1* exp_dist = new TF1("exp", "expo([0], [1])", 0., 30.);

  impulse_histo->Fit("exp", "q", "", 0., 30.);

  fit_func = impulse_histo->GetFunction("exp");

  std::cout << "IMPULSE FIT FUNCTION\n";
  std::cout << "Parameter 0: " << fit_func->GetParameter(0);
  std::cout << "Parameter 1: " << fit_func->GetParameter(1);
  std::cout << "Chi square: " << fit_func->GetChisquare();
  std::cout << "NDF: " << fit_func->GetNDF();
  std::cout << "Chi/NDF: " << fit_func->GetChisquare() / fit_func->GetNDF();
  std::cout << "Probability: " << fit_func->GetProb();

  (impulse_histo->GetMean() - impulse_histo->GetMeanError() < 1. &&
   1. < impulse_histo->GetMean() + impulse_histo->GetMeanError())
      ? std::cout << "Va bene lo stessoooo"
      : std::cout << "Problemi con exp";

    TH1D* disc_histo = (TH1D*)list->FindObject("inv_mass_disc");
    TH1D* conc_histo = (TH1D*)list->FindObject("inv_mass_conc");
    TH1D* disc_pk_histo = (TH1D*)list->FindObject("inv_mass_pk0");
    TH1D* conc_pk_histo = (TH1D*)list->FindObject("inv_mass_pk1");
    TH1D* kstar_histo = (TH1D*)list->FindObject("inv_mass_kstar");

    TH1D* diff1_histo = new TH1D(*disc_histo);
    diff1_histo->Add(disc_histo, conc_histo, 1., -1.);

    TH1D* diff2_histo = new TH1D(*disc_pk_histo);
    diff2_histo->Add(disc_pk_histo, conc_pk_histo, 1., -1.);

    TF1* gauss_dist = new TF1("gauss", "gaus([0], [1], [2])", 0., 1.5);

    gauss_dist->SetParameters(10, 0.8, 0.05);

    diff1_histo->Fit("gauss", "q", "", 0., 1.5);

    fit_func = diff1_histo->GetFunction("gauss");

    std::cout << "DIFFERENCE 1 FIT FUNCTION\n";
    std::cout << "Parameter 0: " << fit_func->GetParameter(0);
    std::cout << "Parameter 1: " << fit_func->GetParameter(1);
    std::cout << "Parameter 2: " << fit_func->GetParameter(2);
    std::cout << "Chi square: " << fit_func->GetChisquare();
    std::cout << "NDF: " << fit_func->GetNDF();
    std::cout << "Chi/NDF: " << fit_func->GetChisquare() / fit_func->GetNDF();
    std::cout << "Probability: " << fit_func->GetProb();

    diff2_histo->Fit("gauss", "q", "", 0., 1.5);

    fit_func = diff2_histo->GetFunction("gauss");

    std::cout << "DIFFERENCE 2 FIT FUNCTION\n";
    std::cout << "Parameter 0: " << fit_func->GetParameter(0);
    std::cout << "Parameter 1: " << fit_func->GetParameter(1);
    std::cout << "Parameter 2: " << fit_func->GetParameter(2);
    std::cout << "Chi square: " << fit_func->GetChisquare();
    std::cout << "NDF: " << fit_func->GetNDF();
    std::cout << "Chi/NDF: " << fit_func->GetChisquare() / fit_func->GetNDF();
    std::cout << "Probability: " << fit_func->GetProb();

    

}