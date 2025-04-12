#pragma once
#include <limits>
#include <cassert>
#include "Logger.h"
#include "Profiler.h"
#include "Paths.h"

namespace Crayon
{
#ifdef WINDOWS
    //ToDo: what's this for?
    //Oh, it's for input: so if you're getting an keypress event then if you're on Windows you'll set this to be a wchar_t. But... is this actually what we want? If we were on Linux etc, then would we want to use a utf-8 or whatever instead?

    //In other words, shouldn't this be, like, osCharacterFormat or something like that? isn't unicode_char = wchar_t just like saying unicodeCharacter=unicodeCharacter? What does this add?
    using unicode_char = wchar_t;
#endif

#ifdef DEBUG
#define CRAYON_ASSERT(x)  assert(x)
#else
#define CRAYON_ASSERT(x)
#endif

    class Core
    {
    public:
#undef max
        static constexpr size_t InvalidSize = std::numeric_limits<size_t>::max();
    };


    

}