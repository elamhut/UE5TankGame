// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Tank.h"

ATankPlayerController::ATankPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	InputMappingContext = CreateDefaultSubobject<UInputMappingContext>("Input Mapping Context");
	return;
}

void ATankPlayerController::SetPlayerEnabledState(const bool bIsPlayerEnabled)
{
	if (bIsPlayerEnabled)
	{
		EnableInput(this);
	}
	else
	{
		DisableInput(this);
	}
	bShowMouseCursor = bIsPlayerEnabled;
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (const ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player))
		if (const auto Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			if (!InputMappingContext.IsNull())
				Subsystem->AddMappingContext(InputMappingContext.LoadSynchronous(), 0);

	if (AActor* CurrentPawn = GetPawn())
	{
		TankPlayer = Cast<ATank>(CurrentPawn);
		checkf(TankPlayer, TEXT("Unable to get TankPlayer as ATank"));
	}

	EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	checkf(EnhancedInputComponent, TEXT("Unable to get Enhanced Input correctly"));

	EnhancedInputComponent->BindAction(MoveAction,
	                                   ETriggerEvent::Triggered,
	                                   this,
	                                   &ATankPlayerController::HandleMove);

	EnhancedInputComponent->BindAction(TurnAction,
	                                   ETriggerEvent::Triggered,
	                                   this,
	                                   &ATankPlayerController::HandleTurn);

	EnhancedInputComponent->BindAction(RotateAction,
	                                   ETriggerEvent::Triggered,
	                                   this,
	                                   &ATankPlayerController::HandleRotate);

	EnhancedInputComponent->BindAction(FireAction,
	                                   ETriggerEvent::Started,
	                                   this,
	                                   &ATankPlayerController::HandleFire);

	UE_LOG(LogTemp, Warning, TEXT("This Player Controller: %s"), *GetName());
}

void ATankPlayerController::PlayerTick(const float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
}

void ATankPlayerController::HandleMove(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();
	TankPlayer->DoMove(&MovementVector);
}

void ATankPlayerController::HandleTurn(const FInputActionValue& Value)
{
	const FVector2D TurnVector = Value.Get<FVector2D>();
	TankPlayer->DoTurn(&TurnVector);
}

void ATankPlayerController::HandleRotate(const FInputActionValue& Value)
{
	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_WorldStatic, false, HitResult);
	DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.f, 10, FColor::Cyan);

	TankPlayer->DoRotate(&HitResult.ImpactPoint);
}

void ATankPlayerController::HandleFire()
{
	TankPlayer->DoFire();
}
