// Fill out your copyright notice in the Description page of Project Settings.


#include "DmgBonusEffect.h"
#include "../../../../TowerEntity.h"

UDmgBonusEffect::UDmgBonusEffect() : UTimeBuffEffect()
{
	setId("DmgBonusEffect");
}

void UDmgBonusEffect::apply()
{
	_towerTarget->multDamage += _bonus * _stack;
}

void UDmgBonusEffect::revert()
{
	_towerTarget->multDamage -= _bonus * _stack;
}
