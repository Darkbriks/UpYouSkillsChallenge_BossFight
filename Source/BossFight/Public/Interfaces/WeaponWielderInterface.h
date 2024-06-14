#pragma once

#include "WeaponWielderInterface.generated.h"

UINTERFACE(MinimalAPI)
class UWeaponWielderInterface : public UInterface
{
	GENERATED_BODY()
};

class IWeaponWielderInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon")
	class AMasterWeapon* GetWeapon();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon")
	void CollectWeapon(class AMasterWeapon* Weapon);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon")
	void PlayMontage(class UAnimMontage* Montage);
};