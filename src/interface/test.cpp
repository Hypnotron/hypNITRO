#define DISABLE_LOGGING
#include "../arm.hpp"

int main(int argc, char* argv[]) {
    debug::write(
            debug::message,
            "%s"
            "hello, world!");
    debug::info();
    return 0;
}
