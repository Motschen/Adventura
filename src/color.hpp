#include <iostream>

enum class Color {
    RESET = 0,
    BRIGHT_BLACK= 90,
    BRIGHT_RED= 91,
    BRIGHT_GREEN= 92,
    BRIGHT_YELLOW= 93,
    BRIGHT_BLUE= 94,
    BRIGHT_MAGENTA= 95,
    BRIGHT_CYAN= 96,
    BRIGHT_WHITE= 97
};
std::ostream& operator<<(std::ostream& os, Color color) {
    return os << "\033[" << static_cast<int>(color) << "m";
}