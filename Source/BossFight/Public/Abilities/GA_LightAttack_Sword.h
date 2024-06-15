#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GA_LightAttack_Sword.generated.h"

UCLASS()
class BOSSFIGHT_API UGA_LightAttack_Sword : public UGameplayAbility
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
	TSubclassOf<UGameplayEffect> AttackEffect;

public:
	UGA_LightAttack_Sword();
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
};
