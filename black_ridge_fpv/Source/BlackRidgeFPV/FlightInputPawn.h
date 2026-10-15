#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "FlightInputState.h"
#include "FlightInputPawn.generated.h"

class UCameraComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

UCLASS()
class BLACKRIDGEFPV_API AFlightInputPawn : public APawn
{
    GENERATED_BODY()

public:
    AFlightInputPawn();
    virtual void Tick(float DeltaSeconds) override;
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
    virtual void PawnClientRestart() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
    const FFlightInputState& GetFlightInput() const { return SmoothedInput; }

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere)
    TObjectPtr<UCameraComponent> Camera;

    UPROPERTY(Transient)
    TObjectPtr<UInputMappingContext> FlightMapping;

    UPROPERTY(Transient)
    TArray<TObjectPtr<UInputAction>> FlightActions;

    UPROPERTY(EditDefaultsOnly, Category="Flight Input", meta=(ClampMin="0.1", ClampMax="30.0"))
    float InputResponseRate = 8.0f;

private:
    void CreateFlightMapping();
    void OnThrottle(const FInputActionValue& Value);
    void OnPitch(const FInputActionValue& Value);
    void OnRoll(const FInputActionValue& Value);
    void OnYaw(const FInputActionValue& Value);
    void SetAxis(float& Axis, float Value, const TCHAR* Name);
    FFlightInputState TargetInput;
    FFlightInputState SmoothedInput;
    bool bTraceInput = false;
    float TraceElapsed = 0.0f;
};
