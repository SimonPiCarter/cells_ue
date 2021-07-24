// Fill out your copyright notice in the Description page of Project Settings.


#include "BuffEquipEffect.h"
#include "../../../MobEntity.h"
#include "../../../TowerEntity.h"

UBuffEquipEffect::UBuffEquipEffect() : UBuffEffect()
{}

void UBuffEquipEffect::runEffect(float)
{
	// NA
	// equipment effect are handled directly when assigning slots
}
