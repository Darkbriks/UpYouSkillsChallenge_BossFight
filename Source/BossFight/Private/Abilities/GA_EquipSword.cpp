#include "Abilities/GA_EquipSword.h"
#include "GameplayTagContainer.h"
#include "BossFightCharacter.h"
#include "UObject/ConstructorHelpers.h"


UGA_EquipSword::UGA_EquipSword()
{
	static ConstructorHelpers::FClassFinder<UGameplayEffect> Effect(TEXT("/Game/BossFight/Content/Blueprint/Abilities/Effects/GE_EquipSword"));
	if (Effect.Succeeded()) { GameplayEffectClass = Effect.Class; }
	
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Input.Weapon.Sword.Equip")));
	ActivationRequiredTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Weapon.Sword")));
	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Weapon.Sword.Equipped")));
	CostGameplayEffectClass = this->GameplayEffectClass;
}

void UGA_EquipSword::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	if (CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		if (IWeaponWielderInterface* WeaponWielderInterface = Cast<IWeaponWielderInterface>(ActorInfo->AvatarActor))
		{
			WeaponWielderInterface->Execute_EquipWeapon(WeaponWielderInterface->_getUObject());
		}
	}
	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}

void UGA_EquipSword::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}