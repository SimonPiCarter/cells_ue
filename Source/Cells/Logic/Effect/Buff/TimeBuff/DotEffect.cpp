// Fill out your copyright notice in the Description page of Project Settings.


#include "DotEffect.h"
#include "../../../../MobEntity.h"
#include "../../../LogicEngine.h"
#include "../../AttackEffect.h"

UDotEffect::UDotEffect() : UTimeBuffEffect(), _dotTime(0.f), _dmg(0.f), _dmgType(DmgType::Standard), _lethal(true)
{
	setId("DotEffect");
}
UDotEffect::UDotEffect(float duration_p, float dmg_p) : UTimeBuffEffect(duration_p), _dmg(dmg_p), _dmgType(DmgType::Standard), _lethal(true)
{
	setId("DotEffect");
}

void UDotEffect::updateBuff(float)
{
	if(_mobTarget->hitpoint <= 0.f
	|| (_mobTarget->hitpoint <= 1.f && !_lethal) )
	{
		over = true;
		return;
	}
	float step_l = 1.f;
	while(_fullElapsedTime - _dotTime > step_l)
	{
		_dotTime += step_l;

		// add attack effect
		UAttackEffect * attackEffect_l = NewObject<UAttackEffect>(logic);
		attackEffect_l->_damage = _dmg * _stack;
		attackEffect_l->_dmgType = _dmgType;
		attackEffect_l->_lethal = _lethal;
		attackEffect_l->_mobTarget = _mobTarget;
		attackEffect_l->source = source;
		logic->registerEffect(attackEffect_l);
	}
}
