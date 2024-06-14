#include "Collectibles/MasterCollectible.h"
#include "Components/SphereComponent.h"

AMasterCollectible::AMasterCollectible()
{
	PrimaryActorTick.bCanEverTick = false;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->InitSphereRadius(100.f);
	SphereComponent->SetCollisionProfileName(TEXT("OverlapAll"));
	SphereComponent->SetGenerateOverlapEvents(true);
	RootComponent = SphereComponent;
}

void AMasterCollectible::Interact(ABossFightCharacter* Character)
{
	Destroy();
}