#pragma once

namespace config 
{
    constexpr const int kfps_max = 240; 
    constexpr const double ktime_step_millis = 1000.0/static_cast<double>(kfps_max);
    constexpr const double kball_radius = 15.0;
    constexpr const int kballs_count = 10;
    constexpr const double karrowlength_scaling_factor = 60.0;
}