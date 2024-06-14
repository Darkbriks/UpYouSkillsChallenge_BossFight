#include "Weapons/MasterWeapon.h"
#include "Abilities/GA_EquipSword.h"
#include "Abilities/GA_UnEquipSword.h"
#include "AbilitySystemComponent.h"

AMasterWeapon::AMasterWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
}

void AMasterWeapon::AttachToSheith(USkeletalMeshComponent* SkeletalMesh)
{
	Root->AttachToComponent(SkeletalMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, SheithSocketName);
	Mesh->SetRelativeTransform(SheithOffset);
}

void AMasterWeapon::AttachToHand(USkeletalMeshComponent* SkeletalMesh)
{
	Root->AttachToComponent(SkeletalMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, HandSocketName);
	Mesh->SetRelativeTransform(HandOffset);
}

void AMasterWeapon::Equip(UAbilitySystemComponent* AbilitySystemComponent, bool bIsEquipped)
{
	if (AbilitySystemComponent)
	{
		if (bIsEquipped) { AbilitySystemComponent->TryActivateAbilityByClass(UnEquipAbility); }
		else { AbilitySystemComponent->TryActivateAbilityByClass(EquipAbility); }
	}
}

void AMasterWeapon::LightAttack(UAbilitySystemComponent* AbilitySystemComponent)
{
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->TryActivateAbilityByClass(LightAttackAbility);
	}
}