// Fill out your copyright notice in the Description page of Project Settings.


#include "BlastRunnerEnemy.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
// Sets default values
ABlastRunnerEnemy::ABlastRunnerEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
	PlayerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));
	SetRootComponent(PlayerMesh);


	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	CapsuleComponent->InitCapsuleSize(93.684525, 58.94849);
	CapsuleComponent->SetupAttachment(RootComponent);





}

// Called when the game starts or when spawned
void ABlastRunnerEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABlastRunnerEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABlastRunnerEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

