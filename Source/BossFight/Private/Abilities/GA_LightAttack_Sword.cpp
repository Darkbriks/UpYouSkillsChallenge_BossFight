#include "Abilities/GA_LightAttack_Sword.h"
#include "GameplayTagContainer.h"
#include "Abilities/Effects/GE_Attack.h"
#include "Interfaces/WeaponWielderInterface.h"


UGA_LightAttack_Sword::UGA_LightAttack_Sword()
{
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Input.LightAttack.Sword")));
	ActivationRequiredTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Weapon.Sword.Equipped")));
	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Weapon.Attack")));
}

void UGA_LightAttack_Sword::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		if (IWeaponWielderInterface* WeaponWielderInterface = Cast<IWeaponWielderInterface>(ActorInfo->AvatarActor))
		{
			WeaponWielderInterface->Execute_LightAttack(WeaponWielderInterface->_getUObject());
			ApplyGameplayEffectToOwner(Handle, ActorInfo, ActivationInfo, NewObject<UGE_Attack>(), 1);
		}
	}
	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}