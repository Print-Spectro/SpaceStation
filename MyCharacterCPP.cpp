// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacterCPP.h"
#include <EnhancedInputComponent.h>
#include <EnhancedInputSubsystems.h>
#include "EnhancedInput/Public/EnhancedInputComponent.h"
#include "MyInputConfigData.h"

// Sets default values
AMyCharacterCPP::AMyCharacterCPP()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyCharacterCPP::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyCharacterCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacterCPP::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//Get player controller
	APlayerController* PC = Cast<APlayerController>(GetController());

	// Get the local player subsystem
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());

	//Clear out existing mapping, and add our mapping
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMapping, 0);

	//Getting the EnhancedInputComponent
	UEnhancedInputComponent* PEI = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	//Binding the actions
	PEI->BindAction(InputActions->InputMove, ETriggerEvent::Triggered, this, &AMyCharacterCPP::Move);
	PEI->BindAction(InputActions->InputLook, ETriggerEvent::Triggered, this, &AMyCharacterCPP::Look);
	PEI->BindAction(InputActions->InputInteract, ETriggerEvent::Triggered, this, &AMyCharacterCPP::Interact);
	PEI->BindAction(InputActions->InputJump, ETriggerEvent::Triggered, this, &AMyCharacterCPP::Jump);
}	

void AMyCharacterCPP::Move(const FInputActionValue& Value) 
{	
	UE_LOG(LogTemp, Display, TEXT("MoveTriggered"));
	if (Controller != nullptr)
	{
		const FVector2D MoveValue = Value.Get<FVector2D>();
		const FRotator MovementRotation(0, Controller->GetControlRotation().Yaw, 0);
		//Forward/Backward direction
		if (MoveValue.Y != 0.f)
		{
			//Get forward vector
			const FVector Direction = MovementRotation.RotateVector(FVector::ForwardVector);

			AddMovementInput(Direction, MoveValue.Y);
		}

		//Right.Feft direction
		if (MoveValue.X != 0.f)
		{
			//Get right vector
			const FVector Direction = MovementRotation.RotateVector(FVector::RightVector);

			AddMovementInput(Direction, MoveValue.X);
		}
	}
}

void AMyCharacterCPP::Look(const FInputActionValue& Value) 
{
	FVector2D LookValue = Value.Get<FVector2D>();
	
	if (Controller != nullptr)
	{
		AddControllerYawInput(LookValue.X);
		AddControllerPitchInput(LookValue.Y);
	}
}

void AMyCharacterCPP::Interact(const FInputActionValue& Value) {
	
}

void AMyCharacterCPP::Jump(const FInputActionValue& Value) {
	AddMovementInput(FVector(0.0f, 0.0f, 100.0f), 100);
	UE_LOG(LogTemp, Display, TEXT("JumpActivated"));
}