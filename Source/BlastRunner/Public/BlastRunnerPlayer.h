// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BlastRunnerPlayer.generated.h"

UCLASS()
class BLASTRUNNER_API ABlastRunnerPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABlastRunnerPlayer();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
class	UCameraComponent* Camera;

UPROPERTY(EditAnywhere, BlueprintReadWrite)
class UFloatingPawnMovement* MovementComponent;


UPROPERTY(EditAnywhere, BlueprintReadWrite)
UStaticMeshComponent* PlayerMesh;

UPROPERTY(EditAnywhere,BlueprintReadWrite)
class USpringArmComponent* SpringArm;




protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float Axis);
	void MoveRight(float Axis);



};
