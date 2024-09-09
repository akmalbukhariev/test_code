#include "InsertMirror.h"

int main() {

    std::int32_t r = 0; //Row count of the grid
    std::int32_t c = 0; //Column count of the grid
    std::int32_t m = 0; // / mirrors
    std::int32_t n = 0; // \ mirrors 

    std::cin >> r >> c >> m >> n;

    MirrorGrid mirrorSlash = {};      // Grid for / mirrors
    MirrorGrid mirrorBackslash = {};  // Grid for \ mirrors

    // Input for / mirrors
    for (std::int32_t i = 0; i < m; ++i) {
        std::int32_t ri, ci;
        std::cin >> ri >> ci;
        mirrorSlash[ri][ci] = true;
    }

    // Input for \ mirrors
    for (std::int32_t i = 0; i < n; ++i) {
        std::int32_t ri, ci;
        std::cin >> ri >> ci;
        mirrorBackslash[ri][ci] = true;
    }

    InsertMirror insert(r, c, m, n);
    insert.run(mirrorSlash, mirrorBackslash);

    return 0;
}