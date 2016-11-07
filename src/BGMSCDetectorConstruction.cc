#include "BGMSCDetectorConstruction.hh"

#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4NistManager.hh"
#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"
#include "G4VisAttributes.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4RunManager.hh"
#include "G4VSolid.hh"
#include "G4Sphere.hh"
#include "G4UserLimits.hh"

using namespace CLHEP;

BGMSCDetectorConstruction::BGMSCDetectorConstruction()
    :fStepLimit(NULL)
{}

//BGMSCDetectorConstruction::~BGMSCDetectorConstruction()
//{
//  delete fStepLimit;
//}

G4VPhysicalVolume* BGMSCDetectorConstruction::Construct()
{
    // Cleanup old geometry
    G4GeometryManager::GetInstance()->OpenGeometry();
    G4PhysicalVolumeStore::GetInstance()->Clean();
    G4LogicalVolumeStore::GetInstance()->Clean();
    G4SolidStore::GetInstance()->Clean();

    G4VisAttributes* visAttributes = new G4VisAttributes;
    visAttributes->SetForceWireframe(true);
    visAttributes->SetForceAuxEdgeVisible(true);

    G4NistManager* nistManager = G4NistManager::Instance();
    G4Material* Au = nistManager->FindOrBuildMaterial("G4_Au");
    G4Material* vacuum = nistManager->FindOrBuildMaterial("G4_Galactic");
    G4Material* water = nistManager->FindOrBuildMaterial("G4_WATER");

    // World
    G4Box* world = new G4Box("World", 40*cm, 40*cm, 40*cm);   //halfx=0.05um
    G4LogicalVolume *worldLogic = new G4LogicalVolume(world, vacuum, "WorldLogic");
    G4VPhysicalVolume *worldPhys = new G4PVPlacement(0, G4ThreeVector(), worldLogic, "WorldPhys", 0, false, 0);
    worldLogic->SetVisAttributes(visAttributes);

//    G4Sphere *nanoPart = new G4Sphere("NanoPart", 0, 10*nm, 0*deg, 360*deg, 0*deg, 180*deg);
//    G4LogicalVolume *nanoPartLogic = new G4LogicalVolume(nanoPart, Au, "NanoPartLogic");
//    new G4PVPlacement(0, G4ThreeVector(0, 0, 0), nanoPartLogic, "NanoPartPhys", worldLogic, 0, 0);
//    nanoPartLogic->SetVisAttributes(visAttributes);

    G4Box* phantomSolid = new G4Box("PhatomSolid", 10*cm, 10*cm, 20*cm);
    G4LogicalVolume *phantomLogic = new G4LogicalVolume(phantomSolid, water, "PhantomLogic");
    G4VPhysicalVolume *phantomPhys = new G4PVPlacement(0, G4ThreeVector(0, 0, 0), phantomLogic, "phantomPhys", worldLogic, false, 0);

    G4double maxStep = 1*mm;
    fStepLimit = new G4UserLimits(maxStep);
    phantomLogic->SetUserLimits(fStepLimit);

    return worldPhys;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void BGMSCDetectorConstruction::SetMaxStep(G4double maxStep)
{
    if ((fStepLimit)&&(maxStep>0.)) fStepLimit->SetMaxAllowedStep(maxStep);
}
