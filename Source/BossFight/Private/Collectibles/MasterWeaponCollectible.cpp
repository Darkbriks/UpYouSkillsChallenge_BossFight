#include "Collectibles/MasterWeaponCollectible.h"
#include "AbilitySystemComponent.h"
#include "Abilities/GA_CollectWeapon.h"

void AMasterWeaponCollectible::Interact(UAbilitySystemComponent* AbilitySystemComponent)
{
	if (AbilityClass && AbilitySystemComponent)
	{
		FGameplayAbilitySpecHandle AbilitySpecHandle = AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(AbilityClass.GetDefaultObject()));
		AbilitySystemComponent->TryActivateAbility(AbilitySpecHandle, true);
	}
	Destroy();
}
