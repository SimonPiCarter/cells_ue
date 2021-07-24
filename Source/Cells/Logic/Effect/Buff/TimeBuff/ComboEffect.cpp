// Fill out your copyright notice in the Description page of Project Settings.


#include "ComboEffect.h"
#include "../../../../MobEntity.h"
#include "../../../LogicEngine.h"
#include "../../AttackEffect.h"

UComboEffect::UComboEffect() : UTimeBuffEffect(), _dmg(0.f), _dmgType(DmgType::Standard), _dmgSpawned(false)
{
	setId("ComboEffect");
}
UComboEffect::UComboEffect(float duration_p, float dmg_p) : UTimeBuffEffect(duration_p), _dmg(dmg_p), _dmgType(DmgType::Standard), _dmgSpawned(false)
{
	setId("ComboEffect");
}

void UComboEffect::apply()
{
	bool shouldTrigger_l = true;
	std::list<UBuffEffect *> otherPieces_l;
	// Check that every required buff is registered in the mob
	for(FString const & str_l : _comboIdArray)
	{
		std::string strBuffId_l("ComboEffect_");
		strBuffId_l += std::string(TCHAR_TO_UTF8(*str_l));

		if(strBuffId_l == getId())
		{
			otherPieces_l.push_back(this);
			continue;
		}
		UBuffEffect * buff_l = _mobTarget->getRegisteredBuff(strBuffId_l);
		if(!buff_l)
		{
			shouldTrigger_l = false;
		}
		else
		{
			otherPieces_l.push_back(buff_l);
		}
	}

	// If we should trigger spawn dmg of every piece
	if(shouldTrigger_l)
	{
		spawnDmg();
		for(UBuffEffect * buff_l : otherPieces_l)
		{
			UComboEffect * combo_l = dynamic_cast<UComboEffect *>(buff_l);
			if(combo_l)
			{
				combo_l->spawnDmg();
			}
		}
	}
}

void UComboEffect::spawnDmg()
{
	// spaw dmg once
	if(_dmgSpawned)
	{
		return;
	}

	// add attack effect
	UAttackEffect * attackEffect_l = NewObject<UAttackEffect>(logic);
	attackEffect_l->_damage = _dmg;
	attackEffect_l->_dmgType = _dmgType;
	attackEffect_l->_mobTarget = _mobTarget;
	attackEffect_l->source = source;
	logic->registerEffect(attackEffect_l);
	_dmgSpawned = true;
	over = true;
}

void UComboEffect::init(FString id, TArray<FString> const &comboIdArray, float dmg, DmgType dmgType)
{
	setId("ComboEffect_"+std::string(TCHAR_TO_UTF8(*id)));
	_comboIdArray = comboIdArray;
	_dmg = dmg;
	_dmgType = dmgType;
}
