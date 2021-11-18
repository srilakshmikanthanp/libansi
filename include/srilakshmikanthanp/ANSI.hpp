// Copyright (c) 2021 Sri Lakshmi Kanthan P
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#ifndef ANSI_HPP
#define ANSI_HPP

#define _USE_MATH_DEFINES

#ifdef __linux__

    #include <iostream>
    #include <string>
    #include <sstream>
    #include <math.h>

    int ANSI__init()
    {
        return 0;
    }

#elif _WIN32

    #include <iostream>
    #include <string>
    #include <sstream>
    #include <windows.h>
    #include <math.h>

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
 * @namespace srilakshmikanthanp::ansi
 * @brief  contains ansi escape sequence
 */
namespace srilakshmikanthanp {
namespace ansi
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
     * @brief Clears part of the screen.
     *
     * If n is 0 (or missing), clear from cursor to end of screen.
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
        clrscr(int n = 0) : n{n}
        {
        }

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
    struct clrlin
    {
    private:
        int n;

    public:
        clrlin(int n = 0) : n{n}
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
     *
     * New lines are added at the bottom.
     */
    struct scrollup
    {
    private:
        int n;

    public:
        scrollup(int n = 1) : n{n}
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
     *
     * New lines are added at the top.  
     */
    struct scrolldn
    {
    private:
        int n;

    public:
        scrolldn(int n = 1) : n{n}
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
        fg_color(int n) : n{n}, r{-1}, g{-1}, b{-1}
        {
        }

        fg_color(int r, int g, int b) : n{-1}, r{r}, g{g}, b{b}
        {
        }

        TEMPLATE
        friend OSTREAM &operator<<(OSTREAM &os, const fg_color &ref)
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
        bg_color(int n) : n{n}, r{-1}, g{-1}, b{-1}
        {
        }

        bg_color(int r, int g, int b) : n{-1}, r{r}, g{g}, b{b}
        {
        }

        TEMPLATE
        friend OSTREAM &operator<<(OSTREAM &os, const bg_color &ref)
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
     * @brief Colorize the given text
     */
    class colorize
    {
    private:
        double fq1, fq2, fq3, amp, cen, ps1, ps2, ps3;
        std::string str;

    public:
        /**
         * @brief Construct a new colorize object
         * 
         * @param str string
         */
        colorize(std::string str) : str(str)
        {
            fq1 = 2 * M_PI / str.size();
            fq2 = 2 * M_PI / str.size();
            fq3 = 2 * M_PI / str.size();
            amp = 127;
            cen = 128;
            ps1 = 0 * M_PI/3;
            ps2 = 2 * M_PI/3;
            ps3 = 4 * M_PI/3;  
        }

        /**
         * @brief output
         * 
         * @param os stream
         * @param obj obj
         * @return OSTREAM& stream
         */
        TEMPLATE
        friend OSTREAM& operator<<(OSTREAM& os, const colorize &obj)
        {
            int r = 0, g = 0, b = 0, v = 0;

            for(std::string::size_type i = 0; i < obj.str.size(); ++i)
            {
                if(!std::isspace(obj.str[i]))
                {
                    r  =  std::sin(obj.fq1 * v + obj.ps1) * obj.amp + obj.cen;
                    g  =  std::sin(obj.fq2 * v + obj.ps2) * obj.amp + obj.cen;
                    b  =  std::sin(obj.fq3 * v + obj.ps3) * obj.amp + obj.cen;
                    v  =  v + 1;
                    os << fg_color(r, g, b) << obj.str[i];
                }
                else
                {
                    os << obj.str[i];
                }
            }

            return os << reset;
        }
    };
} // namespace ansi
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