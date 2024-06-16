#include "Collectibles/MasterWeaponCollectible.h"
#include "BossFightCharacter.h"
#include "AbilitySystemComponent.h"
#include "Abilities/GA_CollectWeapon.h"

void AMasterWeaponCollectible::Interact(ABossFightCharacter* Character)
{
	if (AbilityClass != nullptr)
	{
		if (UAbilitySystemComponent* AbilitySystemComponent = Character->GetAbilitySystemComponent())
		{
			FGameplayAbilitySpecHandle AbilitySpecHandle = AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(AbilityClass.GetDefaultObject()));
			AbilitySystemComponent->TryActivateAbility(AbilitySpecHandle, true);
		}
	}
	Destroy();
}
