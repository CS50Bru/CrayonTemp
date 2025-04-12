//an enum naming the Win32 keycodes
//Tully, J., 2010. Keys Enumeration Win32. [online] Codeproject.com. 
//Available at: <https://www.codeproject.com/Tips/73227/Keys-Enumeration-Win32> [Accessed 7 June 2022].

#pragma once
#include<string>
#include<vector>
namespace Crayon
{

#define LINK_NAME_TO_VALUE \
    X(Backspace, 0x08) \
    X(Tab, 0x09) \
    X(Clear, 0x0C) \
    X(Enter, 0x0D) \
    X(Shift, 0x10) \
    X(Control, 0x11) \
    X(Alt, 0x12) \
    X(Pause, 0x13) \
    X(CapsLock, 0x14) \
    X(Escape, 0x1B) \
    X(Space, 0x20) \
    X(PageUp, 0x21) \
    X(PageDown, 0x22) \
    X(End, 0x23) \
    X(Home, 0x24) \
    X(Left, 0x25) \
    X(Up, 0x26) \
    X(Right, 0x27) \
    X(Down, 0x28) \
    X(Select, 0x29) \
    X(Print, 0x2A) \
    X(Execute, 0x2B) \
    X(PrintScreen, 0x2C) \
    X(Insert, 0x2D) \
    X(Delete, 0x2E) \
    X(Help, 0x2F) \
    X(Zero, 0x30) \
    X(One, 0x31) \
    X(Two, 0x32) \
    X(Three, 0x33) \
    X(Four, 0x34) \
    X(Five, 0x35) \
    X(Six, 0x36) \
    X(Seven, 0x37) \
    X(Eight, 0x38) \
    X(Nine, 0x39) \
    X(A, 0x41) \
    X(B, 0x42) \
    X(C, 0x43) \
    X(D, 0x44) \
    X(E, 0x45) \
    X(F, 0x46) \
    X(G, 0x47) \
    X(H, 0x48) \
    X(I, 0x49) \
    X(J, 0x4A) \
    X(K, 0x4B) \
    X(L, 0x4C) \
    X(M, 0x4D) \
    X(N, 0x4E) \
    X(O, 0x4F) \
    X(P, 0x50) \
    X(Q, 0x51) \
    X(R, 0x52) \
    X(S, 0x53) \
    X(T, 0x54) \
    X(U, 0x55) \
    X(V, 0x56) \
    X(W, 0x57) \
    X(X, 0x58) \
    X(Y, 0x59) \
    X(Z, 0x5A) \
    X(LeftWindowsKey, 0x5B) \
    X(RightWindowsKey, 0x5C) \
    X(ApplicationsKey, 0x5D) \
    X(Sleep, 0x5F) \
    X(NumPad0, 0x60) \
    X(NumPad1, 0x61) \
    X(NumPad2, 0x62) \
    X(NumPad3, 0x63) \
    X(NumPad4, 0x64) \
    X(NumPad5, 0x65) \
    X(NumPad6, 0x66) \
    X(NumPad7, 0x67) \
    X(NumPad8, 0x68) \
    X(NumPad9, 0x69) \
    X(Multiply, 0x6A) \
    X(Add, 0x6B) \
    X(Separator, 0x6C) \
    X(Subtract, 0x6D) \
    X(Decimal, 0x6E) \
    X(Divide, 0x6F) \
    X(F1, 0x70) \
    X(F2, 0x71) \
    X(F3, 0x72) \
    X(F4, 0x73) \
    X(F5, 0x74) \
    X(F6, 0x75) \
    X(F7, 0x76) \
    X(F8, 0x77) \
    X(F9, 0x78) \
    X(F10, 0x79) \
    X(F11, 0x7A) \
    X(F12, 0x7B) \
    X(F13, 0x7C) \
    X(F14, 0x7D) \
    X(F15, 0x7E) \
    X(F16, 0x7F) \
    X(F17, 0x80) \
    X(F18, 0x81) \
    X(F19, 0x82) \
    X(F20, 0x83) \
    X(F21, 0x84) \
    X(F22, 0x85) \
    X(F23, 0x86) \
    X(F24, 0x87) \
    X(Numlock, 0x90) \
    X(ScrollLock, 0x91) \
    X(LeftShift, 0xA0) \
    X(RightShift, 0xA1) \
    X(LeftControl, 0xA2) \
    X(RightControl, 0xA3) \
    X(LeftMenu, 0xA4) \
    X(RightMenu, 0xA5) \
    X(BrowserBack, 0xA6) \
    X(BrowserForward, 0xA7) \
    X(BrowserRefresh, 0xA8) \
    X(BrowserStop, 0xA9) \
    X(BrowserSearch, 0xAA) \
    X(BrowserFavorites, 0xAB) \
    X(BrowserHome, 0xAC) \
    X(VolumeMute, 0xAD) \
    X(VolumeDown, 0xAE) \
    X(VolumeUp, 0xAF) \
    X(NextTrack, 0xB0) \
    X(PreviousTrack, 0xB1) \
    X(StopMedia, 0xB2) \
    X(PlayPause, 0xB3) \
    X(LaunchMail, 0xB4) \
    X(SelectMedia, 0xB5) \
    X(LaunchApp1, 0xB6) \
    X(LaunchApp2, 0xB7) \
    X(OEM1, 0xBA) \
    X(OEMPlus, 0xB8) \
    X(OEMComma, 0xBC) \
    X(OEMMinus, 0xBD) \
    X(OEMPeriod, 0xBE) \
    X(OEM2, 0xBF) \
    X(OEM3, 0xC0) \
    X(OEM4, 0xDB) \
    X(OEM5, 0xDC) \
    X(OEM6, 0xDD) \
    X(OEM7, 0xDE) \
    X(OEM8, 0xDF) \
    X(OEM102, 0xE2) \
    X(Process, 0xE5) \
    X(Packet, 0xE7) \
    X(Attn, 0xF6) \
    X(CrSel, 0xF7) \
    X(ExSel, 0xF8) \
    X(EraseEOF, 0xF9) \
    X(Play, 0xFA) \
    X(Zoom, 0xFB) \
    X(PA1, 0xFD) \
    X(OEMClear, 0xFE)\
    X(MouseLeft, 0x01) \
    X(MouseRight, 0x02) \
    X(MouseMiddle, 0x04)\
    X(InvalidValue, 0x00)\
    X(MouseMove, 0xFF)\
    X(MouseWheel, 0x100)



        //Ok, let's create our enum class:
    #define X(name, value) name = value,

enum class InputName : size_t
{
    LINK_NAME_TO_VALUE
    Size
    #undef X
     };

    constexpr size_t inputNameCount = static_cast<size_t>(InputName::Size);


    inline std::vector<std::string> generateKeyNames()
    {
        std::vector<std::string> keyCodeStringPairs(inputNameCount, "Unnamed Input");

    #define X(name, value) keyCodeStringPairs[value]=#name;
        LINK_NAME_TO_VALUE
    #undef X

        return keyCodeStringPairs;
    }

    inline const std::string& getKeyNameAsString( InputName keyCode )
    {
        using KeyCodeStringPair = std::pair<InputName, std::string>;
        static std::vector<std::string> keyCodeStringPairs = generateKeyNames();
        return ( keyCodeStringPairs[static_cast<size_t>(keyCode)] );
    }

}
