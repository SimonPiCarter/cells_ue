// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../TimeBuffEffect.h"
#include "../../../../DmgType.h"
#include "ComboEffect.generated.h"

/**
 *
 */
UCLASS()
class CELLS_API UComboEffect : public UTimeBuffEffect
{
	GENERATED_BODY()
public:
	UComboEffect();
	UComboEffect(float duration_p, float dmg_p);

	virtual void apply();

	void spawnDmg();

protected:
	/// @brief damage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ComboEffect")
		float _dmg;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ComboEffect")
		DmgType _dmgType;

	/// @brief damage every second
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ComboEffect")
		TArray<FString> _comboIdArray;

	bool _dmgSpawned;

    UFUNCTION(BlueprintCallable, Category = "ComboEffect")
        void init(FString id, TArray<FString> const &comboIdArray, float dmg, DmgType dmgType);
};
