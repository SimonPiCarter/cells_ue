// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic.h"

float ALogic::FixedTimeStep = 0.1f;

// Sets default values
ALogic::ALogic() : accumulatedTime(0.f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALogic::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALogic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	accumulatedTime += DeltaTime;

	// run as many logic pass as required to consume time
	while (accumulatedTime >= FixedTimeStep)
	{
		// consume time from the rendering system
		accumulatedTime -= FixedTimeStep;
		// run with fixed time
		runlogic(FixedTimeStep);
	}
}

