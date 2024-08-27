//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file B1/src/DetectorConstruction.cc
/// \brief Implementation of the B1::DetectorConstruction class

#include "DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

namespace B1
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  G4NistManager* nist = G4NistManager::Instance();
  
  // Elements
  G4Element* elTi = nist->FindOrBuildElement("Ti");
  G4Element* elH = nist->FindOrBuildElement("H");

  // Define Tritium (H-3)
  G4Isotope* isoH3 = new G4Isotope("Tritium", 1, 3, 3.0160492*g/mole);
  G4Element* elT = new G4Element("Tritium", "T", 1);
  elT->AddIsotope(isoH3, 100*perCent);

  // Titanium Tritide (TiTr)
  G4Material* TiTr = new G4Material("TiTr", 4.506*g/cm3, 2);
  TiTr->AddElement(elTi, 1);
  TiTr->AddElement(elT, 1);

  // Define Vacuum
  G4Material* vacuum = new G4Material("Galactic", 1., 1.01*g/mole, CLHEP::universe_mean_density,
                                      kStateGas, 2.73*kelvin, 3.e-18*pascal);

  // World volume
  G4double world_size = 1.0*m;
  G4Material* world_mat = vacuum;  // Use vacuum as the world material

  G4Box* solidWorld = new G4Box("World", world_size/2, world_size/2, world_size/2);
  G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, world_mat, "World");
  G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "World", 0, false, 0, true);

  // Target volume (TiTr plate)
  G4double target_sizeXY = 10.0*cm;
  G4double target_thickness = 1.0*mm;

  G4Box* solidTarget = new G4Box("Target", target_sizeXY/2, target_sizeXY/2, target_thickness/2);
  G4LogicalVolume* logicTarget = new G4LogicalVolume(solidTarget, TiTr, "Target");
  new G4PVPlacement(0, G4ThreeVector(0, 0, 0), logicTarget, "Target", logicWorld, false, 0, true);

  // Set the scoring volume to be the target volume
  fScoringVolume = logicTarget;

  return physWorld;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
}
