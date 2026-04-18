#pragma once

#include "PiSubmarine/Volts.h"
#include "PiSubmarine/Amperes.h"
#include "PiSubmarine/AmpereHours.h"
#include "PiSubmarine/NormalizedFraction.h"
#include "PiSubmarine/Celsius.h"
#include <chrono>

namespace PiSubmarine::Battery::Telemetry::Api
{
    struct State
    {
        Volts PackVoltage{};
        Volts ChargerVoltage{};
    	Amperes PackCurrent{};
    	Amperes ChargerCurrent{};
    	Celsius ChargerTemperature{};
    	Celsius PackTemperature{};
    	Celsius MonitorTemperature{};
        AmpereHours RemainingCapacity{};
    	NormalizedFraction StateOfCharge{0};
        std::optional<std::chrono::milliseconds> TimeToFull{};
        std::optional<std::chrono::milliseconds> TimeToEmpty{};

        [[nodiscard]] constexpr bool operator==(const State&) const = default;
    };
}
