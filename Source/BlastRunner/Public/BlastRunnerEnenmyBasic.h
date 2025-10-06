// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BlastRunnerEnenmyBasic.generated.h"




UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	IDLE,
	Chase,
	Flee,
	Attack

};




UCLASS()
class BLASTRUNNER_API ABlastRunnerEnenmyBasic : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABlastRunnerEnenmyBasic();


	UPROPERTY(EditAnywhere, Category = "Visual")
	UStaticMeshComponent* PlayerMesh;



	float Health = 10;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EEnemyState EnemyState;



protected:
	
	virtual void BeginPlay() override;

	FTimerHandle CheckDistanceTimerHandle;


	// Functions
	UFUNCTION()
	void OnSeenPawn(APawn* Pawn);

	void StartChasing();

	void CheckDistanceToPlayer();

	void AttackThePlayer();

public:	

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UPawnSensingComponent* PawnSensingComponent;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraShake")
	TSubclassOf<UCameraShakeBase> HitCameraShake;


	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<AActor*> ChosetheActor;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	USoundBase* BlastSound;

	APawn* TargetPawn;

	UPROPERTY(EditAnywhere, Category = "Effects")
	class UNiagaraSystem* ExplosionEffect;

};
