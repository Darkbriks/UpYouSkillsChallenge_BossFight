#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GameplayTagContainer.h"
#include "GameplayEffectComponents/TargetTagsGameplayEffectComponent.h"
#include "GE_CollectSword.generated.h"

UCLASS()
class BOSSFIGHT_API UGE_CollectSword : public UGameplayEffect
{
	GENERATED_BODY()

public:
	UGE_CollectSword()
	{
		DurationPolicy = EGameplayEffectDurationType::Infinite;
	
		FInheritedTagContainer TargetTags;
		TargetTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Weapon.Sword")));

		UTargetTagsGameplayEffectComponent* TargetTagsComponent = NewObject<UTargetTagsGameplayEffectComponent>(this, TEXT("TargetTagsComponent"));
		TargetTagsComponent->SetAndApplyTargetTagChanges(TargetTags);
	}
};
