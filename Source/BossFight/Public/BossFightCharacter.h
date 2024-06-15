#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "Interfaces/WeaponWielderInterface.h"
#include "Enums/WeaponType.h"
#include "BossFightCharacter.generated.h"

class AMasterWeapon;
class IInteractionInterface;
class USpringArmComponent;
class UCameraComponent;
class USphereComponent;
class UInputMappingContext;
class UInputAction;
struct FBranchingPointNotifyPayload;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class ABossFightCharacter : public ACharacter, public IWeaponWielderInterface
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USphereComponent* InteractionSphere;


	////////// Input //////////
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* EquipAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LightAttackAction;

	////////// Abilities //////////
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Abilities, meta = (AllowPrivateAccess = "true"))
	class UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Abilities, meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<class UGameplayAbility>> DefaultAbilities;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Abilities, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* DefaultHitMontage;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Actor Attributes", meta = (AllowPrivateAccess = "true"))
	const class UBaseActorAttributes* ActorAttributes;
	
	IInteractionInterface* Interactable;

	UPROPERTY(BlueprintReadOnly, Category = "Weapons", meta = (AllowPrivateAccess = "true"))
	AMasterWeapon* PossessedWeapon;

	UPROPERTY(BlueprintReadOnly, Category = "Weapons", meta = (AllowPrivateAccess = "true"))
	bool bIsEquipped;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void BeginPlay();

	void SetAnimWeaponType(TEnumAsByte<EWeaponType> WeaponType);

	////////// Overlap //////////
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	////////// Abilities //////////
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Category = "Interactions")
	void Interact();

	UFUNCTION(BlueprintCallable, Category = "Weapons")
	void Equip();

	UFUNCTION(BlueprintCallable, Category = "Weapons")
	void LightAttack();

public:
	ABossFightCharacter();

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
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	FORCEINLINE USphereComponent* GetInteractionSphere() const { return InteractionSphere; }
	FORCEINLINE UAbilitySystemComponent* GetAbilitySystemComponent() const { return AbilitySystemComponent; }
};