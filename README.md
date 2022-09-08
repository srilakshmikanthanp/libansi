<!--
 Copyright (c) 2021 Sri Lakshmi Kanthan P
 
 This software is released under the MIT License.
 https://opensource.org/licenses/MIT
-->

<!-- PROJECT LOGO -->
<br />
  <h3 align="center">libansi</h3>

  <p align="center">
    ANSI escape sequence
    <br />
    <a href="https://srilakshmikanthanp.github.io/libansi/docs/html"><strong>Explore the docs »</strong></a>
    <br />
    <a href="https://github.com/srilakshmikanthanp/libansi/issues">Report Bug</a>
    ·
    <a href="https://github.com/srilakshmikanthanp/libansi/issues">Request Feature</a>
  </p>
</p>

<!-- TABLE OF CONTENTS -->
<details open="open">
  <summary><h2 style="display: inline-block">Table of Contents</h2></summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
  </ol>
</details>

<!-- ABOUT THE PROJECT -->
## About The Project

This is a wrapper over ANSI escape sequence for color, cursor movementand etc.

<!-- GETTING STARTED -->
## Getting Started

### Installation

It's a Header only library so just download `libansi.hpp`

<!-- USAGE EXAMPLES -->
## Usage

Usage is very easy this library uses manipulators to make work easy, if you are using windows you may need to enable virtual terminal processing,

~~~cpp
// sample to enable
int EnableVirtualTerminalProcessing()
{
  HANDLE StdOut = GetStdHandle(STD_OUTPUT_HANDLE);

  if (StdOut != INVALID_HANDLE_VALUE)
  {
    DWORD mode = 0;
    if (GetConsoleMode(StdOut, &mode))
    {
      mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
      if (SetConsoleMode(StdOut, mode))
      {
        return 0;
      }
    }
  }

  return GetLastError();
}
~~~

**3 and 4 bit colors:**

~~~cpp
// background
std::cout << ansi::bg_yellow;
// foreground
std::cout << ansi::fg_blue;
// output
std::cout << "Blue on yellow";
// reset
std::cout << ansi::reset;
~~~

**8 bit color:**

~~~cpp
// background
std::cout << ansi::bg_color(157);
// foreground
std::cout << ansi::fg_color(100);
// outpt
std::cout << "8 bit color";
// reset
std::cout << ansi::reset;
~~~

**24 bit color:**

~~~cpp
// background
std::cout << libansi::bg_color(0, 255, 0);
// foreground
std::cout << libansi::fg_color(0, 0, 255);
// output
std::cout << "24 bit color";
// reset
std::cout << libansi::reset;
~~~

**to string:**

You can easily convert this manipulators to string by using `ansi::str`

~~~cpp
std::string bg_yellow = libansi::str(ansi::bg_yellow);
std::string fg_blue   = libansi::str(ansi::fg_blue);
std::string reset     = libansi::str(ansi::reset);

std::cout << bg_yelow;
// foreground
std::cout << fg_blue;
// output
std::cout << "Blue on Yellow";
// reset
std::cout << reset;
~~~

_For more examples, please refer to the [Documentation]("https://srilakshmikanthanp.github.io/libansi/docs/html")_

<!-- CONTRIBUTING -->
## Contributing

Contributions are what make the open source community such an amazing place to be learn, inspire, and create. Any contributions you make are **greatly appreciated**.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE` for more information.

<!-- CONTACT -->
## Contact

Project Link: [https://github.com/srilakshmikanthanp/libansi](https://github.com/srilakshmikanthanp/libansi)
