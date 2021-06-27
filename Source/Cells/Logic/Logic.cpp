// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic.h"

float BaseLogic::FixedTimeStep = 0.01f;

BaseLogic::BaseLogic() : accumulatedTime(0.f)
{}

BaseLogic::~BaseLogic()
{}

void BaseLogic::run(float elapsedTime_p)
{
	accumulatedTime += elapsedTime_p;

	// run as many logic pass as required to consume time
	while (accumulatedTime >= FixedTimeStep)
	{
		// consume time from the rendering system
		accumulatedTime -= FixedTimeStep;
		// run with fixed time
		runlogic(FixedTimeStep, accumulatedTime);
	}
}

// Sets default values
ALogicActor::ALogicActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALogicActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALogicActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	run(DeltaTime);
}

