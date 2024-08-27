#include "SteppingAction.hh"
#include "EventAction.hh"
#include "DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Track.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTable.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"  // Include CLHEP units

namespace B1
{

SteppingAction::SteppingAction(EventAction* eventAction)
: fEventAction(eventAction)
{}

void SteppingAction::UserSteppingAction(const G4Step* step)
{
  if (!fScoringVolume) {
      const auto detConstruction = static_cast<const DetectorConstruction*>(
          G4RunManager::GetRunManager()->GetUserDetectorConstruction());
      fScoringVolume = detConstruction->GetScoringVolume();
  }

  G4LogicalVolume* volume = step->GetPreStepPoint()->GetTouchableHandle()
      ->GetVolume()->GetLogicalVolume();

  if (volume != fScoringVolume) return;

  // Check for fusion event
  const auto& secondaries = step->GetSecondaryInCurrentStep();
  for (const auto& secondary : *secondaries) {
      if (IsFusionReaction(secondary)) {
          fEventAction->AddFusionEvent();

          // Kill the neutron to prevent further interactions and overcounting
          secondary->SetTrackStatus(fStopAndKill);
      }
  }
}


bool SteppingAction::IsFusionReaction(const G4Track* track)
{
  // Ensure the track is a secondary particle
  if (track->GetParentID() == 0) {
    // This is a primary particle, not a product of a fusion reaction
    return false;
  }

  auto particleName = track->GetDefinition()->GetParticleName();

  if (particleName == "neutron") {
    G4double energy = track->GetKineticEnergy();

    // Check if the neutron energy is around 14 MeV (with a tolerance)
    if (energy >= 14.0 * MeV && energy <= 14.2 * MeV) {
      return true;
    }
  }

  return false;
}

}
