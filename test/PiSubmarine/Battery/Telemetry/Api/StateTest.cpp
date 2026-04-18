#include <gtest/gtest.h>
#include <cmath>
#include <limits>
#include "PiSubmarine/Battery/Telemetry/Api/State.h"

namespace PiSubmarine::Battery::Telemetry::Api
{
    namespace
    {
        [[nodiscard]] double OffsetByUlps(double value, const std::size_t ulps)
        {
            for (std::size_t i = 0; i < ulps; ++i)
            {
                value = std::nextafter(value, std::numeric_limits<double>::infinity());
            }

            return value;
        }

        [[nodiscard]] State CreateBaselineState()
        {
            return State{
                .PackVoltage = Volts{12.0},
                .ChargerVoltage = Volts{14.2},
                .PackCurrent = Amperes{-1.5},
                .ChargerCurrent = Amperes{2.0},
                .ChargerTemperature = Celsius{36.5},
                .PackTemperature = Celsius{33.0},
                .MonitorTemperature = Celsius{35.25},
                .RemainingCapacity = AmpereHours{7.8},
                .StateOfCharge = NormalizedFraction{0.64},
                .TimeToFull = std::chrono::milliseconds{120000},
                .TimeToEmpty = std::chrono::milliseconds{240000}
            };
        }
    }

    TEST(StateTest, OperatorEqReturnsTrueForIdenticalStates)
    {
        const auto left = CreateBaselineState();
        const auto right = CreateBaselineState();

        EXPECT_TRUE(left == right);
    }

    TEST(StateTest, OperatorEqReturnsTrueForSmallUnitValueDifferences)
    {
        const auto left = CreateBaselineState();
        auto right = CreateBaselineState();

        right.PackVoltage.Value = OffsetByUlps(right.PackVoltage.Value, 4);
        right.ChargerVoltage.Value = OffsetByUlps(right.ChargerVoltage.Value, 4);
        right.PackCurrent.Value = OffsetByUlps(right.PackCurrent.Value, 4);
        right.ChargerCurrent.Value = OffsetByUlps(right.ChargerCurrent.Value, 4);
        right.ChargerTemperature.Value = OffsetByUlps(right.ChargerTemperature.Value, 4);
        right.PackTemperature.Value = OffsetByUlps(right.PackTemperature.Value, 4);
        right.MonitorTemperature.Value = OffsetByUlps(right.MonitorTemperature.Value, 4);

        EXPECT_TRUE(left == right);
    }

    TEST(StateTest, OperatorEqReturnsFalseForLargeUnitValueDifferences)
    {
        const auto left = CreateBaselineState();
        auto right = CreateBaselineState();

        right.PackVoltage.Value = OffsetByUlps(right.PackVoltage.Value, 32);

        EXPECT_FALSE(left == right);
    }

    TEST(StateTest, OperatorEqReturnsFalseWhenNonFloatingFieldsDiffer)
    {
        const auto left = CreateBaselineState();
        auto right = CreateBaselineState();

        right.TimeToEmpty = std::chrono::milliseconds{240001};

        EXPECT_FALSE(left == right);
    }
}
