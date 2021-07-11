// Fill out your copyright notice in the Description page of Project Settings.


#include "BuffEffect.h"
#include "../../../MobEntity.h"
#include "../../../TowerEntity.h"

UBuffEffect::UBuffEffect() : _applied(false)
{}

void UBuffEffect::runEffect(float)
{
	// NA
}

/// @brief to be called to register the buff in the target
/// MUST BE CALLED when buff is applied
void UBuffEffect::registerBuff()
{
	if(_mobTarget)
	{
		_mobTarget->registerBuff(this);
	}
	else if(_towerTarget)
	{
		_towerTarget->registerBuff(this);
	}
}

/// @brief unregister the buff from the target
/// MUST BE CALLED when buff is reverted
void UBuffEffect::unregisterBuff()
{
	if(_mobTarget)
	{
		_mobTarget->unregisterBuff(this);
	}
	else if(_towerTarget)
	{
		_towerTarget->unregisterBuff(this);
	}
}

bool UBuffEffect::isRegistered()
{
	if(_mobTarget)
	{
		return _mobTarget->isRegistered(this);
	}
	else if(_towerTarget)
	{
		return _towerTarget->isRegistered(this);
	}
	return false;
}

UBuffEffect & UBuffEffect::getRegisteredBuff()
{
	UBuffEffect * ptr_l = nullptr;
	if(_mobTarget)
	{
		ptr_l = _mobTarget->getRegisteredBuff(this->getId());
	}
	else if(_towerTarget)
	{
		ptr_l = _towerTarget->getRegisteredBuff(this->getId());
	}
	if(!ptr_l) { throw std::logic_error("Looking for unregistered buff in UBuffEffect::getRegisteredBuff()"); }
	return *ptr_l;
}

void UBuffEffect::setIdImpl(FString const &id_p)
{
	_id = TCHAR_TO_UTF8(*id_p);
}
