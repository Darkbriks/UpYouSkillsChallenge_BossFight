#pragma once

#include "CoreMinimal.h"
#include "Collectibles/MasterCollectible.h"
#include "MasterWeaponCollectible.generated.h"

UCLASS()
class BOSSFIGHT_API AMasterWeaponCollectible : public AMasterCollectible
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	TSubclassOf<class UGameplayAbility> AbilityClass = nullptr;
	
	void Interact(UAbilitySystemComponent* AbilitySystemComponent) override;
};
