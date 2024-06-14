#include "Abilities/GA_UnEquipSword.h"
#include "GameplayTagContainer.h"
#include "BossFightCharacter.h"

UGA_UnEquipSword::UGA_UnEquipSword()
{
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Input.Weapon.Sword.UnEquip")));
	ActivationRequiredTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Weapon.Sword.Equipped")));
}

void UGA_UnEquipSword::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	if (CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		BP_RemoveGameplayEffectFromOwnerWithGrantedTags(FGameplayTagContainer(FGameplayTag::RequestGameplayTag(FName("Weapon.Sword.Equipped"))));
		if (IWeaponWielderInterface* WeaponWielderInterface = Cast<IWeaponWielderInterface>(ActorInfo->AvatarActor))
		{
			WeaponWielderInterface->Execute_UnEquipWeapon(WeaponWielderInterface->_getUObject());
		}
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
	}
}

void UGA_UnEquipSword::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}