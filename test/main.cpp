// Copyright (c) 2022 Sri Lakshmi Kanthan P
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include "../include/srilakshmikanthanp/libansi.hpp"

using namespace srilakshmikanthanp;

int main()
{
    // background
    std::cout << libansi::bg_yellow;
    // foreground
    std::cout << libansi::fg_blue;
    // output
    std::cout << "Blue on yellow\n";
    // reset
    std::cout << libansi::reset;

    // background
    std::cout << libansi::bg_color(157);
    // foreground
    std::cout << libansi::fg_color(100);
    // outpt
    std::cout << "8 bit color\n";
    // reset
    std::cout << libansi::reset;

    // background
    std::cout << libansi::bg_color(0, 255, 0);
    // foreground
    std::cout << libansi::fg_color(0, 0, 255);
    // output
    std::cout << "24 bit color\n";
    // reset
    std::cout << libansi::reset;

    // done
    return 0;
}
