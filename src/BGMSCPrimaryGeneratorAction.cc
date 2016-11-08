#include "BGMSCPrimaryGeneratorAction.hh"

#include "G4Proton.hh"
#include "G4Gamma.hh"
#include "G4Electron.hh"

using namespace CLHEP;

BGMSCPrimaryGeneratorAction::BGMSCPrimaryGeneratorAction()
{
    CircleSource = new G4SingleParticleSource;
    CircleSource->SetParticleDefinition(G4Gamma::Definition());

    G4SPSEneDistribution* energy = CircleSource->GetEneDist();
    energy->SetMonoEnergy(250*keV);

    G4SPSPosDistribution* position = CircleSource->GetPosDist();
    position->SetPosDisType("Plane");
    position->SetPosDisShape("Circle");
    position->SetRadius(50*mm);
    position->SetCentreCoords(G4ThreeVector(0*m, 0*m, -201*mm));

    G4SPSAngDistribution* angular = CircleSource->GetAngDist();
    angular->SetParticleMomentumDirection(G4ThreeVector(0.0,0.0,1.0));
    angular->DefineAngRefAxes("angref1", G4ThreeVector(-1.0,0.0,0.0));
    CircleSource->SetNumberOfParticles(1);
}

BGMSCPrimaryGeneratorAction::~BGMSCPrimaryGeneratorAction()
{
    delete CircleSource;
}

void BGMSCPrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{
    CircleSource->GeneratePrimaryVertex(event);
}
