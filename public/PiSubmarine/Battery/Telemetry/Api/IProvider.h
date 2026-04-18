#pragma once

#include "PiSubmarine/Battery/Telemetry/Api/State.h"
#include "PiSubmarine/Error/Api/Result.h"

namespace PiSubmarine::Battery::Telemetry::Api
{
    class IProvider
    {
    public:
        virtual ~IProvider() = default;

        [[nodiscard]] virtual Error::Api::Result<State> GetState() const = 0;
    };
}

