// Fill out your copyright notice in the Description page of Project Settings.


#include "BuffDmgLastHitEffect.h"

#include <sstream>
#include <iomanip>
#include <cmath>

#include "../BuffEquipEffect.h"
#include "../../../../TowerEntity.h"

UBuffDmgLastHitEffect::UBuffDmgLastHitEffect() : UBuffEquipEffect(), _count(0), _switched(false)
{}

void UBuffDmgLastHitEffect::apply()
{
    if(!_switched)
    {
	    _towerTarget->multDamage -= 1.f - 1.f/(2.f*_factor);
    }
    else
    {
        _towerTarget->multDamage += _factor;
    }

}

void UBuffDmgLastHitEffect::revert()
{
    if(!_switched)
    {
	    _towerTarget->multDamage += 1.f - 1.f/(2.f*_factor);
    }
    else
    {
        _towerTarget->multDamage -= _factor;
    }
}

void UBuffDmgLastHitEffect::increaseCount()
{
    if(_count < 100)
    {
        ++_count;
        if(_count == 100)
        {
            this->switchBuff();
        }
    }
}

void UBuffDmgLastHitEffect::switchBuff()
{
    if(!_switched)
    {
        // revert debuff
        this->revert();
        _switched = true;
        this->apply();
    }
}
