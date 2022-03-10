// Copyright (c) 2022 Sri Lakshmi Kanthan P
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include "../include/srilakshmikanthanp/ANSI.hpp"

using namespace srilakshmikanthanp;

int main()
{
    // background
    std::cout << ansi::bg_yellow;
    // foreground
    std::cout << ansi::fg_blue;
    // output
    std::cout << "Blue on yellow\n";
    // reset
    std::cout << ansi::reset;

    // background
    std::cout << ansi::bg_color(157);
    // foreground
    std::cout << ansi::fg_color(100);
    // outpt
    std::cout << "8 bit color\n";
    // reset
    std::cout << ansi::reset;

    // background
    std::cout << ansi::bg_color(0, 255, 0);
    // foreground
    std::cout << ansi::fg_color(0, 0, 255);
    // output
    std::cout << "24 bit color\n";
    // reset
    std::cout << ansi::reset;

    // done
    return 0;
}
