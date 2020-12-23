#pragma once

///////////////////////////////////////////////////////////

namespace rts::cmd {

///////////////////////////////////////////////////////////

constexpr auto MATCH_MAX_TIME_HOURS = 4;
constexpr auto STEP_TIME_MS = 200; 
constexpr auto STEP_TIME_SEC = STEP_TIME_MS / 1000.f; 
constexpr auto CMDS_PER_STEP_MAX = 5;

constexpr auto MATCH_MAX_TIME_SEC = MATCH_MAX_TIME_HOURS * 60 * 60;
constexpr auto STEPS_PER_SEC = 1000 / STEP_TIME_MS;
constexpr auto STEPS_MAX = MATCH_MAX_TIME_SEC * STEPS_PER_SEC;

///////////////////////////////////////////////////////////

}//ns