#include "Abilities/GA_CollectSword.h"
#include "GameplayTagContainer.h"
#include "BossFightCharacter.h"
#include "Weapons/MasterWeapon.h"

UGA_CollectSword::UGA_CollectSword()
{
	static ConstructorHelpers::FClassFinder<UGameplayEffect> Effect(TEXT("/Game/BossFight/Content/Blueprint/Abilities/Effects/GE_CollectSword"));
	if (Effect.Succeeded()) { GameplayEffectClass = Effect.Class; }
	
	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Weapon.Sword")));
	CostGameplayEffectClass = this->GameplayEffectClass;
}

void UGA_CollectSword::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
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
}

void UGA_CollectSword::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	
	UE_LOG(LogTemp, Warning, TEXT("GA_CollectSword::EndAbility"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("GA_CollectSword::EndAbility"));
}