#include "Weapons/MasterWeapon.h"
#include "AbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "Interfaces/WeaponWielderInterface.h"

AMasterWeapon::AMasterWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

	HitDetection = CreateDefaultSubobject<UCapsuleComponent>(TEXT("HitDetection"));
	HitDetection->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	HitDetection->SetupAttachment(Mesh);
}

void AMasterWeapon::BeginPlay()
{
	Super::BeginPlay();

	HitDetection->OnComponentBeginOverlap.AddDynamic(this, &AMasterWeapon::OnHitDetectionOverlapBegin);
}

void AMasterWeapon::OnHitDetectionOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherComp->ComponentHasTag(FName("HitDetection"))) { return; }
	if (UAbilitySystemComponent* AbilitySystemComponent = Cast<UAbilitySystemComponent>(OtherActor->GetComponentByClass(UAbilitySystemComponent::StaticClass())))
	{
		if (AbilitySystemComponent->GetOwner() != Wielder)
		{
			if (IWeaponWielderInterface* WeaponWielderInterface = Cast<IWeaponWielderInterface>(Wielder))
			{
				AbilitySystemComponent->TryActivateAbilityByClass(HitReactionAbility);
			}
		}
	}
}

void AMasterWeapon::SetWielder(AActor* NewWielder)
{
	Wielder = NewWielder;
	if (UAbilitySystemComponent* AbilitySystemComponent = Cast<UAbilitySystemComponent>(Wielder->GetComponentByClass(UAbilitySystemComponent::StaticClass())))
	{
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(EquipAbility));
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(UnEquipAbility));
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(LightAttackAbility));
	}
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

void AMasterWeapon::StartHitDetection()
{
	HitDetection->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AMasterWeapon::StopHitDetection()
{
	HitDetection->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}