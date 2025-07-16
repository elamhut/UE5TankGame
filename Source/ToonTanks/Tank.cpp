// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
}

void ATank::DoMove(const FVector2D* Value)
{
	const FVector DeltaLocation = FVector(Value->X, Value->Y, 0.f);
	const float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);

	AddActorLocalOffset(DeltaLocation * MoveSpeed * DeltaTime, true);
}

void ATank::DoTurn(const FVector2D* Value)
{
	const FRotator DeltaTurn = FRotator(0, Value->X, 0);
	const float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);

	AddActorLocalRotation(DeltaTurn * TurnSpeed * DeltaTime, true);
}
