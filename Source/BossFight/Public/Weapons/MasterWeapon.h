#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MasterWeapon.generated.h"

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
	FTransform SheithOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	FTransform HandOffset;

public:	
	AMasterWeapon();

	void AttachToSheith(USkeletalMeshComponent* SkeletalMesh, FName SocketName);
	void AttachToHand(USkeletalMeshComponent* SkeletalMesh, FName SocketName);
};
