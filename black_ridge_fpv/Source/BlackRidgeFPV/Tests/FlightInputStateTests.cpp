#include "FlightInputState.h"
#include "Misc/AutomationTest.h"

#if WITH_DEV_AUTOMATION_TESTS
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FFlightInputResponseTest, "BlackRidgeFPV.Input.FrameRateIndependentResponse",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FFlightInputResponseTest::RunTest(const FString& Parameters)
{
    FFlightInputState Target;
    Target.Throttle = 1.0f;
    Target.Pitch = -1.0f;
    Target.Roll = 1.0f;
    Target.Yaw = -1.0f;
    FFlightInputState At30;
    FFlightInputState At120;
    for (int32 Frame = 0; Frame < 30; ++Frame) { At30.Approach(Target, 1.0f / 30.0f, 8.0f); }
    for (int32 Frame = 0; Frame < 120; ++Frame) { At120.Approach(Target, 1.0f / 120.0f, 8.0f); }
    TestTrue(TEXT("Response after one second is independent of frame rate"), FMath::IsNearlyEqual(At30.Pitch, At120.Pitch, 0.00001f));
    TestTrue(TEXT("Press reaches at least 99 percent without overshoot"), At30.Throttle > 0.99f && At30.Throttle <= 1.0f);
    const FFlightInputState Neutral;
    for (int32 Frame = 0; Frame < 60; ++Frame) { At30.Approach(Neutral, 1.0f / 60.0f, 8.0f); }
    TestTrue(TEXT("All axes return to neutral after release"), FMath::Abs(At30.Throttle) < 0.001f && FMath::Abs(At30.Pitch) < 0.001f && FMath::Abs(At30.Roll) < 0.001f && FMath::Abs(At30.Yaw) < 0.001f);
    FFlightInputState OutOfRange;
    OutOfRange.Roll = 100.0f;
    At30.Approach(OutOfRange, 100.0f, 8.0f);
    TestEqual(TEXT("Invalid command magnitude cannot exceed normalized range"), At30.Roll, 1.0f);
    return true;
}
#endif
