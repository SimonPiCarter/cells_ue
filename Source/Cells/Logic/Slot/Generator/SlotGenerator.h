#pragma once

#include "../../LogicEngine.h"
#include "../../BluePrintLibrary.h"
#include "../../Slot/Slot.h"

/// @brief This class is the base class for generator
/// of slot
class SlotGenerator
{
public:
    SlotGenerator(unsigned int frequency_p, unsigned int lvlMin_p, std::string const &blueprint_p) : _frequency(frequency_p), _lvlMin(lvlMin_p), _blueprint(blueprint_p) {}
    virtual ~SlotGenerator() {}

    /// @brief generate new slot
    virtual USlot * generate(ALogicEngine * logic_p, float level_p)
    {
		UBlueprint* blueprint_l = logic_p->library->getBluePrint("slot", _blueprint);
		// spawn
        USlot *slot_l = NewObject<USlot>(logic_p, (UClass*)blueprint_l->GeneratedClass);

        slot_l->setup(logic_p, level_p);

        return slot_l;
    }

    unsigned int getFrequency() const { return _frequency; }
    unsigned int getLvlMin() const { return _lvlMin; }

protected:
    unsigned int const _frequency;
    unsigned int const _lvlMin;
    std::string const _blueprint;
};
