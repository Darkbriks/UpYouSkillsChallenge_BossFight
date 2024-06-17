#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Weapons/MasterWeapon.h"
#include "GA_CollectWeapon.generated.h"

UCLASS()
class BOSSFIGHT_API UGA_CollectWeapon : public UGameplayAbility
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AMasterWeapon> WeaponToAttachClass = nullptr;

public:
	UGA_CollectWeapon();

	AMasterWeapon* GetWeaponToAttach() const { return WeaponToAttachClass.GetDefaultObject(); }

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
};
