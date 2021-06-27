// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Logic.generated.h"

UCLASS(Abstract)
class CELLS_API ALogic : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALogic();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to consume a fixed amount of time
	// every logic component using time should inherit this
	// @param elapsedTime_p the time to be consumed
	// @param remaining accumulated time that can be passed on new generated logic component
	virtual void runlogic(float elapsedTime_p, float remainingTime_p) {} // shoulld be virtual pure

	static float FixedTimeStep;

	// time accumulated since last frame
	float accumulatedTime;

public:	
	// Called every frame (cannot extend anymore)
	virtual void Tick(float DeltaTime) override final;
};
