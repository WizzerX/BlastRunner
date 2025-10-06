// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BlastRunnerPlayer.generated.h"

UENUM(BlueprintType)
enum class ERunnerState:uint8
{
	Green  UMETA(DisplayName = "GREEN"),
	Yellow  UMETA(DisplayName = "YELLOW"),
	Red  UMETA(DisplayName = "RED")

};





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


UPROPERTY(EditAnywhere, Category = "Visual")
UStaticMeshComponent* PlayerMesh;

UPROPERTY(EditAnywhere,BlueprintReadWrite)
class USpringArmComponent* SpringArm;

UPROPERTY(EditAnywhere, BlueprintReadWrite)
class UWidgetComponent* TimeProgress;

UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
class UCapsuleComponent* CapsuleComponent;

class UBlastRunnerWidget* BlastRunnerWidget;


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
	void Blast();

	float ColorTimer = 0.0;
	int BlastTime = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	ERunnerState RunnerState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* ExploadeSound;


	int SwitchTORed = 0;

	void PlayerDeath();


public:

	void TimeExploader();

	FTimerHandle BlastTimer;

	float Life = 4.0;

	void TakeDamage(float Value);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* CountDownSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraShake")
	TSubclassOf<UCameraShakeBase> HitCameraShake;

	void CameraHitShake();

private:
class 	ABlastRunnerController* CharacterController;

int score = 0;

TArray<AActor*>ChosetheActor;

UPROPERTY(EditAnywhere, Category = "Effects")
class UNiagaraSystem* ExplosionEffect;

UPROPERTY(EditAnywhere, Category = "Effects")
class UNiagaraSystem* EnenmyEffect;



private:

	ABlastRunnerController* PlayerController;





};
