#include "RunAction.hh"
#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4AccumulableManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

namespace B1
{

RunAction::RunAction()
: fEdep(0.), fEdep2(0.), fFusionCount(0)  // Initialize fusion count to 0
{
  // Register accumulables to the accumulable manager
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->RegisterAccumulable(fEdep);
  accumulableManager->RegisterAccumulable(fEdep2);
  accumulableManager->RegisterAccumulable(fFusionCount);
}

void RunAction::BeginOfRunAction(const G4Run*)
{
  // Reset accumulables to their initial values at the start of each run
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->Reset();
}

void RunAction::EndOfRunAction(const G4Run* run)
{
  G4int nofEvents = run->GetNumberOfEvent();
  if (nofEvents == 0) return;

  // Merge accumulables from all threads (if running in multi-threaded mode)
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->Merge();

  // Compute total fusion events
  G4int fusionCount = fFusionCount.GetValue();

  // Print results at the end of the run
  if (IsMaster()) {
    G4cout << G4endl
           << "--------------------End of Global Run-----------------------" << G4endl
           << " The run consisted of " << nofEvents << " events." << G4endl
           << " Total number of fusion events: " << fusionCount << G4endl
           << "------------------------------------------------------------" << G4endl;
  }
}

void RunAction::AddEdep(G4double edep)
{
  fEdep  += edep;
  fEdep2 += edep*edep;
}


}
