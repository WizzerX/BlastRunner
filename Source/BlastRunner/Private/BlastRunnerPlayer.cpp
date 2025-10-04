// Fill out your copyright notice in the Description page of Project Settings.


#include "BlastRunnerPlayer.h"
#include "stdio.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BlastRunner/Public/BlastRunnerWidget.h"
#include "Components/CapsuleComponent.h"
#include "BlastRunner/Public/BlastRunnerController.h"
#include "Kismet/KismetSystemLibrary.h"
// Sets default values
ABlastRunnerPlayer::ABlastRunnerPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	



	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	CapsuleComponent->InitCapsuleSize(93.684525, 58.94849);
	SetRootComponent(CapsuleComponent);

	CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CapsuleComponent->SetCollisionObjectType(ECC_Pawn);
	CapsuleComponent->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block); // if TraceTypeQuery1 maps to Visibility



	PlayerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));
	PlayerMesh->SetupAttachment(RootComponent);
	PlayerMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);


	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(PlayerMesh);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);


	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));


	
	
	

	

	
	



	TimeProgress = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	TimeProgress->SetupAttachment(PlayerMesh);

	BlastRunnerWidget = Cast<UBlastRunnerWidget>(TimeProgress->GetUserWidgetObject());
	
	RunnerState = ERunnerState::Green;


	
	
}

// Called when the game starts or when spawned
void ABlastRunnerPlayer::BeginPlay()
{
	Super::BeginPlay();
	BlastRunnerWidget = Cast<UBlastRunnerWidget>(TimeProgress->GetUserWidgetObject());

	GetWorld()->GetTimerManager().SetTimer(BlastTimer, this, &ABlastRunnerPlayer::TimeExploader, 1, true, 1.f);
	
	BlastRunnerWidget->MakeChargeToGreen();
	CharacterController = Cast<ABlastRunnerController>(GetController());
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
	PlayerInputComponent->BindAction("Blast",EInputEvent::IE_Pressed, this, &ABlastRunnerPlayer::Blast);
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

void ABlastRunnerPlayer::Blast()
{

	FHitResult HitResult;
	//if (BlastRunnerWidget&& ColorTimer>=3.7f)
	
		UKismetSystemLibrary::SphereTraceSingle(GetWorld(),GetTargetLocation(this), GetTargetLocation(this) * 500.f, 500.f,
			ETraceTypeQuery::TraceTypeQuery1, false, ChosetheActor, EDrawDebugTrace::ForDuration, HitResult, true);
		



		UGameplayStatics::PlaySound2D(GetWorld(), ExploadeSound);
		ERunnerState::Green;
		ColorTimer = 0.0;
		SwitchTORed = 0;

	

	
}

void ABlastRunnerPlayer::TimeExploader()
{
	if (SwitchTORed == 2)
	{
		BlastRunnerWidget->MakeChargeToRed();
		//DO THE STUFF
		SwitchTORed = 0;
		UGameplayStatics::PlaySound2D(GetWorld(), ExploadeSound);
		ColorTimer = 0.0;
		ERunnerState::Green;
		
		
		
			Life = FMath::Clamp(Life-=1.f, 0.0f, 4.f);
			float Percentage = Life / 4;
			GEngine->AddOnScreenDebugMessage(1, 3, FColor::Red, FString("Fired the function!"));
			if(CharacterController)
			CharacterController->UpdateHealth(Percentage);
		


		return;
	}


	if (ColorTimer >= 3.7f)
	{
		BlastRunnerWidget->MakeChargeToYellow();
		SwitchTORed = 2;
		ERunnerState::Yellow;
		return;
	}


	ColorTimer = FMath::Clamp(ColorTimer += .3f, 0.0f, 5.f);
	BlastRunnerWidget->MakeChargeToGreen();
	float percentage = ColorTimer / 5.f;
	ERunnerState::Green;

	BlastRunnerWidget->UpdateUI(percentage);
	GEngine->AddOnScreenDebugMessage(1, 3, FColor::Purple, FString("PROGRESS UPDATED!"));

}


void ABlastRunnerPlayer::TakeDamage(float Value)
{

	Life = FMath::Clamp(Life -= Value, 0.0f, 4.f);
	float Percentage = Life / 4;
	GEngine->AddOnScreenDebugMessage(1, 3, FColor::Red, FString("Fired the function!"));
	if (CharacterController)
		CharacterController->UpdateHealth(Percentage);


}

