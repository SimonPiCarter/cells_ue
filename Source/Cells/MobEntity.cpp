// Fill out your copyright notice in the Description page of Project Settings.


#include "MobEntity.h"

// Sets default values
AMobEntity::AMobEntity()
	: armorType(ArmorType::Standard)
	, _currentCheckPoint(0)
	, hitpoint(3.)
	, maxHitpoint(3.)
	, speed(10)
	, damageMultiplier(1.)
	, damageLife(1.)
	, scrapReward(1.)
	, size(1.)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AMobEntity::move(float time_p)
{
	FVector currentLocation_l = this->GetActorLocation();
	float remaining_l = time_p;
	// skip if at last checkpoint
	while (!isAtLastCheckPoint() && remaining_l > 1e-7)
	{
		// direction to next checkpoint
		FVector2D const& checkpoint_l = getCurrentCheckPoint();
		FVector target_l = FVector(checkpoint_l, currentLocation_l.Z);
		FVector direction_l = target_l - currentLocation_l;
		// normalize direction
		float length_l = direction_l.Size();
		direction_l /= length_l;
		// reached checkpoint
		if (length_l < time_p * speed)
		{
			currentLocation_l = target_l;
			remaining_l -= length_l / speed;
			++_currentCheckPoint;
		}
		else
		{
			currentLocation_l += time_p * speed * direction_l;
			remaining_l = 0;
		}
	}
	this->SetActorLocation(currentLocation_l);
}

bool AMobEntity::isAtLastCheckPoint()
{
	return _currentCheckPoint >= checkpoints.Num();
}

FVector2D const & AMobEntity::getCurrentCheckPoint()
{
	return checkpoints[_currentCheckPoint];
}

// Called when the game starts or when spawned
void AMobEntity::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMobEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMobEntity::setArmorType(FString const & str_p)
{
	armorType = fromStringToArmorType(std::string(TCHAR_TO_UTF8(*str_p)));
}
