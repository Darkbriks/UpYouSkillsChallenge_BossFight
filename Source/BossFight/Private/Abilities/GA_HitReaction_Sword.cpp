#include "Abilities/GA_HitReaction_Sword.h"
#include "GameplayTagContainer.h"
#include "Abilities/Effects/GE_React.h"
#include "Interfaces/WeaponWielderInterface.h"
#include "Weapons/MasterWeapon.h"


UGA_HitReaction_Sword::UGA_HitReaction_Sword()
{
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Weapon.Sword.React")));
	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("React.Hit")));
}

void UGA_HitReaction_Sword::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Hit"));
		if (IWeaponWielderInterface* WeaponWielderInterface = Cast<IWeaponWielderInterface>(ActorInfo->AvatarActor))
		{
			WeaponWielderInterface->Execute_Hit(WeaponWielderInterface->_getUObject());
			ApplyGameplayEffectToOwner(Handle, ActorInfo, ActivationInfo, NewObject<UGE_React>(), 1);
		}
	}
	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}