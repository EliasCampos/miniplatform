//
// Created by elias on 24.02.2020.
//

#include "../includes/miniplatform/effect.h"

EffectInitializationException::EffectInitializationException(std::string &reason): std::runtime_error(reason) {}


Effect& Effect::get_instance()
{
    static Effect instance;
    return instance;
}


void Effect::perform(EffectType effect)
{
    sf::SoundBuffer& buff = get_sound_buffer(effect);
    sound.setBuffer(buff);
    sound.play();
}

Effect::Effect()
{
    EffectType effect_type_list[] = {EffectType::JUMP, EffectType::COIN_TOUCH, EffectType::LAVA_TOUCH, EffectType::LEVEL_END};
    for (EffectType effect_type: effect_type_list)
    {
        sf::SoundBuffer& buff = get_sound_buffer(effect_type);
        sf::String sound_file = get_default_sound_file(effect_type);
        if (!buff.loadFromFile(sound_file))
        {
            std::string error = "Can't load sound effect file " + sound_file;
            throw EffectInitializationException(error);
        }
    }
}
