#include "Abilities/GA_CollectWeapon.h"
#include "GameplayTagContainer.h"
#include "BossFightCharacter.h"
#include "Abilities/Effects/GE_CollectSword.h"
#include "Weapons/MasterWeapon.h"

UGA_CollectWeapon::UGA_CollectWeapon()
{
	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Weapon.Sword")));
	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("React")));
	CostGameplayEffectClass = UGE_CollectSword::StaticClass();
}

void UGA_CollectWeapon::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	if (CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		if (AMasterWeapon* WeaponToAttach = GetWorld()->SpawnActor<AMasterWeapon>(WeaponToAttachClass, FVector::ZeroVector, FRotator::ZeroRotator))
		{
			if (IWeaponWielderInterface* WeaponWielderInterface = Cast<IWeaponWielderInterface>(ActorInfo->AvatarActor))
			{
				WeaponWielderInterface->Execute_CollectWeapon(WeaponWielderInterface->_getUObject(), WeaponToAttach);
			}
		}
	}
	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}

void UGA_CollectWeapon::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}