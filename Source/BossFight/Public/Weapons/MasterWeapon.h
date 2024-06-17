#pragma once

#include "CoreMinimal.h"
#include "Enums/WeaponType.h"
#include "GameFramework/Actor.h"
#include "MasterWeapon.generated.h"

class UAbilitySystemComponent;
class UCapsuleComponent;
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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* HitDetection;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UAbilitySystemComponent* Wielder;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameplayAbility> HitReactionAbility;

	////////// Animations //////////
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* EquipMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* UnEquipMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* LightAttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* HitReactionMontage;

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHitDetectionOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	AMasterWeapon();

	UAbilitySystemComponent* GetWielder() const { return Wielder; }
	void SetWielder(UAbilitySystemComponent* NewWielder);

	void AttachToSheith(USkeletalMeshComponent* SkeletalMesh);
	void AttachToHand(USkeletalMeshComponent* SkeletalMesh);

	void Equip(UAbilitySystemComponent* AbilitySystemComponent, bool bIsEquipped);
	void LightAttack(UAbilitySystemComponent* AbilitySystemComponent);

	TEnumAsByte<EWeaponType> GetWeaponType() const { return WeaponType; }
	UAnimMontage* GetEquipMontage() const { return EquipMontage; }
	UAnimMontage* GetUnEquipMontage() const { return UnEquipMontage; }
	UAnimMontage* GetLightAttackMontage() const { return LightAttackMontage; }
	UAnimMontage* GetHitReactionMontage() const { return HitReactionMontage; }

	void StartHitDetection();
	void StopHitDetection();
};
