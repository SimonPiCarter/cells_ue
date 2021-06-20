// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerEntity.h"

// Sets default values
ATowerEntity::ATowerEntity()
	: multAttackSpeed(1.)
	, multDamage(1.)
	, bonusRange(1.)
	, maxSlots(2)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATowerEntity::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATowerEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

