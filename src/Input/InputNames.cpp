/*
Copyright (c) 2019 Gratian Pawliszyn
This program is free software: you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the Free
Software Foundation, either version 3 of the License, or (at your option)
any later version.
This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
more details.
You should have received a copy of the GNU General Public License along with
this program. If not, see <http://www.gnu.org/licenses/>. */

#include "Input/InputNames.hpp"

namespace nanowars {
namespace input {

    std::string InputNames::toString(sf::Keyboard::Key key)
    {
        static_assert(sf::Keyboard::KeyCount == 101);
#define insert_case(id)    \
    case sf::Keyboard::id: \
        return #id
        switch (key)
        {
            insert_case(Unknown);
            insert_case(A);
            insert_case(B);
            insert_case(C);
            insert_case(D);
            insert_case(E);
            insert_case(F);
            insert_case(G);
            insert_case(H);
            insert_case(I);
            insert_case(J);
            insert_case(K);
            insert_case(L);
            insert_case(M);
            insert_case(N);
            insert_case(O);
            insert_case(P);
            insert_case(Q);
            insert_case(R);
            insert_case(S);
            insert_case(T);
            insert_case(U);
            insert_case(V);
            insert_case(W);
            insert_case(X);
            insert_case(Y);
            insert_case(Z);
            insert_case(Num0);
            insert_case(Num1);
            insert_case(Num2);
            insert_case(Num3);
            insert_case(Num4);
            insert_case(Num5);
            insert_case(Num6);
            insert_case(Num7);
            insert_case(Num8);
            insert_case(Num9);
            insert_case(Escape);
            insert_case(LControl);
            insert_case(LShift);
            insert_case(LAlt);
            insert_case(LSystem);
            insert_case(RControl);
            insert_case(RShift);
            insert_case(RAlt);
            insert_case(RSystem);
            insert_case(Menu);
            insert_case(LBracket);
            insert_case(RBracket);
            insert_case(SemiColon);
            insert_case(Comma);
            insert_case(Period);
            insert_case(Quote);
            insert_case(Slash);
            insert_case(BackSlash);
            insert_case(Tilde);
            insert_case(Equal);
            insert_case(Dash);
            insert_case(Space);
            insert_case(Return);
            insert_case(BackSpace);
            insert_case(Tab);
            insert_case(PageUp);
            insert_case(PageDown);
            insert_case(End);
            insert_case(Home);
            insert_case(Insert);
            insert_case(Delete);
            insert_case(Add);
            insert_case(Subtract);
            insert_case(Multiply);
            insert_case(Divide);
            insert_case(Left);
            insert_case(Right);
            insert_case(Up);
            insert_case(Down);
            insert_case(Numpad0);
            insert_case(Numpad1);
            insert_case(Numpad2);
            insert_case(Numpad3);
            insert_case(Numpad4);
            insert_case(Numpad5);
            insert_case(Numpad6);
            insert_case(Numpad7);
            insert_case(Numpad8);
            insert_case(Numpad9);
            insert_case(F1);
            insert_case(F2);
            insert_case(F3);
            insert_case(F4);
            insert_case(F5);
            insert_case(F6);
            insert_case(F7);
            insert_case(F8);
            insert_case(F9);
            insert_case(F10);
            insert_case(F11);
            insert_case(F12);
            insert_case(F13);
            insert_case(F14);
            insert_case(F15);
            insert_case(Pause);
        }
#undef insert_case
        return "Unknown";
    }

    sf::Keyboard::Key InputNames::toKey(std::string key)
    {
        static_assert(sf::Keyboard::KeyCount == 101);
#define insert_if(id) else if (key == #id) return sf::Keyboard::Key::id

        if (key == "A")
            return sf::Keyboard::Key::A;
        insert_if(B);
        insert_if(C);
        insert_if(D);
        insert_if(E);
        insert_if(F);
        insert_if(G);
        insert_if(H);
        insert_if(I);
        insert_if(J);
        insert_if(K);
        insert_if(L);
        insert_if(M);
        insert_if(N);
        insert_if(O);
        insert_if(P);
        insert_if(Q);
        insert_if(R);
        insert_if(S);
        insert_if(T);
        insert_if(U);
        insert_if(V);
        insert_if(W);
        insert_if(X);
        insert_if(Y);
        insert_if(Z);
        insert_if(Num0);
        insert_if(Num1);
        insert_if(Num2);
        insert_if(Num3);
        insert_if(Num4);
        insert_if(Num5);
        insert_if(Num6);
        insert_if(Num7);
        insert_if(Num8);
        insert_if(Num9);
        insert_if(Escape);
        insert_if(LControl);
        insert_if(LShift);
        insert_if(LAlt);
        insert_if(LSystem);
        insert_if(RControl);
        insert_if(RShift);
        insert_if(RAlt);
        insert_if(RSystem);
        insert_if(Menu);
        insert_if(LBracket);
        insert_if(RBracket);
        insert_if(SemiColon);
        insert_if(Comma);
        insert_if(Period);
        insert_if(Quote);
        insert_if(Slash);
        insert_if(BackSlash);
        insert_if(Tilde);
        insert_if(Equal);
        insert_if(Dash);
        insert_if(Space);
        insert_if(Return);
        insert_if(BackSpace);
        insert_if(Tab);
        insert_if(PageUp);
        insert_if(PageDown);
        insert_if(End);
        insert_if(Home);
        insert_if(Insert);
        insert_if(Delete);
        insert_if(Add);
        insert_if(Subtract);
        insert_if(Multiply);
        insert_if(Divide);
        insert_if(Left);
        insert_if(Right);
        insert_if(Up);
        insert_if(Down);
        insert_if(Numpad0);
        insert_if(Numpad1);
        insert_if(Numpad2);
        insert_if(Numpad3);
        insert_if(Numpad4);
        insert_if(Numpad5);
        insert_if(Numpad6);
        insert_if(Numpad7);
        insert_if(Numpad8);
        insert_if(Numpad9);
        insert_if(F1);
        insert_if(F2);
        insert_if(F3);
        insert_if(F4);
        insert_if(F5);
        insert_if(F6);
        insert_if(F7);
        insert_if(F8);
        insert_if(F9);
        insert_if(F10);
        insert_if(F11);
        insert_if(F12);
        insert_if(F13);
        insert_if(F14);
        insert_if(F15);
        insert_if(Pause);
#undef insert_if
        return sf::Keyboard::Key::Unknown;
    }
}
}