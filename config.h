#pragma once

namespace config 
{
    constexpr const int kfps_max = 240; 
    constexpr const double ktime_step_millis = 1000.0/static_cast<double>(kfps_max);
    constexpr const double kball_radius = 12.0;
}