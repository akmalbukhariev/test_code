#include "InsertMirror.h"
 
InsertMirror::InsertMirror(std::int32_t r, std::int32_t c, std::int32_t m, std::int32_t n)
    :_r(r), _c(c), _m(m), _n(n), _mirrorSlash{}, _mirrorBackslash{}{ }

InsertMirror::~InsertMirror() 
{

}

void InsertMirror::run(const MirrorGrid& mirrorSlash, const MirrorGrid& mirrorBackslash) noexcept
{
    _mirrorSlash = mirrorSlash;
    _mirrorBackslash = mirrorBackslash;

    // Check if no mirrors are provided
    if (_m == 0 && _n == 0) {
        std::cout << "-1\n";
        return;
    }

    // First check if the safe opens without placing a mirror
    if (simulateLaser()) {
        std::cout << "0\n";
        return;
    }

    std::array<GridPosition, max_r* max_c> validPositions = {};
    std::size_t validCount = 0;

    for (std::int32_t i = 1; i <= _r; ++i) {
        for (std::int32_t j = 1; j <= _c; ++j) {
            // Skip if there's a mirror at this position
            if (_mirrorSlash[i][j] || _mirrorBackslash[i][j]) {
                continue;
            }

            // Simulate placing a / mirror
            _mirrorSlash[i][j] = true;
            if (simulateLaser()) {
                validPositions[validCount] = { i, j };
                ++validCount;
            }
            _mirrorSlash[i][j] = false;

            // Simulate placing a \ mirror
            _mirrorBackslash[i][j] = true;
            if (simulateLaser()) {
                validPositions[validCount] = { i, j };
                ++validCount;
            }
            _mirrorBackslash[i][j] = false;
        }
    }

    if (validCount == 0) {
        std::cout << "-1\n";
    }
    else {
        std::sort(validPositions.begin(), validPositions.begin() + validCount);
        std::cout << validCount << ' ' << validPositions[0].first << ' ' << validPositions[0].second << '\n';
    }
}
 
bool InsertMirror::simulateLaser() noexcept {
    std::int32_t x = 1;
    std::int32_t y = 1;
    std::int32_t dir = Right;

    while (isInsideGrid(x, y)) {
        if (_mirrorSlash[x][y]) { // /
           
            if (dir == Right) dir = Up;
            else if (dir == Down) dir = Left;
            else if (dir == Left) dir = Down;
            else if (dir == Up) dir = Right;
        }
        else if (_mirrorBackslash[x][y]) { // \

            if (dir == Right) dir = Down;
            else if (dir == Down) dir = Right;
            else if (dir == Left) dir = Up;
            else if (dir == Up) dir = Left;
        }

        // Move in the current direction
        x += dx[dir];
        y += dy[dir];

        // Check if the laser reaches the bottom-right corner
        if (x == _r && y == _c && dir == Right) {
            return true;
        }
    }

    return false;
}

inline bool InsertMirror::isInsideGrid(std::int32_t x, std::int32_t y) noexcept {
    return x >= 1 && x <= _r && y >= 1 && y <= _c;
}