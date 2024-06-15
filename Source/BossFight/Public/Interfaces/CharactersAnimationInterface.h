#pragma once

#include "Enums/WeaponType.h"
#include "CharactersAnimationInterface.generated.h"

UINTERFACE(MinimalAPI)
class UCharactersAnimationInterface : public UInterface
{
	GENERATED_BODY()
};

class ICharactersAnimationInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetWeaponType(const EWeaponType WeaponType);
};