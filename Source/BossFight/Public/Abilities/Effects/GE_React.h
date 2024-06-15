#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GameplayTagContainer.h"
#include "GameplayEffectComponents/TargetTagsGameplayEffectComponent.h"
#include "GE_React.generated.h"

UCLASS()
class BOSSFIGHT_API UGE_React: public UGameplayEffect
{
	GENERATED_BODY()

public:
	UGE_React()
	{
		DurationPolicy = EGameplayEffectDurationType::HasDuration;
		DurationMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(.5f));

		FInheritedTagContainer TargetTags;
		TargetTags.AddTag(FGameplayTag::RequestGameplayTag(FName("React.Hit")));

		UTargetTagsGameplayEffectComponent* TargetTagsComponent = NewObject<UTargetTagsGameplayEffectComponent>(this, TEXT("TargetTagsComponent"));
		TargetTagsComponent->SetAndApplyTargetTagChanges(TargetTags);
	}
};