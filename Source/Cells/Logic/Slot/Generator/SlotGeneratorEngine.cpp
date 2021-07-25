#include "SlotGeneratorEngine.h"

#include "../../LogicEngine.h"
#include <vector>

namespace
{
    /// @brief add generator one time per frequency if level requirement is met
    void addGeneratorToVector(std::vector<SlotGenerator *> &vec_p, float baseLevel_p, SlotGenerator *generetor_p)
    {
        if(float(generetor_p->getLvlMin()) < baseLevel_p)
        {
            // add generator one time per frequency
            for(unsigned int i = 0 ; i < generetor_p->getFrequency() ; ++ i)
            {
                vec_p.push_back(generetor_p);
            }
        }
    }
}

SlotGeneratorEngine::~SlotGeneratorEngine()
{
    for(SlotGenerator *generator_l : _listGenerators)
    {
        delete generator_l;
    }
}

/// @brief generate count_p slots using a slot level baseLevel_p
std::list<USlot *> SlotGeneratorEngine::generateSlots(unsigned int count_p, ALogicEngine *logic_p, float minLevel_p, float maxLevel_p)
{
    // create vector using frequency of every generator available for given level
    std::vector<SlotGenerator *> gen_l;
    for(SlotGenerator *generator_l : _listGenerators)
    {
        // add generator to vector if possible
        addGeneratorToVector(gen_l, minLevel_p, generator_l);
    }

    // generate slots
    std::list<USlot *> slots_l;

    for(unsigned int i = 0 ; i < count_p && gen_l.size() > 0 ; ++ i)
    {
        float level_l = logic_p->genUniform(minLevel_p, maxLevel_p);
        int rand_l = logic_p->genIntUniform(0, gen_l.size()-1);
        slots_l.push_back(gen_l[rand_l]->generate(logic_p, level_l));
    }

    return slots_l;
}

void SlotGeneratorEngine::addGenerator(unsigned int frequency_p, unsigned int lvlMin_p, std::string const &blueprint_p)
{
    _listGenerators.push_back(new SlotGenerator(frequency_p, lvlMin_p, blueprint_p));
}
