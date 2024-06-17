#include "WeaponWielderCharacter.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/Controller.h"
#include "Interfaces/CharactersAnimationInterface.h"
#include "Weapons/MasterWeapon.h"
#include "BaseActorAttributes.h"

AWeaponWielderCharacter::AWeaponWielderCharacter()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	
	GetMesh()->ComponentTags.Add(FName("HitDetection"));
	GetMesh()->SetGenerateOverlapEvents(true);
}

//////////////////////////////////////////////////////////////////////////
/// Protected
//////////////////////////////////////////////////////////////////////////
void AWeaponWielderCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (AbilitySystemComponent)
	{
		for (TSubclassOf<UGameplayAbility> Ability : DefaultAbilities)
		{
			if (Ability){ AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability.GetDefaultObject(), 1, 0)); }
		}

		ActorAttributes = AbilitySystemComponent->GetSet<UBaseActorAttributes>();

		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ActorAttributes->GetHealthAttribute()).AddUObject(this, &AWeaponWielderCharacter::HealthChanged);
	}
}

////////// Animation //////////
void AWeaponWielderCharacter::SetAnimWeaponType(TEnumAsByte<EWeaponType> WeaponType)
{
	if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
	{
		if (AnimInstance->GetClass()->ImplementsInterface(UCharactersAnimationInterface::StaticClass()))
		{
			ICharactersAnimationInterface::Execute_SetWeaponType(AnimInstance, WeaponType);
		}
	}
}

////////// Attributes //////////
void AWeaponWielderCharacter::HealthChanged(const FOnAttributeChangeData& Data)
{
	float Health = Data.NewValue; UpdateHealth(Health);
}

void AWeaponWielderCharacter::UpdateHealth(const float Health)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Health: %f"), Health));
	if (Health <= 0) { GetMesh()->SetAllBodiesBelowSimulatePhysics(FName("pelvis"), true); }
}

////////// Abilities //////////
void AWeaponWielderCharacter::Equip()
{
	if (PossessedWeapon && AbilitySystemComponent) { PossessedWeapon->Equip(AbilitySystemComponent, bIsEquipped); }
}

void AWeaponWielderCharacter::LightAttack()
{
	if (AbilitySystemComponent && bIsEquipped)
	{
		PossessedWeapon->LightAttack(AbilitySystemComponent);
	}
}

//////////////////////////////////////////////////////////////////////////
/// Public
//////////////////////////////////////////////////////////////////////////
void AWeaponWielderCharacter::CollectWeapon(AMasterWeapon* Weapon)
{
	if (PossessedWeapon) { PossessedWeapon->Destroy(); }
	PossessedWeapon = Weapon;
	PossessedWeapon->SetWielder(this);
	PossessedWeapon->AttachToSheith(GetMesh());
}

void AWeaponWielderCharacter::Hit()
{
	if (PossessedWeapon) { PlayMontage(PossessedWeapon->GetHitReactionMontage()); }
	else { PlayMontage(DefaultHitMontage); }
}

void AWeaponWielderCharacter::PlayMontage(UAnimMontage* Montage)
{
	if (Montage && GetMesh())
	{
		if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
		{
			AnimInstance->Montage_Play(Montage);
			AnimInstance->OnPlayMontageNotifyBegin.AddDynamic(this, &AWeaponWielderCharacter::OnNotifyBegin);
		}
	}
}

void AWeaponWielderCharacter::OnNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload)
{
	if (NotifyName == FName("AttachWeaponToHand")) { PossessedWeapon->AttachToHand(GetMesh()); }
	else if (NotifyName == FName("AttachWeaponToSheith")) { PossessedWeapon->AttachToSheith(GetMesh()); }
	else if (NotifyName == FName("DetachWeapon")) { PossessedWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform); }
	else if (NotifyName == FName("EquipWeapon")) { bIsEquipped = true; SetAnimWeaponType(PossessedWeapon->GetWeaponType()); }
	else if (NotifyName == FName("UnEquipWeapon")) { bIsEquipped = false; SetAnimWeaponType(EWeaponType::UNARMED); }
	else if (NotifyName == FName("StartHitDetection")) { PossessedWeapon->StartHitDetection(); }
	else if (NotifyName == FName("StopHitDetection")) { PossessedWeapon->StopHitDetection(); }
}