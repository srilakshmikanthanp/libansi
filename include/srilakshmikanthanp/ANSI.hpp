// Copyright (c) 2021 Sri Lakshmi Kanthan P
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#ifndef ANSI_HPP
#define ANSI_HPP

#ifdef __linux__

    #include <iostream>
    #include <string>
    #include <sstream>

    int ANSI__init()
    {
        return 0;
    }

#elif _WIN32

    #include <iostream>
    #include <string>
    #include <sstream>
    #include <windows.h>

    int ANSI__init()
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

#endif

/**
 * @brief Some macros that makes code smaller 
 */
#define TEMPLATE template <class CharT, class TraitsT>
#define OSTREAM std::basic_ostream<CharT, TraitsT>
#define STRING std::basic_string<CharT>
#define W(str) [](std::string arg) {       \
    return STRING(arg.begin(), arg.end()); \
}(std::string(str))

/**
 * @namespace srilakshmikanthanp::ANSI
 * @brief  contains ansi escape sequence
 */
namespace srilakshmikanthanp::ANSI
{
    /**
     * @brief error code, Make sure it is zero
     * especially for windows platforms.
     */
    const int init_error = ANSI__init();

    /**
     * @brief ansi to string
     */
    std::string str(std::ostream &(*manip)(std::ostream &))
    {
        std::ostringstream stream("");
        stream << manip;
        return stream.str();
    }

    /**
     * @brief ansi to str
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
     * @brief Moves the cursor to row n, column m.
     */
    struct cursor
    {
    private:
        int n, m;

    public:
        cursor(int n, int m) : n{n}, m{m}
        {
        }

        TEMPLATE
        friend OSTREAM &operator<<(OSTREAM &os, const cursor &cur)
        {
            return os << W("\033[") << cur.n << W(";") << cur.m << W("H");
        }
    };

    /**
     * @brief Clears part of the screen. If n is 0 (or missing), 
     * clear from cursor to end of screen. 
     * If n is 1, clear from cursor to beginning of the screen. 
     * If n is 2, clear entire screen (and moves cursor to upper 
     * left on DOS ansi.SYS). If n is 3, clear entire screen and 
     * delete all lines saved in the scrollback buffer 
     * (this feature was added for xterm and is supported by 
     * other terminal applications).
     */
    struct clrscr
    {
    private:
        int n;

    public:
        clrscr(int n) : n{n}
        {
        }

        TEMPLATE
        friend OSTREAM &operator<<(OSTREAM &os, const clrscr &dis)
        {
            return os << W("\033[") << dis.n << W("J");
        }
    };

    /**
     * @brief Erases part of the line. If n is 0 (or missing),
     * clear from cursor to the end of the line. If n is 1, 
     * clear from cursor to beginning of the line. If n is 2, 
     * clear entire line. Cursor position does not change. 
     */
    struct clrlin
    {
    private:
        int n;

    public:
        clrlin(int n) : n{n}
        {
        }

        TEMPLATE
        friend OSTREAM &operator<<(OSTREAM &os, const clrlin &lin)
        {
            return os << W("\033[") << lin.n << W("K");
        }
    };

    /**
     * @brief Scroll whole page up by n (default 1) lines. 
     * New lines are added at the bottom.
     */
    struct scrollup
    {
    private:
        int n;

    public:
        scrollup(int n) : n{n}
        {
        }

        TEMPLATE
        friend OSTREAM &operator<<(OSTREAM &os, const scrollup &ref)
        {
            return os << W("\033[") << ref.n << W("S");
        }
    };

    /**
     * @brief Scroll whole page down by n (default 1) lines. 
     * New lines are added at the top.  
     */
    struct scrolldn
    {
    private:
        int n;

    public:
        scrolldn(int n) : n{n}
        {
        }

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
     * @brief Restore Saved Cursor Position
     */
    TEMPLATE
    OSTREAM &hidecursor(OSTREAM &os)
    {
        return os << W("\033[?25l");
    }

    /**
     * @brief reset manipulator
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
     * @brief italic 
     */
    TEMPLATE
    OSTREAM &italic(OSTREAM &os)
    {
        return os << W("\033[3m");
    }

    /**
     * @brief 	Underline
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
     * @brief invert
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
     * @brief strike
     */
    TEMPLATE
    OSTREAM &strike(OSTREAM &os)
    {
        return os << W("\033[9m");
    }

    /**
     * @brief font 
     */
    struct font
    {
    private:
        int n;

    public:
        font(int n) : n{n}
        {
        }

        TEMPLATE
        friend OSTREAM &operator<<(OSTREAM &os, const font &ref)
        {
            if (ref.n >= 10 && ref.n <= 20)
            {
                return os << W("\033[") << ref.n << W("m");
            }
            else
            {
                return os;
            }
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
     * @brief not italic
     */
    TEMPLATE
    OSTREAM &notitalic(OSTREAM &os)
    {
        return os << W("\033[23m");
    }

    /**
     * @brief not underlined
     */
    TEMPLATE
    OSTREAM &notunderline(OSTREAM &os)
    {
        return os << W("\033[24m");
    }

    /**
     * @brief not blinked
     */
    TEMPLATE
    OSTREAM &notblink(OSTREAM &os)
    {
        return os << W("\033[25m");
    }

    /**
     * @brief proportional space
     */
    TEMPLATE
    OSTREAM &prospace(OSTREAM &os)
    {
        return os << W("\033[26m");
    }

    /**
     * @brief not invert
     */
    TEMPLATE
    OSTREAM &notinvert(OSTREAM &os)
    {
        return os << W("\033[27m");
    }

    /**
     * @brief not conceal
     */
    TEMPLATE
    OSTREAM &notconceal(OSTREAM &os)
    {
        return os << W("\033[28m");
    }

    /**
     * @brief not strkie
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
    OSTREAM &FGblack(OSTREAM &os)
    {
        return os << W("\033[30m");
    }

    /**
     * @brief Foreground red
     */
    TEMPLATE
    OSTREAM &FGred(OSTREAM &os)
    {
        return os << W("\033[31m");
    }

    /**
     * @brief Foreground green
     */
    TEMPLATE
    OSTREAM &FGgreen(OSTREAM &os)
    {
        return os << W("\033[32m");
    }

    /**
     * @brief Foreground yellow
     */
    TEMPLATE
    OSTREAM &FGyellow(OSTREAM &os)
    {
        return os << W("\033[33m");
    }

    /**
     * @brief Foreground blue
     */
    TEMPLATE
    OSTREAM &FGblue(OSTREAM &os)
    {
        return os << W("\033[34m");
    }

    /**
     * @brief Foreground magenta
     */
    TEMPLATE
    OSTREAM &FGmagenta(OSTREAM &os)
    {
        return os << W("\033[35m");
    }

    /**
     * @brief Foreground cyan
     */
    TEMPLATE
    OSTREAM &FGcyan(OSTREAM &os)
    {
        return os << W("\033[36m");
    }

    /**
     * @brief Foreground white
     */
    TEMPLATE
    OSTREAM &FGwhite(OSTREAM &os)
    {
        return os << W("\033[37m");
    }

    /**
     * @brief Foreground brightblack
     */
    TEMPLATE
    OSTREAM &FGbrightblack(OSTREAM &os)
    {
        return os << W("\033[90m");
    }

    /**
     * @brief Foreground brightred
     */
    TEMPLATE
    OSTREAM &FGbrightred(OSTREAM &os)
    {
        return os << W("\033[91m");
    }

    /**
     * @brief Foreground brightgreen
     */
    TEMPLATE
    OSTREAM &FGbrightgreen(OSTREAM &os)
    {
        return os << W("\033[92m");
    }

    /**
     * @brief Foreground brightyellow
     */
    TEMPLATE
    OSTREAM &FGbrightyellow(OSTREAM &os)
    {
        return os << W("\033[93m");
    }

    /**
     * @brief Foreground brightblue
     */
    TEMPLATE
    OSTREAM &FGbrightblue(OSTREAM &os)
    {
        return os << W("\033[94m");
    }

    /**
     * @brief Foreground brightmagenta
     */
    TEMPLATE
    OSTREAM &FGbrightmagenta(OSTREAM &os)
    {
        return os << W("\033[95m");
    }

    /**
     * @brief Foreground brightcyan
     */
    TEMPLATE
    OSTREAM &FGbrightcyan(OSTREAM &os)
    {
        return os << W("\033[96m");
    }

    /**
     * @brief Foreground brightwhite
     */
    TEMPLATE
    OSTREAM &FGbrightwhite(OSTREAM &os)
    {
        return os << W("\033[97m");
    }

    /**
     * @brief Foreground default
     */
    TEMPLATE
    OSTREAM &FGdefault(OSTREAM &os)
    {
        return os << W("\033[39m");
    }

    /**
     * @brief Foreground color 
     */
    struct FGcolor
    {
    private:
        int n, r, g, b;

    public:
        FGcolor(int n) : n{n}, r{-1}, g{-1}, b{-1}
        {
        }

        FGcolor(int r, int g, int b) : n{-1}, r{r}, g{g}, b{b}
        {
        }

        TEMPLATE
        friend OSTREAM &operator<<(OSTREAM &os, const FGcolor &ref)
        {
            if (ref.n >= 0 && ref.n <= 255)
            {
                return os << W("\033[38;5;") << ref.n << W("m");
            }
            else if (ref.r >= 0 && ref.r <= 255 && ref.g >= 0 && ref.g <= 255 && ref.b >= 0 && ref.b <= 255)
            {
                return os << W("\033[38;2;") << ref.r << W(";") << ref.g << W(";") << ref.b << W("m");
            }
            else
            {
                return os;
            }
        }
    };

    /**
     * @brief background black
     */
    TEMPLATE
    OSTREAM &BGblack(OSTREAM &os)
    {
        return os << W("\033[40m");
    }

    /**
     * @brief background red
     */
    TEMPLATE
    OSTREAM &BGred(OSTREAM &os)
    {
        return os << W("\033[41m");
    }

    /**
     * @brief background green
     */
    TEMPLATE
    OSTREAM &BGgreen(OSTREAM &os)
    {
        return os << W("\033[42m");
    }

    /**
     * @brief background yellow
     */
    TEMPLATE
    OSTREAM &BGyellow(OSTREAM &os)
    {
        return os << W("\033[43m");
    }

    /**
     * @brief background blue
     */
    TEMPLATE
    OSTREAM &BGblue(OSTREAM &os)
    {
        return os << W("\033[44m");
    }

    /**
     * @brief background magenta
     */
    TEMPLATE
    OSTREAM &BGmagenta(OSTREAM &os)
    {
        return os << W("\033[45m");
    }

    /**
     * @brief background cyan
     */
    TEMPLATE
    OSTREAM &BGcyan(OSTREAM &os)
    {
        return os << W("\033[46m");
    }

    /**
     * @brief background white
     */
    TEMPLATE
    OSTREAM &BGwhite(OSTREAM &os)
    {
        return os << W("\033[47m");
    }

    /**
     * @brief background brightblack
     */
    TEMPLATE
    OSTREAM &BGbrightblack(OSTREAM &os)
    {
        return os << W("\033[100m");
    }

    /**
     * @brief background brightred
     */
    TEMPLATE
    OSTREAM &BGbrightred(OSTREAM &os)
    {
        return os << W("\033[101m");
    }

    /**
     * @brief background brightgreen
     */
    TEMPLATE
    OSTREAM &BGbrightgreen(OSTREAM &os)
    {
        return os << W("\033[102m");
    }

    /**
     * @brief background brightyellow
     */
    TEMPLATE
    OSTREAM &BGbrightyellow(OSTREAM &os)
    {
        return os << W("\033[103m");
    }

    /**
     * @brief background brightblue
     */
    TEMPLATE
    OSTREAM &BGbrightblue(OSTREAM &os)
    {
        return os << W("\033[104m");
    }

    /**
     * @brief background brightmagenta
     */
    TEMPLATE
    OSTREAM &BGbrightmagenta(OSTREAM &os)
    {
        return os << W("\033[105m");
    }

    /**
     * @brief background brightcyan
     */
    TEMPLATE
    OSTREAM &BGbrightcyan(OSTREAM &os)
    {
        return os << W("\033[96m");
    }

    /**
     * @brief background brightwhite
     */
    TEMPLATE
    OSTREAM &BGbrightwhite(OSTREAM &os)
    {
        return os << W("\033[97m");
    }

    /**
     * @brief background default
     */
    TEMPLATE
    OSTREAM &BGdefault(OSTREAM &os)
    {
        return os << W("\033[49m");
    }

    /**
     * @brief background color 
     */
    struct BGcolor
    {
    private:
        int n, r, g, b;

    public:
        BGcolor(int n) : n{n}, r{-1}, g{-1}, b{-1}
        {
        }

        BGcolor(int r, int g, int b) : n{-1}, r{r}, g{g}, b{b}
        {
        }

        TEMPLATE
        friend OSTREAM &operator<<(OSTREAM &os, const BGcolor &ref)
        {
            if (ref.n >= 0 && ref.n <= 255)
            {
                return os << W("\033[48;5;") << ref.n << W("m");
            }
            else if (ref.r >= 0 && ref.r <= 255 && ref.g >= 0 && ref.g <= 255 && ref.b >= 0 && ref.b <= 255)
            {
                return os << W("\033[48;2;") << ref.r << W(";") << ref.g << W(";") << ref.b << W("m");
            }
            else
            {
                return os;
            }
        }
    };

    /**
     * @brief not proprotional space
     */
    TEMPLATE
    OSTREAM &notprospace(OSTREAM &os)
    {
        return os << W("\033[50m");
    }

    /**
     * @brief framed
     */
    TEMPLATE
    OSTREAM &framed(OSTREAM &os)
    {
        return os << W("\033[51m");
    }

    /**
     * @brief encircled
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
     * @brief not framed or encircled
     */
    TEMPLATE
    OSTREAM &notemoj(OSTREAM &os)
    {
        return os << W("\033[54m");
    }

    /**
     * @brief not overlined
     */
    TEMPLATE
    OSTREAM &notoverlined(OSTREAM &os)
    {
        return os << W("\033[54m");
    }

    /**
     * @brief background default
     */
    TEMPLATE
    OSTREAM &defaultunderlinecolor(OSTREAM &os)
    {
        return os << W("\033[49m");
    }

    /**
     * @brief background color 
     */
    struct underlinecolor
    {
    private:
        int n, r, g, b;

    public:
        underlinecolor(int n) : n{n}, r{-1}, g{-1}, b{-1}
        {
        }

        underlinecolor(int r, int g, int b) : n{-1}, r{r}, g{g}, b{b}
        {
        }

        TEMPLATE
        friend OSTREAM &operator<<(OSTREAM &os, const underlinecolor &ref)
        {
            if (ref.n >= 0 && ref.n <= 255)
            {
                return os << W("\033[58;5;") << ref.n << W("m");
            }
            else if (ref.r >= 0 && ref.r <= 255 && ref.g >= 0 && ref.g <= 255 && ref.b >= 0 && ref.b <= 255)
            {
                return os << W("\033[58;2;") << ref.r << W(";") << ref.g << W(";") << ref.b << W("m");
            }
            else
            {
                return os;
            }
        }
    };

    /**
     * @brief super script
     */
    TEMPLATE
    OSTREAM &supscript(OSTREAM &os)
    {
        return os << W("\033[73m");
    }

    /**
     * @brief sub script
     */
    TEMPLATE
    OSTREAM &subscript(OSTREAM &os)
    {
        return os << W("\033[74m");
    }

} // namespace srilakshmikanthanp::ansi

/**
 * @brief undef macros 
 */
#undef TEMPLATE
#undef OSTREAM
#undef STRING
#undef W
#endif