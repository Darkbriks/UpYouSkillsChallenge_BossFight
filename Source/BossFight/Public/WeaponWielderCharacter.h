#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/WeaponWielderInterface.h"
#include "Enums/WeaponType.h"
#include "WeaponWielderCharacter.generated.h"

class AMasterWeapon;
class UAbilitySystemComponent;
class UGameplayAbility;
class UAnimMontage;
struct FOnAttributeChangeData;
struct FBranchingPointNotifyPayload;

UCLASS()
class BOSSFIGHT_API AWeaponWielderCharacter : public ACharacter, public IWeaponWielderInterface
{
	GENERATED_BODY()

	////////// Abilities //////////
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Abilities, meta = (AllowPrivateAccess = "true"))
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Abilities, meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Abilities, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* DefaultHitMontage;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Actor Attributes", meta = (AllowPrivateAccess = "true"))
	const class UBaseActorAttributes* ActorAttributes;

	UPROPERTY(BlueprintReadOnly, Category = "Weapons", meta = (AllowPrivateAccess = "true"))
	AMasterWeapon* PossessedWeapon;

	UPROPERTY(BlueprintReadOnly, Category = "Weapons", meta = (AllowPrivateAccess = "true"))
	bool bIsEquipped;

	virtual void BeginPlay() override;

	void SetAnimWeaponType(TEnumAsByte<EWeaponType> WeaponType);

	virtual void HealthChanged(const FOnAttributeChangeData& Data);
	void UpdateHealth(const float Health);

	UFUNCTION(BlueprintCallable, Category = "Weapons")
	void Equip();

	UFUNCTION(BlueprintCallable, Category = "Weapons")
	void LightAttack();

public:
	AWeaponWielderCharacter();
	
	UFUNCTION()
	void OnNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);

	////////// WeaponWielderInterface //////////
	virtual AMasterWeapon* GetWeapon() { if (PossessedWeapon) { return PossessedWeapon; } return nullptr; }
	AMasterWeapon* GetWeapon_Implementation() override { return GetWeapon(); }
	
	virtual void CollectWeapon(AMasterWeapon* Weapon);
	void CollectWeapon_Implementation(AMasterWeapon* Weapon) override { CollectWeapon(Weapon); }

	virtual void Hit();
	void Hit_Implementation() override { Hit(); }

	virtual void PlayMontage(UAnimMontage* Montage);
	void PlayMontage_Implementation(UAnimMontage* Montage) override { PlayMontage(Montage); }

	////////// Getters //////////
	FORCEINLINE UAbilitySystemComponent* GetAbilitySystemComponent() const { return AbilitySystemComponent; }
};
