// Fill out your copyright notice in the Description page of Project Settings.


#include "BuffDmgLastHit.h"

#include <sstream>
#include <iomanip>
#include <cmath>

#include "../../../Effect/Buff/EquipBuff/BuffDmgLastHitEffect.h"

UBuffDmgLastHit::UBuffDmgLastHit() : UBuffOnEquip()
{}

void UBuffDmgLastHit::spawnEffectOnLastHit(ALogicEngine* engine, ATowerEntity* source, AMobEntity* target)
{
    UBuffDmgLastHitEffect * buff_l = static_cast<UBuffDmgLastHitEffect *>(_buff);

    buff_l->increaseCount();

    // update desc
    description = buildBasicDesc();
}

FString UBuffDmgLastHit::buildBasicDesc()
{
    UBuffDmgLastHitEffect * buff_l = static_cast<UBuffDmgLastHitEffect *>(_buff);

	std::stringstream ss_l;
	ss_l << "Reduce damage by <YellowReg>" << cround(100.f-1.f/(2.f*_factor)*100.f) << "%</>. After <YellowReg>" << 100 << "</> "
        << "last hit, damage is increased by <YellowReg>" << cround(_factor*100.f)
        << "%</>. Current last hits : <YellowReg>" << (buff_l?buff_l->getCount():0u) << "/100</>";

	std::string str_l = ss_l.str();
	return FString(str_l.c_str());
}
