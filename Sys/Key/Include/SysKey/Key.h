#ifndef SYSKEY_KEY_H
#define SYSKEY_KEY_H

namespace SysKey {
  enum class Key {
    A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P,
    Q, R, S, T, U, V, W, X, Y, Z,
    Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9, Num0,
    Up, Down, Right, Left,
    Enter, Space, Comma, Period, Tab, Backspace, Escape, Capslock,
    LeftAlt, LeftControl, RightShift, RightAlt, RightControl,
    Unknown,
    Count
  };
}

#endif
