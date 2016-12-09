#include <SDL2/SDL_mixer.h>
#include "soundstructs.hpp"

namespace ice
{
namespace sound
{

Effect::~Effect()
{
    if (pChunk_)
    {
        Mix_FreeChunk(pChunk_);
        pChunk_ = nullptr;
    }
}

void Effect::Play()
{
    if (!pChunk_) return;
    Mix_PlayChannelTimed(-1, pChunk_, 0, -1);
}

} // namespace sound
} // namespace ice
