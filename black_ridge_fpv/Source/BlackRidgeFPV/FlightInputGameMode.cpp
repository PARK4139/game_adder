#include "FlightInputGameMode.h"
#include "FlightInputPawn.h"

AFlightInputGameMode::AFlightInputGameMode()
{
    DefaultPawnClass = AFlightInputPawn::StaticClass();
}
