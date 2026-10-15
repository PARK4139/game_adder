#pragma once

#include "CoreMinimal.h"

// Device-independent command state. No movement or flight physics lives here.
struct FFlightInputState
{
    float Throttle = 0.0f;
    float Pitch = 0.0f;
    float Roll = 0.0f;
    float Yaw = 0.0f;

    void Approach(const FFlightInputState& Target, float DeltaSeconds, float ResponseRate)
    {
        if (!FMath::IsFinite(DeltaSeconds) || DeltaSeconds <= 0.0f)
        {
            return;
        }
        const float Alpha = 1.0f - FMath::Exp(-FMath::Max(0.0f, ResponseRate) * DeltaSeconds);
        Throttle = FMath::Lerp(Throttle, FMath::Clamp(Target.Throttle, -1.0f, 1.0f), Alpha);
        Pitch = FMath::Lerp(Pitch, FMath::Clamp(Target.Pitch, -1.0f, 1.0f), Alpha);
        Roll = FMath::Lerp(Roll, FMath::Clamp(Target.Roll, -1.0f, 1.0f), Alpha);
        Yaw = FMath::Lerp(Yaw, FMath::Clamp(Target.Yaw, -1.0f, 1.0f), Alpha);
    }
};
