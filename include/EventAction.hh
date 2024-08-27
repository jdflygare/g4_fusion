#ifndef B1EventAction_h
#define B1EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

namespace B1
{

class RunAction;

class EventAction : public G4UserEventAction
{
  public:
    EventAction(RunAction* runAction);
    ~EventAction() override = default;

    void BeginOfEventAction(const G4Event* event) override;
    void EndOfEventAction(const G4Event* event) override;

    void AddEdep(G4double edep) { fEdep += edep; }
    void AddFusionEvent();  // Ensure this method is declared

  private:
    RunAction* fRunAction = nullptr;
    G4double   fEdep = 0.;
    G4int      fFusionEvents = 0;  // Track the number of fusion events
};

}

#endif
