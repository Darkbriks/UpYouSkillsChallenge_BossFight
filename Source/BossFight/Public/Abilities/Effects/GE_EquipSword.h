#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GameplayTagContainer.h"
#include "GameplayEffectComponents/TargetTagsGameplayEffectComponent.h"
#include "GE_EquipSword.generated.h"

UCLASS()
class BOSSFIGHT_API UGE_EquipSword: public UGameplayEffect
{
	GENERATED_BODY()

public:
	UGE_EquipSword()
	{
		DurationPolicy = EGameplayEffectDurationType::Infinite;
	
		FInheritedTagContainer TargetTags;
		TargetTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Weapon.Sword.Equipped")));

		UTargetTagsGameplayEffectComponent* TargetTagsComponent = NewObject<UTargetTagsGameplayEffectComponent>(this, TEXT("TargetTagsComponent"));
		TargetTagsComponent->SetAndApplyTargetTagChanges(TargetTags);
	}
};
