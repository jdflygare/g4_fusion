#include "PrimaryGeneratorAction.hh"

#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4IonTable.hh"

namespace B1
{

PrimaryGeneratorAction::PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(nullptr)
{
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);

  // Default particle kinematic: deuteron with 150 keV energy
  G4ParticleDefinition* particleDefinition = G4IonTable::GetIonTable()->GetIon(1, 2, 0);
  fParticleGun->SetParticleDefinition(particleDefinition);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
  fParticleGun->SetParticleEnergy(150.*keV);
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  // Set gun position 5 cm in front of the target
  G4double z0 = -5.0*cm;
  fParticleGun->SetParticlePosition(G4ThreeVector(0.,0.,z0));

  fParticleGun->GeneratePrimaryVertex(anEvent);
}

}
