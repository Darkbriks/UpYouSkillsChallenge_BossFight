#include "Abilities/GA_UnEquipSword.h"
#include "GameplayTagContainer.h"
#include "WeaponWielderCharacter.h"
#include "Weapons/MasterWeapon.h"

UGA_UnEquipSword::UGA_UnEquipSword()
{
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Input.Weapon.Sword.UnEquip")));
	ActivationRequiredTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Weapon.Sword.Equipped")));
	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("React")));
}

void UGA_UnEquipSword::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	if (CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		BP_RemoveGameplayEffectFromOwnerWithGrantedTags(FGameplayTagContainer(FGameplayTag::RequestGameplayTag(FName("Weapon.Sword.Equipped"))));
		if (IWeaponWielderInterface* WeaponWielderInterface = Cast<IWeaponWielderInterface>(ActorInfo->AvatarActor))
		{
			if (AMasterWeapon* Weapon = WeaponWielderInterface->Execute_GetWeapon(WeaponWielderInterface->_getUObject()))
			{
				WeaponWielderInterface->Execute_PlayMontage(WeaponWielderInterface->_getUObject(), Weapon->GetUnEquipMontage());
			}
		}
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
	}
}