// Fill out your copyright notice in the Description page of Project Settings.


#include "BlastRunnerPlayer.h"
#include "stdio.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BlastRunner/Public/BlastRunnerWidget.h"

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


	TimeProgress = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	TimeProgress->SetupAttachment(PlayerMesh);





}

// Called when the game starts or when spawned
void ABlastRunnerPlayer::BeginPlay()
{
	Super::BeginPlay();


	GetWorld()->GetTimerManager().SetTimer(BlastTimer, this, &ABlastRunnerPlayer::TimeExploader, 1, true, 1.f);
	
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
	

	}



}

void ABlastRunnerPlayer::MoveRight(float Axis)
{
	if (Controller != nullptr && Axis != 0.0f)
	{
		
		const FRotator PlayerRotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.0f, PlayerRotation.Yaw, 0.0f);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Axis);


	}


}

void ABlastRunnerPlayer::TimeExploader()
{
	BlastRunnerWidget = Cast<UBlastRunnerWidget>(TimeProgress->GetUserWidgetObject());
	
	if (TimeLeft >= 3.7f)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), ExploadeSound);
		TimeLeft = 0.0f;





	}


		TimeLeft = FMath::Clamp(TimeLeft+=.3f, 0.0f, 5.f);
		float percentage = TimeLeft / 5.f;
		if (BlastRunnerWidget)
		{
			BlastRunnerWidget->UpdateUI(percentage);
			GEngine->AddOnScreenDebugMessage(1, 3, FColor::Purple, FString("PROGRESS UPDATED!"));

			





		}
		else
		{
			GEngine->AddOnScreenDebugMessage(1, 3, FColor::Purple, FString("Cast Failed!"));
		
		}




	



}

