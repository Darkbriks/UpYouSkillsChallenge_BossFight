#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GA_HitReaction_Sword.generated.h"

UCLASS()
class BOSSFIGHT_API UGA_HitReaction_Sword : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UGA_HitReaction_Sword();
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
};
