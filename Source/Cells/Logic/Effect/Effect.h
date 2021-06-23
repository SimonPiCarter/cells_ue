// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Logic.h"
#include "Effect.generated.h"

class AMobEntity;
class ATowerEntity;

/**
 * 
 */
UCLASS()
class CELLS_API AEffect : public ALogic
{
	GENERATED_BODY()
public:
	AEffect();

	virtual void runlogic(float elapsedTime_p) final;

	virtual void runEffect(float elapsedTime_p) {}

	bool isOver() const { return over; }
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
		AMobEntity * target;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
		ATowerEntity* source;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
		bool onHold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
		bool over;
};
