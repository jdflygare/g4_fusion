#include "EventAction.hh"
#include "RunAction.hh"
#include "G4Event.hh"

namespace B1
{

EventAction::EventAction(RunAction* runAction)
: fRunAction(runAction)
{}

void EventAction::BeginOfEventAction(const G4Event*)
{
  fEdep = 0.;
  fFusionEvents = 0;  // Reset fusion events for each event
}

void EventAction::EndOfEventAction(const G4Event*)
{
    fRunAction->AddEdep(fEdep);

    // Pass the total number of fusion events directly
    fRunAction->AddFusionEvent(fFusionEvents);
}

void EventAction::AddFusionEvent()
{
  fFusionEvents++;  // Increment the fusion event count
}

}
