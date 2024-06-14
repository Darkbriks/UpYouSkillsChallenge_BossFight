#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractionInterface.h"
#include "MasterCollectible.generated.h"

class ABossFightCharacter;
class USphereComponent;

UCLASS()
class BOSSFIGHT_API AMasterCollectible : public AActor, public IInteractionInterface
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USphereComponent* SphereComponent;
	
public:	
	AMasterCollectible();
	
	virtual void Interact(ABossFightCharacter* Character);
	void Interact_Implementation(ABossFightCharacter* Character) override { Interact(Character); }
};
