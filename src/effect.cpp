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

Effect::Effect()
{
    for (int i = 0; i < SOUNDS_NUMBER; i++)
    {
        sounds.emplace_back();
    }

    EffectType effect_type_list[] = {
            EffectType::JUMP,
            EffectType::COIN_TOUCH,
            EffectType::LAVA_TOUCH,
            EffectType::LEVEL_END,
            EffectType::TIME_STOP,
    };
    for (EffectType effect_type: effect_type_list)
    {
        sf::SoundBuffer& buff = get_sound_buffer(effect_type);
        std::string sound_file = get_default_sound_file(effect_type);
        if (!buff.loadFromFile(sound_file))
        {
            std::string error = "Can't load sound effect file " + sound_file;
            throw EffectInitializationException(error);
        }
    }
}
void Effect::perform(EffectType effect)
{
    sf::SoundBuffer& buff = get_sound_buffer(effect);

    for (auto &sound: sounds)
    {
        if (sound.getStatus() != sf::Sound::Status::Playing)
        {
            sound.setBuffer(buff);
            sound.play();
            break;
        }
    }
}
