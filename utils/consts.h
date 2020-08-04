#include <Arduboy2.h>

#pragma once


enum class Direction : uint8_t {

    Left,
    Right,
    Up,
    Down,

};

enum class XPosition : uint8_t {

    LH_Attack,
    LH_Position4,
    LH_Position3,
    LH_Position2,
    LH_Position1,
    Centre,
    RH_Position1,
    RH_Position2,
    RH_Position3,
    RH_Position4,
    RH_Attack,

};

inline XPosition &operator++(XPosition &c ) {
    c = static_cast<XPosition>( static_cast<uint8_t>(c) + 1 );
    return c;
}

inline XPosition operator++(XPosition &c, int ) {
    XPosition result = c;
    ++c;
    return result;
}

inline XPosition &operator--(XPosition &c ) {
    c = static_cast<XPosition>( static_cast<uint8_t>(c) - 1 );
    return c;
}

inline XPosition operator--(XPosition &c, int ) {
    XPosition result = c;
    --c;
    return result;
}

enum class YPosition : uint8_t {

    Level_1,
    Level_2,
    Level_3

};

inline YPosition &operator++(YPosition &c ) {
    c = static_cast<YPosition>( static_cast<uint8_t>(c) + 1 );
    return c;
}

inline YPosition operator++(YPosition &c, int ) {
    YPosition result = c;
    ++c;
    return result;
}

inline YPosition &operator--(YPosition &c ) {
    c = static_cast<YPosition>( static_cast<uint8_t>(c) - 1 );
    return c;
}

inline YPosition operator--(YPosition &c, int ) {
    YPosition result = c;
    --c;
    return result;
}

namespace Constants {

    constexpr uint8_t Player1_Index = 1;
    constexpr uint8_t Player1_XPos = 0;
    constexpr YPosition Player1_YPos = YPosition::Level_1;
  
    constexpr uint8_t Player2_Index = 2;
    constexpr uint8_t Player2_XPos = 90;
    constexpr YPosition Player2_YPos = YPosition::Level_1;

    constexpr uint8_t Level_1 = 0;
    constexpr uint8_t Level_2 = 1;
    constexpr uint8_t Level_3 = 2;
 
}