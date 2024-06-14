#include "Weapons/MasterWeapon.h"

AMasterWeapon::AMasterWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
}

void AMasterWeapon::AttachToSheith(USkeletalMeshComponent* SkeletalMesh, FName SocketName)
{
	Root->AttachToComponent(SkeletalMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, SocketName);
	Mesh->SetRelativeTransform(SheithOffset);
}

void AMasterWeapon::AttachToHand(USkeletalMeshComponent* SkeletalMesh, FName SocketName)
{
	Root->AttachToComponent(SkeletalMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, SocketName);
	Mesh->SetRelativeTransform(HandOffset);
}