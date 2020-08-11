#include "systemF/util.h"

#include <string>

namespace systemF {

auto freshName() -> std::string {
    static int counter = 0;

    return std::string("v_" + std::to_string(counter++));
}

} // namespace systemF