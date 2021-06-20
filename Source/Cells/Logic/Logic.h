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
	virtual void runlogic(float elapsedTime_p) {} // shoulld be virtual pure

	static float FixedTimeStep;

	// time accumulated since last frame
	float accumulatedTime;

public:	
	// Called every frame (cannot extend anymore)
	virtual void Tick(float DeltaTime) override final;
};
