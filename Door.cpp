// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BaseMeshComp = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMeshComp;
	CloseTimer.BindLambda([&]
	{
		if (ShouldClose) {
			ToggleMove();
		}
			
	});
	
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
	
	StartLocation = ADoor::GetActorLocation();
	EndLocation = ADoor::GetActorRotation().RotateVector(MoveOffset) + StartLocation;
	Speed = FVector::Distance(StartLocation, EndLocation) / MoveTime;
	TargetLocation = EndLocation;
	
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	if (ShouldMove) {
		FVector CurrentLocation = ADoor::GetActorLocation();
		ShouldClose = false;
		FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);
		ADoor::SetActorLocation(NewLocation);
		if (CurrentLocation == TargetLocation) {
			SetShouldMove(false);
			if (CurrentLocation == EndLocation)
			{
				ShouldClose = true;
				GetWorld()->GetTimerManager().SetTimer(TimerHandle, CloseTimer, CloseDelay, false);
			}

		}
	}
}

void ADoor::SetShouldMove(bool SetMove) 
{
	ShouldMove = SetMove;
}


void ADoor::ToggleMove()
{
	MoveDirection = !MoveDirection;
	SetShouldMove(true);
	ADoor::SetMoveDirection(MoveDirection);
}

void ADoor::SetMoveDirection(bool Direction)
{
	if (Direction) {
		TargetLocation = EndLocation;
	}
	else {
		TargetLocation = StartLocation;
	}
}

