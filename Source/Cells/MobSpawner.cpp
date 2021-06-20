// Fill out your copyright notice in the Description page of Project Settings.


#include "MobSpawner.h"

#include "Engine/World.h"
#include "MobEntity.h"

AMobSpawner::AMobSpawner() : test(nullptr), storedTime(0)
{}

void AMobSpawner::runlogic(float elapsedTime_p)
{
    storedTime += elapsedTime_p;
    UWorld* const World_l = GetWorld();
    while (World_l  && storedTime > 2.f) {
        storedTime -= 2.f;
        FActorSpawnParameters SpawnParams;
        
        AMobEntity* mob_l = World_l->SpawnActor<AMobEntity>((UClass*)this->test->GeneratedClass, FVector(0, 0, 0), FRotator(0,0,0), SpawnParams);

        mobMover->addMob(mob_l);
    }
}
