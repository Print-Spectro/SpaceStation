// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BaseMeshComp = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMeshComp;
	//binding function to a timer so that the door can automoatically close
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
				//starting timer for the door to automatically close if left open
				if (!GetWorld()->GetTimerManager().IsTimerActive(TimerHandle)) {
					GetWorld()->GetTimerManager().SetTimer(TimerHandle, CloseTimer, CloseDelay, false);
				}
			}

		}
	}
}

void ADoor::SetShouldMove(bool SetMove) 
{
	ShouldMove = SetMove;
}


void ADoor::ToggleMove()
/*
Swaps the direction of the door, also causes the door to move if stationary
*/
{	
	
	MoveDirection = !MoveDirection;
	SetShouldMove(true);
	ADoor::SetMoveDirection(MoveDirection);
}

void ADoor::SetMoveDirection(bool Direction)
{	
	//Use to define the target location for the door to move to
	if (Direction) {
		TargetLocation = EndLocation;
	}
	else {
		TargetLocation = StartLocation;
	}
}



