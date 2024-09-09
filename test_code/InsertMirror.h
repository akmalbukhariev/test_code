#pragma once
#include <cstdint>
#include <array>
#include <algorithm>
#include <iostream>

constexpr std::int32_t max_r = 100;
constexpr std::int32_t max_c = 100;

using GridPosition = std::pair<std::int32_t, std::int32_t>;
using MirrorGrid = std::array<std::array<bool, max_c + 1>, max_r + 1>;

// Movement in x and y directions for each direction
constexpr std::array<std::int32_t, 4> dx = { 0, 1, 0, -1 };
constexpr std::array<std::int32_t, 4> dy = { 1, 0, -1, 0 };

enum Direction {
    Right = 0, Down = 1, Left = 2, Up = 3
};

class InsertMirror
{
public:
    /// <summary>
    /// Insert mirror constructure
    /// </summary>
    /// <param name="r">Row count</param>
    /// <param name="c">Column count</param>
    /// <param name="m">Input for / mirrors</param>
    /// <param name="n">Input for \ mirrors</param>
    InsertMirror(std::int32_t r, std::int32_t c, std::int32_t m, std::int32_t n);
    ~InsertMirror();

    //Start proccess
    void run(const MirrorGrid& mirrorSlash, const MirrorGrid& mirrorBackslash) noexcept;

private:
    //Check if x and y inside the grid
    bool isInsideGrid(std::int32_t x, std::int32_t y) noexcept;

    // Simulate the laser's path
    bool simulateLaser() noexcept;

private:
    std::int32_t _r;
    std::int32_t _c;
    std::int32_t _m;
    std::int32_t _n;

    MirrorGrid _mirrorSlash;
    MirrorGrid _mirrorBackslash;
};