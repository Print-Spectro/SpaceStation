// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "TimerManager.h"
#include "Engine/EngineTypes.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"


UCLASS()
class SPACESTATION_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

	UFUNCTION(BlueprintCallable)
	void ToggleMove();


	


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void SetShouldMove(bool SetMove);

	UFUNCTION()
	void SetMoveDirection(bool Direction);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Meshes", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMeshComp;

	UPROPERTY(EditAnywhere, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	FVector MoveOffset = FVector(0.0f, 160.0f, 0.0f);

	UPROPERTY(EditAnywhere, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float MoveTime = 1;

	float Speed;

	FVector StartLocation;

	FVector EndLocation;

	FVector TargetLocation;

	bool ShouldMove;

	bool ShouldClose = false;

	bool MoveDirection = false;

	FTimerDelegate CloseTimer;

	FTimerHandle TimerHandle;

	UPROPERTY(EditAnywhere, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float CloseDelay = 3;

	//test comment
};
