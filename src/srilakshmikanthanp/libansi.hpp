// Copyright (c) 2021 Sri Lakshmi Kanthan P
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#ifndef SRILAKSHMIKANTHANP_LIBANSI_HPP
#define SRILAKSHMIKANTHANP_LIBANSI_HPP

#define _USE_MATH_DEFINES

#include <iostream>
#include <string>
#include <sstream>
#include <math.h>

/**
 * @brief Some macros that makes code smaller
 */
#define TEMPLATE template <class CharT, class TraitsT>
#define OSTREAM std::basic_ostream<CharT, TraitsT>
#define STRING std::basic_string<CharT, TraitsT>
#define W(str) [](std::string arg) {     \
  return STRING(arg.begin(), arg.end()); \
}(std::string(str))

/**
 * @namespace srilakshmikanthanp::libansi
 * @brief  contains libansi escape sequence
 */
namespace srilakshmikanthanp
{
  namespace libansi
  {
    /**
     * @brief libansi to string
     */
    inline std::string str(std::ostream &(*manip)(std::ostream &))
    {
      std::ostringstream stream("");
      stream << manip;
      return stream.str();
    }

    /**
     * @brief libansi to str
     *
     * @tparam T type
     * @param obj object
     * @return STRING
     */
    template <class T>
    std::string str(T obj)
    {
      std::ostringstream stream("");
      stream << obj;
      return stream.str();
    }

    /**
     * @brief Moves the cursor up n (default 1) cells.
     *
     * If the cursor is already at the edge of the screen, this has no effect.
     */
    struct cursorup
    {
    private:
      int n;

    public:
      cursorup(int n = 1) : n{n} {}

      TEMPLATE
      friend OSTREAM &operator<<(OSTREAM &os, const cursorup &cup)
      {
        return os << W("\033[") << cup.n << W("A");
      }
    };

    /**
     * @brief Moves the cursor down n (default 1) cells.
     *
     * If the cursor is already at the edge of the screen, this has no effect.
     */
    struct cursordn
    {
    private:
      int n;

    public:
      cursordn(int n = 1) : n{n} {}

      TEMPLATE
      friend OSTREAM &operator<<(OSTREAM &os, const cursordn &cdn)
      {
        return os << W("\033[") << cdn.n << W("B");
      }
    };

    /**
     * @brief Moves the cursor forward n (default 1) cells.
     *
     * If the cursor is already at the edge of the screen, this has no effect.
     */
    struct cursorfw
    {
    private:
      int n;

    public:
      cursorfw(int n = 1) : n{n} {}

      TEMPLATE
      friend OSTREAM &operator<<(OSTREAM &os, const cursorfw &cfw)
      {
        return os << W("\033[") << cfw.n << W("C");
      }
    };

    /**
     * @brief Moves the cursor back n (default 1) cells.
     *
     * If the cursor is already at the edge of the screen, this has no effect.
     */
    struct cursorbk
    {
    private:
      int n;

    public:
      cursorbk(int n = 1) : n{n} {}

      TEMPLATE
      friend OSTREAM &operator<<(OSTREAM &os, const cursorbk &cbk)
      {
        return os << W("\033[") << cbk.n << W("D");
      }
    };

    /**
     * @brief Moves the cursor to beginning of line n (default 1) lines down.
     */
    struct cursornext
    {
    private:
      int n;

    public:
      cursornext(int n = 1) : n{n} {}

      TEMPLATE
      friend OSTREAM &operator<<(OSTREAM &os, const cursornext &cnext)
      {
        return os << W("\033[") << cnext.n << W("E");
      }
    };

    /**
     * @brief Moves the cursor to beginning of line n (default 1) lines up.
     */
    struct cursorprev
    {
    private:
      int n;

    public:
      cursorprev(int n = 1) : n{n} {}

      TEMPLATE
      friend OSTREAM &operator<<(OSTREAM &os, const cursorprev &cprev)
      {
        return os << W("\033[") << cprev.n << W("F");
      }
    };

    /**
     * @brief Moves the cursor horizontally to column n (default 1) in the current line.
     */
    struct cursorhoriz
    {
    private:
      int n;

    public:
      cursorhoriz(int n = 1) : n{n} {}

      TEMPLATE
      friend OSTREAM &operator<<(OSTREAM &os, const cursorhoriz &ch)
      {
        return os << W("\033[") << ch.n << W("G");
      }
    };

    /**
     * @brief Moves the cursor vertically to row n (default 1) in the current column.
     */
    struct cursorvert
    {
    private:
      int n;

    public:
      cursorvert(int n = 1) : n{n} {}

      TEMPLATE
      friend OSTREAM &operator<<(OSTREAM &os, const cursorvert &cbk)
      {
        return os << W("\033[") << cbk.n << W("d");
      }
    };

    /**
     * @brief Moves the cursor to row n, column m.
     */
    struct cursormov
    {
    private:
      int n, m;

    public:
      cursormov(int n, int m) : n{n}, m{m} {}

      TEMPLATE
      friend OSTREAM &operator<<(OSTREAM &os, const cursormov &cur)
      {
        return os << W("\033[") << cur.n << W(";") << cur.m << W("H");
      }
    };

    /**
     * @brief Clears part of the screen.
     *
     * If n is 0 (or missing), clear from cursor to end of screen.
     * If n is 1, clear from cursor to beginning of the screen.
     * If n is 2, clear entire screen (and moves cursor to upper
     * left on DOS libansi.SYS). If n is 3, clear entire screen and
     * delete all lines saved in the scrollback buffer
     * (this feature was added for xterm and is supported by
     * other terminal applications).
     */
    struct clrscr
    {
    private:
      int n;

    public:
      clrscr(int n = 0) : n{n} {}

      TEMPLATE
      friend OSTREAM &operator<<(OSTREAM &os, const clrscr &dis)
      {
        return os << W("\033[") << dis.n << W("J");
      }
    };

    /**
     * @brief Erases part of the line.
     *
     * If n is 0 (or missing),
     * clear from cursor to the end of the line. If n is 1,
     * clear from cursor to beginning of the line. If n is 2,
     * clear entire line. Cursor position does not change.
     */
    struct clrline
    {
    private:
      int n;

    public:
      clrline(int n = 0) : n{n} {}

      TEMPLATE
      friend OSTREAM &operator<<(OSTREAM &os, const clrline &lin)
      {
        return os << W("\033[") << lin.n << W("K");
      }
    };

    /**
     * @brief Scroll whole page up by n (default 1) lines.
     *
     * New lines are added at the bottom.
     */
    struct scrollup
    {
    private:
      int n;

    public:
      scrollup(int n = 1) : n{n} {}

      TEMPLATE
      friend OSTREAM &operator<<(OSTREAM &os, const scrollup &ref)
      {
        return os << W("\033[") << ref.n << W("S");
      }
    };

    /**
     * @brief Scroll whole page down by n (default 1) lines.
     *
     * New lines are added at the top.
     */
    struct scrolldn
    {
    private:
      int n;

    public:
      scrolldn(int n = 1) : n{n} {}

      TEMPLATE
      friend OSTREAM &operator<<(OSTREAM &os, const scrolldn &ref)
      {
        return os << W("\033[") << ref.n << W("T");
      }
    };

    /**
     * @brief Save Current Cursor Position
     */
    TEMPLATE
    OSTREAM &savepos(OSTREAM &os)
    {
      return os << W("\033[s");
    }

    /**
     * @brief Restore Saved Cursor Position
     */
    TEMPLATE
    OSTREAM &loadpos(OSTREAM &os)
    {
      return os << W("\033[u");
    }

    /**
     * @brief Shows the cursor, from the VT220.
     */
    TEMPLATE
    OSTREAM &showcursor(OSTREAM &os)
    {
      return os << W("\033[?25h");
    }

    /**
     * @brief Hides the cursor
     */
    TEMPLATE
    OSTREAM &hidecursor(OSTREAM &os)
    {
      return os << W("\033[?25l");
    }

    /**
     * @brief Reset manipulator
     */
    TEMPLATE
    OSTREAM &reset(OSTREAM &os)
    {
      return os << W("\033[0m");
    }

    /**
     * @brief Bold or increased intensity
     */
    TEMPLATE
    OSTREAM &bold(OSTREAM &os)
    {
      return os << W("\033[1m");
    }

    /**
     * @brief Faint, decreased intensity, or dim
     */
    TEMPLATE
    OSTREAM &faint(OSTREAM &os)
    {
      return os << W("\033[2m");
    }

    /**
     * @brief Italic
     */
    TEMPLATE
    OSTREAM &italic(OSTREAM &os)
    {
      return os << W("\033[3m");
    }

    /**
     * @brief Underline
     */
    TEMPLATE
    OSTREAM &underline(OSTREAM &os)
    {
      return os << W("\033[4m");
    }

    /**
     * @brief Slow blink
     */
    TEMPLATE
    OSTREAM &blink(OSTREAM &os)
    {
      return os << W("\033[5m");
    }

    /**
     * @brief Invert
     */
    TEMPLATE
    OSTREAM &invert(OSTREAM &os)
    {
      return os << W("\033[7m");
    }

    /**
     * @brief Conceal
     */
    TEMPLATE
    OSTREAM &conceal(OSTREAM &os)
    {
      return os << W("\033[8m");
    }

    /**
     * @brief Strike
     */
    TEMPLATE
    OSTREAM &strike(OSTREAM &os)
    {
      return os << W("\033[9m");
    }

    /**
     * @brief Font
     */
    struct font
    {
    private:
      int n;

    public:
      font(int n) : n{n} {}

      TEMPLATE
      friend OSTREAM &operator<<(OSTREAM &os, const font &ref)
      {
        if (ref.n >= 10 && ref.n <= 20)
        {
          return os << W("\033[") << ref.n << W("m");
        }

        return os;
      }
    };

    /**
     * @brief Normal intensity
     */
    TEMPLATE
    OSTREAM &normalintensity(OSTREAM &os)
    {
      return os << W("\033[22m");
    }

    /**
     * @brief Not italic
     */
    TEMPLATE
    OSTREAM &notitalic(OSTREAM &os)
    {
      return os << W("\033[23m");
    }

    /**
     * @brief Not underlined
     */
    TEMPLATE
    OSTREAM &notunderline(OSTREAM &os)
    {
      return os << W("\033[24m");
    }

    /**
     * @brief Not blinked
     */
    TEMPLATE
    OSTREAM &notblink(OSTREAM &os)
    {
      return os << W("\033[25m");
    }

    /**
     * @brief Proportional space
     */
    TEMPLATE
    OSTREAM &prospace(OSTREAM &os)
    {
      return os << W("\033[26m");
    }

    /**
     * @brief Not invert
     */
    TEMPLATE
    OSTREAM &notinvert(OSTREAM &os)
    {
      return os << W("\033[27m");
    }

    /**
     * @brief Not conceal
     */
    TEMPLATE
    OSTREAM &notconceal(OSTREAM &os)
    {
      return os << W("\033[28m");
    }

    /**
     * @brief Not strkie
     */
    TEMPLATE
    OSTREAM &notstrike(OSTREAM &os)
    {
      return os << W("\033[29m");
    }

    /**
     * @brief Foreground black
     */
    TEMPLATE
    OSTREAM &fg_black(OSTREAM &os)
    {
      return os << W("\033[30m");
    }

    /**
     * @brief Foreground red
     */
    TEMPLATE
    OSTREAM &fg_red(OSTREAM &os)
    {
      return os << W("\033[31m");
    }

    /**
     * @brief Foreground green
     */
    TEMPLATE
    OSTREAM &fg_green(OSTREAM &os)
    {
      return os << W("\033[32m");
    }

    /**
     * @brief Foreground yellow
     */
    TEMPLATE
    OSTREAM &fg_yellow(OSTREAM &os)
    {
      return os << W("\033[33m");
    }

    /**
     * @brief Foreground blue
     */
    TEMPLATE
    OSTREAM &fg_blue(OSTREAM &os)
    {
      return os << W("\033[34m");
    }

    /**
     * @brief Foreground magenta
     */
    TEMPLATE
    OSTREAM &fg_magenta(OSTREAM &os)
    {
      return os << W("\033[35m");
    }

    /**
     * @brief Foreground cyan
     */
    TEMPLATE
    OSTREAM &fg_cyan(OSTREAM &os)
    {
      return os << W("\033[36m");
    }

    /**
     * @brief Foreground white
     */
    TEMPLATE
    OSTREAM &fg_white(OSTREAM &os)
    {
      return os << W("\033[37m");
    }

    /**
     * @brief Foreground brightblack
     */
    TEMPLATE
    OSTREAM &fg_brightblack(OSTREAM &os)
    {
      return os << W("\033[90m");
    }

    /**
     * @brief Foreground brightred
     */
    TEMPLATE
    OSTREAM &fg_brightred(OSTREAM &os)
    {
      return os << W("\033[91m");
    }

    /**
     * @brief Foreground brightgreen
     */
    TEMPLATE
    OSTREAM &fg_brightgreen(OSTREAM &os)
    {
      return os << W("\033[92m");
    }

    /**
     * @brief Foreground brightyellow
     */
    TEMPLATE
    OSTREAM &fg_brightyellow(OSTREAM &os)
    {
      return os << W("\033[93m");
    }

    /**
     * @brief Foreground brightblue
     */
    TEMPLATE
    OSTREAM &fg_brightblue(OSTREAM &os)
    {
      return os << W("\033[94m");
    }

    /**
     * @brief Foreground brightmagenta
     */
    TEMPLATE
    OSTREAM &fg_brightmagenta(OSTREAM &os)
    {
      return os << W("\033[95m");
    }

    /**
     * @brief Foreground brightcyan
     */
    TEMPLATE
    OSTREAM &fg_brightcyan(OSTREAM &os)
    {
      return os << W("\033[96m");
    }

    /**
     * @brief Foreground brightwhite
     */
    TEMPLATE
    OSTREAM &fg_brightwhite(OSTREAM &os)
    {
      return os << W("\033[97m");
    }

    /**
     * @brief Foreground default
     */
    TEMPLATE
    OSTREAM &fg_default(OSTREAM &os)
    {
      return os << W("\033[39m");
    }

    /**
     * @brief Foreground color
     */
    struct fg_color
    {
    private:
      int n, r, g, b;

    public:
      fg_color(int r, int g, int b) : n{-1}, r{r}, g{g}, b{b} {}

      fg_color(int n) : n{n}, r{-1}, g{-1}, b{-1} {}

      TEMPLATE
      friend OSTREAM &operator<<(OSTREAM &os, const fg_color &ref)
      {
        if (ref.r >= 0 && ref.r <= 255 && ref.g >= 0 && ref.g <= 255 && ref.b >= 0 && ref.b <= 255)
        {
          return os << W("\033[38;2;") << ref.r << W(";") << ref.g << W(";") << ref.b << W("m");
        }
        else if (ref.n >= 0 && ref.n <= 255)
        {
          return os << W("\033[38;5;") << ref.n << W("m");
        }
        else
        {
          return os;
        }
      }
    };

    /**
     * @brief Background black
     */
    TEMPLATE
    OSTREAM &bg_black(OSTREAM &os)
    {
      return os << W("\033[40m");
    }

    /**
     * @brief Background red
     */
    TEMPLATE
    OSTREAM &bg_red(OSTREAM &os)
    {
      return os << W("\033[41m");
    }

    /**
     * @brief Background green
     */
    TEMPLATE
    OSTREAM &bg_green(OSTREAM &os)
    {
      return os << W("\033[42m");
    }

    /**
     * @brief Background yellow
     */
    TEMPLATE
    OSTREAM &bg_yellow(OSTREAM &os)
    {
      return os << W("\033[43m");
    }

    /**
     * @brief Background blue
     */
    TEMPLATE
    OSTREAM &bg_blue(OSTREAM &os)
    {
      return os << W("\033[44m");
    }

    /**
     * @brief Background magenta
     */
    TEMPLATE
    OSTREAM &bg_magenta(OSTREAM &os)
    {
      return os << W("\033[45m");
    }

    /**
     * @brief Background cyan
     */
    TEMPLATE
    OSTREAM &bg_cyan(OSTREAM &os)
    {
      return os << W("\033[46m");
    }

    /**
     * @brief Background white
     */
    TEMPLATE
    OSTREAM &bg_white(OSTREAM &os)
    {
      return os << W("\033[47m");
    }

    /**
     * @brief Background brightblack
     */
    TEMPLATE
    OSTREAM &bg_brightblack(OSTREAM &os)
    {
      return os << W("\033[100m");
    }

    /**
     * @brief Background brightred
     */
    TEMPLATE
    OSTREAM &bg_brightred(OSTREAM &os)
    {
      return os << W("\033[101m");
    }

    /**
     * @brief Background brightgreen
     */
    TEMPLATE
    OSTREAM &bg_brightgreen(OSTREAM &os)
    {
      return os << W("\033[102m");
    }

    /**
     * @brief Background brightyellow
     */
    TEMPLATE
    OSTREAM &bg_brightyellow(OSTREAM &os)
    {
      return os << W("\033[103m");
    }

    /**
     * @brief Background brightblue
     */
    TEMPLATE
    OSTREAM &bg_brightblue(OSTREAM &os)
    {
      return os << W("\033[104m");
    }

    /**
     * @brief Background brightmagenta
     */
    TEMPLATE
    OSTREAM &bg_brightmagenta(OSTREAM &os)
    {
      return os << W("\033[105m");
    }

    /**
     * @brief Background brightcyan
     */
    TEMPLATE
    OSTREAM &bg_brightcyan(OSTREAM &os)
    {
      return os << W("\033[96m");
    }

    /**
     * @brief Background brightwhite
     */
    TEMPLATE
    OSTREAM &bg_brightwhite(OSTREAM &os)
    {
      return os << W("\033[97m");
    }

    /**
     * @brief Background default
     */
    TEMPLATE
    OSTREAM &bg_default(OSTREAM &os)
    {
      return os << W("\033[49m");
    }

    /**
     * @brief Background color
     */
    struct bg_color
    {
    private:
      int n, r, g, b;

    public:
      bg_color(int r, int g, int b) : n{-1}, r{r}, g{g}, b{b} {}

      bg_color(int n) : n{n}, r{-1}, g{-1}, b{-1} {}

      TEMPLATE
      friend OSTREAM &operator<<(OSTREAM &os, const bg_color &ref)
      {
        if (ref.r >= 0 && ref.r <= 255 && ref.g >= 0 && ref.g <= 255 && ref.b >= 0 && ref.b <= 255)
        {
          return os << W("\033[48;2;") << ref.r << W(";") << ref.g << W(";") << ref.b << W("m");
        }
        else if (ref.n >= 0 && ref.n <= 255)
        {
          return os << W("\033[48;5;") << ref.n << W("m");
        }
        else
        {
          return os;
        }
      }
    };

    /**
     * @brief Not proprotional space
     */
    TEMPLATE
    OSTREAM &notprospace(OSTREAM &os)
    {
      return os << W("\033[50m");
    }

    /**
     * @brief Framed
     */
    TEMPLATE
    OSTREAM &framed(OSTREAM &os)
    {
      return os << W("\033[51m");
    }

    /**
     * @brief Encircled
     */
    TEMPLATE
    OSTREAM &encircled(OSTREAM &os)
    {
      return os << W("\033[52m");
    }

    /**
     * @brief Overlined
     */
    TEMPLATE
    OSTREAM &overlined(OSTREAM &os)
    {
      return os << W("\033[53m");
    }

    /**
     * @brief Not framed or encircled
     */
    TEMPLATE
    OSTREAM &notemoj(OSTREAM &os)
    {
      return os << W("\033[54m");
    }

    /**
     * @brief Not overlined
     */
    TEMPLATE
    OSTREAM &notoverlined(OSTREAM &os)
    {
      return os << W("\033[54m");
    }

    /**
     * @brief Underline default
     */
    TEMPLATE
    OSTREAM &defaultunderlinecolor(OSTREAM &os)
    {
      return os << W("\033[59m");
    }

    /**
     * @brief Underline color
     */
    struct underlinecolor
    {
    private:
      int n, r, g, b;

    public:
      underlinecolor(int r, int g, int b) : n{-1}, r{r}, g{g}, b{b} {}

      underlinecolor(int n) : n{n}, r{-1}, g{-1}, b{-1} {}

      TEMPLATE
      friend OSTREAM &operator<<(OSTREAM &os, const underlinecolor &ref)
      {
        if (ref.r >= 0 && ref.r <= 255 && ref.g >= 0 && ref.g <= 255 && ref.b >= 0 && ref.b <= 255)
        {
          return os << W("\033[38;2;") << ref.r << W(";") << ref.g << W(";") << ref.b << W("m");
        }
        else if (ref.n >= 0 && ref.n <= 255)
        {
          return os << W("\033[58;5;") << ref.n << W("m");
        }
        else
        {
          return os;
        }
      }
    };

    /**
     * @brief Superscript
     */
    TEMPLATE
    OSTREAM &supscript(OSTREAM &os)
    {
      return os << W("\033[73m");
    }

    /**
     * @brief Subscript
     */
    TEMPLATE
    OSTREAM &subscript(OSTREAM &os)
    {
      return os << W("\033[74m");
    }

    /**
     * @brief Not superscript or subscript
     */
    TEMPLATE
    OSTREAM &notscript(OSTREAM &os)
    {
      return os << W("\033[75m");
    }
  } // namespace libansi
} // namespace srilakshmikanthanp

/**
 * @brief undef macros
 */
#undef _USE_MATH_DEFINES
#undef TEMPLATE
#undef OSTREAM
#undef STRING
#undef W
#endif
