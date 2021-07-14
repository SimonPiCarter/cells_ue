// Fill out your copyright notice in the Description page of Project Settings.


#include "BuffOnDeathEffect.h"
#include "../TimeBuff/DmgBonusEffect.h"
#include "../TimeBuff/SpeedBonusEffect.h"
#include "../../../LogicEngine.h"

template<typename buff_t>
buff_t * spawnBuff(ALogicEngine * logic_p, ATowerEntity * source)
{
    // add bonus effect
    buff_t * buff_l = NewObject<buff_t>(logic_p);
    buff_l->_towerTarget = source;
    buff_l->source = source;
    logic_p->registerEffect(buff_l);
	return buff_l;
}

UDmgBonusOnDeathEffect::UDmgBonusOnDeathEffect() : UTriggerOnDeathEffect()
{
	setId("DmgBonusOnDeathEffect");
}

void UDmgBonusOnDeathEffect::deathTrigger()
{
	UDmgBonusEffect * buff_l = spawnBuff<UDmgBonusEffect>(logic, source);
	buff_l->_bonus = _bonus;
	buff_l->_maxStack = _maxStackBuff;
	buff_l->_duration = _durationBuff;
}

void UDmgBonusOnDeathEffect::init(int maxStack, float durationBuff, float bonus)
{
	_maxStackBuff = maxStack;
	_durationBuff = durationBuff;
	_bonus = bonus;
}

USpeedBonusOnDeathEffect::USpeedBonusOnDeathEffect() : UTriggerOnDeathEffect()
{
	setId("SpeedBonusOnDeathEffect");
}

void USpeedBonusOnDeathEffect::deathTrigger()
{
	USpeedBonusEffect * buff_l = spawnBuff<USpeedBonusEffect>(logic, source);
	buff_l->_bonus = _bonus;
	buff_l->_maxStack = _maxStackBuff;
	buff_l->_duration = _durationBuff;
}

void USpeedBonusOnDeathEffect::init(int maxStack, float durationBuff, float bonus)
{
	_maxStackBuff = maxStack;
	_durationBuff = durationBuff;
	_bonus = bonus;
}
