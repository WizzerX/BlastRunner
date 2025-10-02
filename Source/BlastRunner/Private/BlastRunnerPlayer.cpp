// Fill out your copyright notice in the Description page of Project Settings.


#include "BlastRunnerPlayer.h"
#include "stdio.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
// Sets default values
ABlastRunnerPlayer::ABlastRunnerPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
	MovementComponent->UpdatedComponent = RootComponent;



	PlayerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));
	PlayerMesh->SetupAttachment(RootComponent);
	
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(PlayerMesh);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);








}

// Called when the game starts or when spawned
void ABlastRunnerPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABlastRunnerPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABlastRunnerPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABlastRunnerPlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABlastRunnerPlayer::MoveRight);

}

void ABlastRunnerPlayer::MoveForward(float Axis)
{
	if (Controller != nullptr && Axis != 0.0f)
	{
		
		const FRotator PlayerRotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.0f, PlayerRotation.Yaw, 0.0f);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Axis);
		UE_LOG(LogTemp, Warning, TEXT("MoveForward"));

	}



}

void ABlastRunnerPlayer::MoveRight(float Axis)
{
	if (Controller != nullptr && Axis != 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("MoveRight"));
		const FRotator PlayerRotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.0f, PlayerRotation.Yaw, 0.0f);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Axis);


	}


}

