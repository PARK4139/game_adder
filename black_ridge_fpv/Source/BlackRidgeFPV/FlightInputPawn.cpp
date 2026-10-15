#include "FlightInputPawn.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/Engine.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/PlayerController.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "InputModifiers.h"
#include "InputCoreTypes.h"
#include "Misc/CommandLine.h"
#include "Misc/Parse.h"

DEFINE_LOG_CATEGORY_STATIC(LogFlightInput, Log, All);

AFlightInputPawn::AFlightInputPawn()
{
    PrimaryActorTick.bCanEverTick = true;
    SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("InputRoot")));
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("InputCamera"));
    Camera->SetupAttachment(RootComponent);
    Camera->SetRelativeLocation(FVector(-200.0f, 0.0f, 150.0f));
    Camera->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));
}

void AFlightInputPawn::CreateFlightMapping()
{
    if (FlightMapping)
    {
        return;
    }
    FlightMapping = NewObject<UInputMappingContext>(this);
    const FKey PositiveKeys[] = { EKeys::Up, EKeys::W, EKeys::D, EKeys::Right };
    const FKey NegativeKeys[] = { EKeys::Down, EKeys::S, EKeys::A, EKeys::Left };
    const FName Names[] = { TEXT("Throttle"), TEXT("Pitch"), TEXT("Roll"), TEXT("Yaw") };
    for (int32 Index = 0; Index < 4; ++Index)
    {
        UInputAction* Action = NewObject<UInputAction>(this, Names[Index]);
        Action->ValueType = EInputActionValueType::Axis1D;
        Action->AccumulationBehavior = EInputActionAccumulationBehavior::Cumulative;
        FlightActions.Add(Action);
        FlightMapping->MapKey(Action, PositiveKeys[Index]);
        FEnhancedActionKeyMapping& NegativeMapping = FlightMapping->MapKey(Action, NegativeKeys[Index]);
        NegativeMapping.Modifiers.Add(NewObject<UInputModifierNegate>(FlightMapping));
    }
}

void AFlightInputPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    CreateFlightMapping();
    UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
    for (ETriggerEvent Event : { ETriggerEvent::Triggered, ETriggerEvent::Completed, ETriggerEvent::Canceled })
    {
        Input->BindAction(FlightActions[0], Event, this, &AFlightInputPawn::OnThrottle);
        Input->BindAction(FlightActions[1], Event, this, &AFlightInputPawn::OnPitch);
        Input->BindAction(FlightActions[2], Event, this, &AFlightInputPawn::OnRoll);
        Input->BindAction(FlightActions[3], Event, this, &AFlightInputPawn::OnYaw);
    }
    if (APlayerController* Controller = Cast<APlayerController>(GetController()))
    {
        if (ULocalPlayer* Player = Controller->GetLocalPlayer())
        {
            if (auto* Subsystem = Player->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
            {
                Subsystem->AddMappingContext(FlightMapping, 0);
            }
        }
    }
    UE_LOG(LogFlightInput, Display, TEXT("a78b16c0 mapping_ready actions=4 keyboard_only=true response_rate=%.2f"), InputResponseRate);
}

void AFlightInputPawn::PawnClientRestart()
{
    TargetInput = FFlightInputState();
    SmoothedInput = FFlightInputState();
    Super::PawnClientRestart();
}

void AFlightInputPawn::BeginPlay()
{
    Super::BeginPlay();
    bTraceInput = FParse::Param(FCommandLine::Get(), TEXT("FPVInputTrace"));
    if (APlayerController* Controller = Cast<APlayerController>(GetController()))
    {
        Controller->SetInputMode(FInputModeGameOnly());
        Controller->bShowMouseCursor = false;
    }
    UE_LOG(LogFlightInput, Display, TEXT("a78b16c0 pawn_started trace=%s"), bTraceInput ? TEXT("true") : TEXT("false"));
}

void AFlightInputPawn::SetAxis(float& Axis, float Value, const TCHAR* Name)
{
    const float Next = FMath::IsFinite(Value) ? FMath::Clamp(Value, -1.0f, 1.0f) : 0.0f;
    if (bTraceInput && !FMath::IsNearlyEqual(Axis, Next))
    {
        UE_LOG(LogFlightInput, Display, TEXT("a78b16c0 axis_event time=%.6f axis=%s previous=%.3f target=%.3f"),
            GetWorld()->GetTimeSeconds(), Name, Axis, Next);
    }
    Axis = Next;
}

void AFlightInputPawn::OnThrottle(const FInputActionValue& Value) { SetAxis(TargetInput.Throttle, Value.Get<float>(), TEXT("throttle")); }
void AFlightInputPawn::OnPitch(const FInputActionValue& Value) { SetAxis(TargetInput.Pitch, Value.Get<float>(), TEXT("pitch")); }
void AFlightInputPawn::OnRoll(const FInputActionValue& Value) { SetAxis(TargetInput.Roll, Value.Get<float>(), TEXT("roll")); }
void AFlightInputPawn::OnYaw(const FInputActionValue& Value) { SetAxis(TargetInput.Yaw, Value.Get<float>(), TEXT("yaw")); }

void AFlightInputPawn::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    SmoothedInput.Approach(TargetInput, DeltaSeconds, InputResponseRate);
    if (bTraceInput)
    {
        TraceElapsed += DeltaSeconds;
        if (TraceElapsed >= 0.02f)
        {
            TraceElapsed = 0.0f;
            UE_LOG(LogFlightInput, Display,
                TEXT("a78b16c0 sample time=%.6f target=%.4f,%.4f,%.4f,%.4f smooth=%.4f,%.4f,%.4f,%.4f"),
                GetWorld()->GetTimeSeconds(), TargetInput.Throttle, TargetInput.Pitch, TargetInput.Roll, TargetInput.Yaw,
                SmoothedInput.Throttle, SmoothedInput.Pitch, SmoothedInput.Roll, SmoothedInput.Yaw);
        }
    }
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(7800, 0.0f, FColor::White,
            TEXT("Keyboard input check: W/S pitch | A/D roll | arrows yaw/throttle. Flight comes next."));
        GEngine->AddOnScreenDebugMessage(7801, 0.0f, FColor::Cyan,
            FString::Printf(TEXT("Throttle %+.2f   Pitch %+.2f   Roll %+.2f   Yaw %+.2f"),
                SmoothedInput.Throttle, SmoothedInput.Pitch, SmoothedInput.Roll, SmoothedInput.Yaw));
    }
}

void AFlightInputPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    if (APlayerController* Controller = Cast<APlayerController>(GetController()))
    {
        if (ULocalPlayer* Player = Controller->GetLocalPlayer())
        {
            if (auto* Subsystem = Player->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
            {
                if (FlightMapping) { Subsystem->RemoveMappingContext(FlightMapping); }
            }
        }
    }
    Super::EndPlay(EndPlayReason);
}
