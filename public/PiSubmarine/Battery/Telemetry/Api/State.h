#pragma once

#include "PiSubmarine/Volts.h"
#include "PiSubmarine/Amperes.h"
#include "PiSubmarine/AmpereHours.h"
#include "PiSubmarine/NormalizedFraction.h"
#include "PiSubmarine/Celsius.h"
#include <chrono>
#include <limits>
#include <cmath>
#include <optional>

namespace PiSubmarine::Battery::Telemetry::Api
{
    struct State
    {
    private:
        [[nodiscard]] static constexpr double Abs(const double value)
        {
            return value < 0.0 ? -value : value;
        }

        [[nodiscard]] static constexpr double Max3(const double a, const double b, const double c)
        {
            const auto ab = a > b ? a : b;
            return ab > c ? ab : c;
        }

        [[nodiscard]] static constexpr bool AreEqualDouble(const double left, const double right)
        {
            const auto diff = Abs(left - right);
            const auto scale = Max3(1.0, Abs(left), Abs(right));
            constexpr double epsilonScale = 8.0;
            return diff <= std::numeric_limits<double>::epsilon() * epsilonScale * scale;
        }

    public:
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

        [[nodiscard]] constexpr bool operator==(const State& other) const
        {
            return AreEqualDouble(PackVoltage.Value, other.PackVoltage.Value)
                && AreEqualDouble(ChargerVoltage.Value, other.ChargerVoltage.Value)
                && AreEqualDouble(PackCurrent.Value, other.PackCurrent.Value)
                && AreEqualDouble(ChargerCurrent.Value, other.ChargerCurrent.Value)
                && AreEqualDouble(ChargerTemperature.Value, other.ChargerTemperature.Value)
                && AreEqualDouble(PackTemperature.Value, other.PackTemperature.Value)
                && AreEqualDouble(MonitorTemperature.Value, other.MonitorTemperature.Value)
                && RemainingCapacity == other.RemainingCapacity
                && StateOfCharge == other.StateOfCharge
                && TimeToFull == other.TimeToFull
                && TimeToEmpty == other.TimeToEmpty;
        }
    };
}
