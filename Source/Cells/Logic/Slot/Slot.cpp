// Fill out your copyright notice in the Description page of Project Settings.


#include "Slot.h"

// Sets default values
ASlot::ASlot() : isAttackModifier(false)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}
ASlot::ASlot(bool attackModifier_p) : isAttackModifier(attackModifier_p)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ASlot::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASlot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

