// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Logic.generated.h"

class BaseLogic
{
public:
	BaseLogic();
	virtual ~BaseLogic();

	void run(float elapsedTime_p);

protected:
	// Called to consume a fixed amount of time
	// every logic component using time should inherit this
	// @param elapsedTime_p the time to be consumed
	// @param remaining accumulated time that can be passed on new generated logic component
	virtual void runlogic(float elapsedTime_p, float remainingTime_p) = 0; // shoulld be virtual pure

	static float FixedTimeStep;

	// time accumulated since last frame
	float accumulatedTime;
};

UCLASS(Abstract)
class CELLS_API ALogicActor : public AActor, public BaseLogic
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALogicActor();

	// should be virtual pure (but cannot)
	virtual void runlogic(float elapsedTime_p, float remainingTime_p) override {}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:	
	// Called every frame (cannot extend anymore)
	virtual void Tick(float DeltaTime) override final;
};

UCLASS(Abstract)
class CELLS_API ULogicObject : public UObject, public BaseLogic
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ULogicObject() {}

	// should be virtual pure (but cannot)
	virtual void runlogic(float elapsedTime_p, float remainingTime_p) override {}
};
