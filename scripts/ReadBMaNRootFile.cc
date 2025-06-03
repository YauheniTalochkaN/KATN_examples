#include <iostream>
#include <filesystem>
#include "TROOT.h"
#include "TFile.h"
#include "TString.h"
#include "TMath.h"
#include "TTree.h"


class BmnFieldPoint 
{
    public:
    BmnFieldPoint() {}
    ~BmnFieldPoint() {}
    BmnFieldPoint(Double_t x, Double_t y, Double_t z, Double_t bx, Double_t by, Double_t bz) 
    {
        fX = x;
        fY = y;
        fZ = z;
        fBx = bx;
        fBy = by;
        fBz = bz;
    }

    BmnFieldPoint& operator=(BmnFieldPoint& right) 
    {
        fX = right.GetX();
        fY = right.GetY();
        fZ = right.GetZ();
        fBx = right.GetBx();
        fBy = right.GetBy();
        fBz = right.GetBz();
        return *this;
    }

    Double_t GetX() { return fX; }
    Double_t GetY() { return fY; }
    Double_t GetZ() { return fZ; }
    Double_t GetBx() { return fBx; }
    Double_t GetBy() { return fBy; }
    Double_t GetBz() { return fBz; }

    private:
    // coordinates (mm)
    Double_t fX;
    Double_t fY;
    Double_t fZ;
    // magnetic field (Tm)
    Double_t fBx;
    Double_t fBy;
    Double_t fBz;
};


void ReadBMaNRootFile(TString name = "./data/FieldMap_1900_extrap.root")
{
    TFile *f = 0;
    f = new TFile(name, "update");

    BmnFieldPoint points;
    
    TTree *tout = (TTree*)f->Get("Field_map");

    tout->SetBranchAddress("field_points",&points);

    //std::filesystem::create_directories("./data");

    TString file_name = "./data/BMaN_data.csv";

    FILE *ff = fopen(file_name, "w");

    Int_t num = tout->GetEntries();
    for(Int_t i = 0; i < num; ++i)
    {
        tout->GetEntry(i, 1);

        fprintf(ff, "%.5e,%.5e,%.5e,%.5e,%.5e,%.5e", points.GetX(), points.GetY(), points.GetZ(), points.GetBx(), points.GetBy(), points.GetBz());
        if(i < num-1) fprintf(ff, "\n");
    }

    fclose(ff);	
    
    tout = nullptr;

    f->Close();
    f = nullptr;
}