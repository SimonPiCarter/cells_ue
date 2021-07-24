// Fill out your copyright notice in the Description page of Project Settings.


#include "EffectMaker.h"

#include <sstream>
#include <iomanip>
#include <cmath>

UEffectMaker::UEffectMaker()
	: USlot(false, true)
	, _buffOnAttack(false)
	, _buffOnHit(false)
	, _buffOnLastHit(false)
	, _buffOnEquip(false)
{}

UEffectMaker::UEffectMaker(bool buffOnAttack_p, bool buffOnHit_p, bool buffOnLastHit_p, bool buffOnEquip_p)
	: USlot(false, true)
	, _buffOnAttack(buffOnAttack_p)
	, _buffOnHit(buffOnHit_p)
	, _buffOnLastHit(buffOnLastHit_p)
	, _buffOnEquip(buffOnEquip_p)
{}
