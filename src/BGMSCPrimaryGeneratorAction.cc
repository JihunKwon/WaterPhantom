#include "BGMSCPrimaryGeneratorAction.hh"

#include "G4Proton.hh"
#include "G4Gamma.hh"
#include "G4Electron.hh"

using namespace CLHEP;

BGMSCPrimaryGeneratorAction::BGMSCPrimaryGeneratorAction()
{
//    CircleSource = new G4SingleParticleSource;
//    CircleSource->SetParticleDefinition(G4Gamma::Definition());

//    G4SPSEneDistribution* energy = CircleSource->GetEneDist();
//    energy->SetMonoEnergy(250*keV);

//    G4SPSPosDistribution* position = CircleSource->GetPosDist();
//    position->SetPosDisType("Plane");
//    position->SetPosDisShape("Circle");
//    position->SetRadius(50*mm);
//    position->SetCentreCoords(G4ThreeVector(0*m, 0*m, -201*mm));

//    G4SPSAngDistribution* angular = CircleSource->GetAngDist();
//    angular->SetParticleMomentumDirection(G4ThreeVector(0.0,0.0,1.0));
//    angular->DefineAngRefAxes("angref1", G4ThreeVector(-1.0,0.0,0.0));
//    CircleSource->SetNumberOfParticles(1);

    G4String fileName = "Varian_TrueBeam6MV_01";
    IAEAReader = new G4IAEAphspReader(fileName);

    G4ThreeVector isoPos(0*mm, 0*mm, -201*mm);
    IAEAReader->SetIsocenterPosition(isoPos);
    IAEAReader->SetTimesRecycled(0);
}

BGMSCPrimaryGeneratorAction::~BGMSCPrimaryGeneratorAction()
{
    if (IAEAReader)
        delete IAEAReader;
    //delete CircleSource;
}

void BGMSCPrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{
    //CircleSource->GeneratePrimaryVertex(event);
    IAEAReader->GeneratePrimaryVertex(event);
    std::vector<G4ThreeVector>* pos = IAEAReader->GetPositionVector();
    G4ThreeVector position = (*pos)[0];
    std::ofstream outfile;
}
