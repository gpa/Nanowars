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

#include "Util/InputUtil.hpp"

namespace nanowars {
namespace util {

    std::string toString(sf::Keyboard::Key key)
    {
		static_assert(sf::Keyboard::KeyCount == 101);
        #define insert_case(id) case sf::Keyboard::id: return #id
        switch(key)
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
}
}