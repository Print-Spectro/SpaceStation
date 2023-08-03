// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "MyCharacterCPP.generated.h"


UCLASS()
class SPACESTATION_API AMyCharacterCPP : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacterCPP();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;




public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

#pragma region /** Input */
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnhancedInput")
	class UInputMappingContext* InputMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UMyInputConfigData* InputActions;

	UFUNCTION(BlueprintCallable)
	AActor* GetClosestInteractable();

	//Handle move input
	void Move(const FInputActionValue& Value);

	//Handle Look input 
	void Look(const FInputActionValue& Value);

	//Handle interact input
	void Interact(const FInputActionValue& Value);

	//Handle Jump input 
	//void Jump(const FInputActionValue& Value);
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Meshes", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* CollisionSphere;
};

