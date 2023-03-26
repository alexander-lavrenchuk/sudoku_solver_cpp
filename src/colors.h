#pragma once
#ifndef _COLORS_H_
#define _COLORS_H_

#include <string>

/* PREFIX */
#define PREFIX              "\033["

/* JOIN STRING */
#define JOIN                ";"

/* COLORS */
#define RESET	            0

#define FOREGROUND_BLACK    30
#define FOREGROUND_RED 	    31
#define FOREGROUND_GREEN    32
#define FOREGROUND_YELLOW   33
#define FOREGROUND_BLUE	    34
#define FOREGROUND_MAGENTA  35
#define FOREGROUND_CYAN	    36
#define FOREGROUND_WHITE    37

#define BACKGROUND_BLACK    40
#define BACKGROUND_RED 	    41
#define BACKGROUND_GREEN    42
#define BACKGROUND_YELLOW   43
#define BACKGROUND_BLUE	    44
#define BACKGROUND_MAGENTA  45
#define BACKGROUND_CYAN	    46
#define BACKGROUND_WHITE    47

/* STYLES */
#define BOLD                1
#define DIM                 2
#define ITALIC              3
#define UNDERLINE           4
#define REVERSE             7

namespace colors {
    using namespace std;

    string format_string = PREFIX;
    
    template<typename T>
    string set_format(T style) {
        string format_string_backup;
        format_string += to_string(style) + "m";    
        format_string_backup = format_string;
        format_string = PREFIX;
        return format_string_backup;
    }
    
    template<typename T, typename... Args>
    string set_format(T style, Args... args) {
        format_string += to_string(style) + JOIN;
        return set_format(args...);
    }
    
    string reset_format() {
        format_string = PREFIX;
        return (string)PREFIX + "0m";
    }
}   // namespace colors

#endif  /* _COLORS_H_ */
// "\033[1;31mbold red text\033[0m\n"
// ANSI colors https://en.wikipedia.org/wiki/ANSI_escape_code

