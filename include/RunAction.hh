#ifndef B1RunAction_h
#define B1RunAction_h 1

#include "G4UserRunAction.hh"
#include "G4Accumulable.hh"
#include "globals.hh"

class G4Run;

namespace B1
{

class RunAction : public G4UserRunAction
{
  public:
    RunAction();
    ~RunAction() override = default;

    void BeginOfRunAction(const G4Run*) override;
    void   EndOfRunAction(const G4Run*) override;

    void AddEdep(G4double edep);
    void AddFusionEvent(G4int numEvents) { fFusionCount += numEvents; }    // Increment fusion event count

  private:
    G4Accumulable<G4double> fEdep;
    G4Accumulable<G4double> fEdep2;
    G4Accumulable<G4int>    fFusionCount;  // Accumulable for global fusion count
};

}

#endif
