//
// Created by elias on 24.02.2020.
//

#ifndef MINIPLATFORM_EFFECT_H
#define MINIPLATFORM_EFFECT_H

#include <exception>
#include <string>

#include <SFML/Audio.hpp>


class EffectInitializationException: std::runtime_error
{
public:
    explicit EffectInitializationException(std::string &reason);
};


enum class EffectType
{
    JUMP,
    COIN_TOUCH,
    LAVA_TOUCH,
    LEVEL_END,
    TIME_STOP,
};


class Effect
{
public:
    static Effect& get_instance();

    void perform(EffectType effect);

private:
    Effect();
    Effect(Effect const&);
    void operator=(Effect const&);

    static const int SOUNDS_NUMBER = 4;

    sf::SoundBuffer JUMP;
    sf::SoundBuffer COIN_TOUCH;
    sf::SoundBuffer LAVA_TOUCH;
    sf::SoundBuffer LEVEL_END;
    sf::SoundBuffer TIME_STOP;

    std::vector<sf::Sound> sounds;

    sf::SoundBuffer& get_sound_buffer(EffectType effect_type)
    {
        switch(effect_type)
        {
            case EffectType::JUMP: return JUMP;
            case EffectType::COIN_TOUCH: return COIN_TOUCH;
            case EffectType::LAVA_TOUCH: return LAVA_TOUCH;
            case EffectType::LEVEL_END: return LEVEL_END;
            case EffectType::TIME_STOP: return TIME_STOP;
            default: throw EffectInitializationException((std::string &)"Unrecognized effect type");
        }
    }

    static std::string get_default_sound_file(EffectType effect_type)
    {
        switch(effect_type)
        {
            case EffectType::JUMP: return "sounds/jump.wav";
            case EffectType::COIN_TOUCH: return "sounds/coin.wav";
            case EffectType::LAVA_TOUCH: return "sounds/fail.wav";
            case EffectType::LEVEL_END: return "sounds/victory.wav";
            case EffectType::TIME_STOP: return "sounds/time_stop.wav";
            default: throw EffectInitializationException((std::string &)"Unrecognized effect type");
        }
    }
};

#endif //MINIPLATFORM_EFFECT_H
