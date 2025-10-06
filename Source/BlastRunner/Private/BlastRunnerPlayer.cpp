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
#include "BlastRunner/Public/BlastRunnerEnenmyBasic.h"
#include "DrawDebugHelpers.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "D:/UE_4.27/UE_4.27/UE_4.27/Engine/Plugins/FX/Niagara/Source/Niagara/Public/NiagaraFunctionLibrary.h"




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
	if (ColorTimer >= 3.5)
	{
		FVector Origin = GetActorLocation();
		float Radius = 650.f;

		TArray<FOverlapResult> Overlaps;
		FCollisionShape Sphere = FCollisionShape::MakeSphere(Radius);
		FCollisionObjectQueryParams ObjectQuery;
		ObjectQuery.AddObjectTypesToQuery(ECC_Pawn);
		ObjectQuery.AddObjectTypesToQuery(ECC_PhysicsBody);

		PlayerDeath();
		bool bHit = GetWorld()->OverlapMultiByObjectType(
			Overlaps,
			Origin,
			FQuat::Identity,
			ObjectQuery,
			Sphere
		);

		/*DrawDebugSphere(
			GetWorld(),
			Origin,        // center
			Radius,        // radius
			32,            // segments (higher = smoother circle)
			FColor::Red,   // color
			false,         // persistent lines? (true = stays forever, false = disappears)
			2.0f,          // life time in seconds
			0,             // depth priority
			2.0f           // line thickness
		);

		*/
		FVector ExplosionLoc = GetActorLocation();
		ExplosionLoc.Z = 30.f;



		if (ExplosionEffect)
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ExplosionEffect, ExplosionLoc, GetActorRotation());


		}




		bool found = false;
		if (bHit)
		{
			for (auto& e : Overlaps)
			{
				PlayerController = Cast<ABlastRunnerController>(GetController());
				ABlastRunnerEnenmyBasic* Enenmy = Cast<ABlastRunnerEnenmyBasic>(e.GetActor());
				if (Enenmy)
				{
					score += 10;
					PlayerController->UpadateScore(score);

					UNiagaraFunctionLibrary::SpawnSystemAtLocation(
						GetWorld(),
						EnenmyEffect,
						Enenmy->GetActorLocation(),
						Enenmy->GetActorRotation()


					);


					PlayerController->ClientStartCameraShake(HitCameraShake, 5.f);


					Enenmy->Destroy();

					UE_LOG(LogTemp, Error, TEXT("ENEMY IS KILLED!"));
					found = true;
				}



			}

		}


		if (!found)
		{
			TakeDamage(1.f);
		}
		UGameplayStatics::PlaySound2D(GetWorld(), ExploadeSound);
		ERunnerState::Green;
		ColorTimer = 0.0;
		SwitchTORed = 0;
	}
}

void ABlastRunnerPlayer::PlayerDeath()
{
	if (Life <= 0)
	{
		//UGameplayStatics::SetGamePaused(GetWorld(), true);
		PlayerController = Cast<ABlastRunnerController>(GetController());
		if (PlayerController)
		{

			PlayerController->DeathUI();
			UGameplayStatics::SetGamePaused(GetWorld(), true);
			
		}
	}



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
		
		Blast();
		return;
	}


	if (ColorTimer >= 3.7f)
	{
		BlastRunnerWidget->MakeChargeToGreen();
		SwitchTORed = 2;
		ERunnerState::Yellow;
		UGameplayStatics::PlaySound2D(GetWorld(), CountDownSound);
		return;
	}


	ColorTimer = FMath::Clamp(ColorTimer += .3f, 0.0f, 5.f);
	BlastRunnerWidget->MakeChargeToGreen();
	float percentage = ColorTimer / 5.f;
	ERunnerState::Green;

	BlastRunnerWidget->UpdateUI(percentage);
	

}


void ABlastRunnerPlayer::TakeDamage(float Value)
{

	Life = FMath::Clamp(Life -= Value, 0.0f, 4.f);
	float Percentage = Life / 4;

	if (CharacterController)
		CharacterController->UpdateHealth(Percentage);

	


}

void ABlastRunnerPlayer::CameraHitShake()
{

	PlayerController->ClientStartCameraShake(HitCameraShake, 5.f);

}

