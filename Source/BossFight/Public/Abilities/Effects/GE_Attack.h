#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GameplayTagContainer.h"
#include "GameplayEffectComponents/TargetTagsGameplayEffectComponent.h"
#include "GE_Attack.generated.h"

UCLASS()
class BOSSFIGHT_API UGE_Attack: public UGameplayEffect
{
	GENERATED_BODY()

public:
	UGE_Attack()
	{
		DurationPolicy = EGameplayEffectDurationType::HasDuration;
		DurationMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(1.0f));

		FInheritedTagContainer TargetTags;
		TargetTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Weapon.Attack")));

		UTargetTagsGameplayEffectComponent* TargetTagsComponent = NewObject<UTargetTagsGameplayEffectComponent>(this, TEXT("TargetTagsComponent"));
		TargetTagsComponent->SetAndApplyTargetTagChanges(TargetTags);
	}
};