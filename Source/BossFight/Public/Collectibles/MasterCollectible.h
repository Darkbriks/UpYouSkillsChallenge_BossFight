#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractionInterface.h"
#include "MasterCollectible.generated.h"

class UAbilitySystemComponent;
class USphereComponent;

UCLASS()
class BOSSFIGHT_API AMasterCollectible : public AActor, public IInteractionInterface
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USphereComponent* SphereComponent;
	
public:	
	AMasterCollectible();
	
	virtual void Interact(UAbilitySystemComponent* AbilitySystemComponent);
	void Interact_Implementation(UAbilitySystemComponent* AbilitySystemComponent) override { Interact(AbilitySystemComponent); }
};
