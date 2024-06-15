#pragma once

#include "CoreMinimal.h"
#include "Enums/WeaponType.h"
#include "GameFramework/Actor.h"
#include "MasterWeapon.generated.h"

class USkeletalMeshComponent;
class UGameplayAbility;
class UAnimMontage;

UCLASS(Blueprintable)
class BOSSFIGHT_API AMasterWeapon : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Mesh;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<EWeaponType> WeaponType = SWORD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	FTransform SheithOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	FTransform HandOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	FName SheithSocketName = "Socket_SwordSheith";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	FName HandSocketName = "hand_r";

	////////// Abilities //////////
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameplayAbility> EquipAbility;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameplayAbility> UnEquipAbility;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameplayAbility> LightAttackAbility;

	////////// Animations //////////
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* EquipMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* UnEquipMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* LightAttackMontage;

public:
	AMasterWeapon();

	void AttachToSheith(USkeletalMeshComponent* SkeletalMesh);
	void AttachToHand(USkeletalMeshComponent* SkeletalMesh);

	void Equip(class UAbilitySystemComponent* AbilitySystemComponent, bool bIsEquipped);
	void LightAttack(class UAbilitySystemComponent* AbilitySystemComponent);

	TEnumAsByte<EWeaponType> GetWeaponType() const { return WeaponType; }
	UAnimMontage* GetEquipMontage() const { return EquipMontage; }
	UAnimMontage* GetUnEquipMontage() const { return UnEquipMontage; }
	UAnimMontage* GetLightAttackMontage() const { return LightAttackMontage; }
};
