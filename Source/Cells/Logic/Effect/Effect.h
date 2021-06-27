// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Logic.h"
#include "Effect.generated.h"

class AMobEntity;
class ATowerEntity;
class ALogicEngine;

/**
 * 
 */
UCLASS(BlueprintType)
class CELLS_API UEffect : public UObject
{
	GENERATED_BODY()
public:
	UEffect();

	virtual void runlogic(float elapsedTime_p) final;

	virtual void runEffect(float elapsedTime_p) {}

	bool isOver() const { return over; }

	void setLogic(ALogicEngine* logic_p) { logic = logic_p; }
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
		AMobEntity * target;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
		ATowerEntity* source;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
		bool onHold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
		bool over;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
		ALogicEngine* logic;
};
