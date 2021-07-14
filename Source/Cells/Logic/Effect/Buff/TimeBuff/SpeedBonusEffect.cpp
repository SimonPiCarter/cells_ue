// Fill out your copyright notice in the Description page of Project Settings.


#include "SpeedBonusEffect.h"
#include "../../../../TowerEntity.h"

USpeedBonusEffect::USpeedBonusEffect() : UTimeBuffEffect(), _bonus(0.f)
{
	setId("SpeedBonusEffect");
}

void USpeedBonusEffect::apply()
{
	_towerTarget->multAttackSpeed += _bonus * _stack;
}

void USpeedBonusEffect::revert()
{
	_towerTarget->multAttackSpeed -= _bonus * _stack;
}
