// Fill out your copyright notice in the Description page of Project Settings.


#include "BlastRunnerEnenmyBasic.h"
#include "Components/CapsuleComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "AIController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "BlastRunner/Public/BlastRunnerPlayer.h"
#include "BlastRunner/Public/BlastRunnerController.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
ABlastRunnerEnenmyBasic::ABlastRunnerEnenmyBasic()
{
 PrimaryActorTick.bCanEverTick = true;

 PlayerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));
 PlayerMesh->SetupAttachment(GetCapsuleComponent());




 PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("Perceptation"));


 PawnSensingComponent->OnSeePawn.AddDynamic(this, &ABlastRunnerEnenmyBasic::OnSeenPawn);
 AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

 EnemyState = EEnemyState::IDLE;
 TargetPawn = nullptr;
 


}


void ABlastRunnerEnenmyBasic::BeginPlay()
{
	Super::BeginPlay();
	
}


void ABlastRunnerEnenmyBasic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABlastRunnerEnenmyBasic::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABlastRunnerEnenmyBasic::OnSeenPawn(APawn* Pawn)
{
	if (!Pawn) return;
	TargetPawn = Pawn;
	EnemyState = EEnemyState::Chase;

	//UE_LOG(LogTemp, Warning, TEXT("Player seen! Starting chase."));

	StartChasing();

}

void ABlastRunnerEnenmyBasic::StartChasing()
{
	if (!TargetPawn) return;

	AAIController* AICon = Cast<AAIController>(GetController());
	if (!AICon) return;

	// Move to player once
	AICon->MoveToActor(TargetPawn, 10.f);

	// Start timer to check distance every 0.2 seconds
	GetWorldTimerManager().SetTimer(CheckDistanceTimerHandle, this, &ABlastRunnerEnenmyBasic::CheckDistanceToPlayer, 0.2f, true);

}

void ABlastRunnerEnenmyBasic::CheckDistanceToPlayer()
{
	if (!TargetPawn) return;




	FVector EnemyLoc = GetActorLocation();
	FVector PlayerLoc = TargetPawn->GetActorLocation();
	EnemyLoc.Z = 0.f;
	PlayerLoc.Z = 0.f;

	float Distance = FVector::Dist(EnemyLoc, PlayerLoc);

	if (Distance <= 300.f)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Enemy attacking player: %s"), *TargetPawn->GetName());
		EnemyState = EEnemyState::Attack;
		AttackThePlayer();
	
		// Stop checking
		GetWorldTimerManager().ClearTimer(CheckDistanceTimerHandle);

	}
}

void ABlastRunnerEnenmyBasic::AttackThePlayer()
{
	if (!TargetPawn) return;

	FHitResult HitResult;
	
	UKismetSystemLibrary::SphereTraceSingle(GetWorld(), TargetPawn->GetTargetLocation(), TargetPawn->GetTargetLocation() * 500.f, 50.f,
		ETraceTypeQuery::TraceTypeQuery1, false, ChosetheActor, EDrawDebugTrace::ForDuration, HitResult, true);
	ABlastRunnerPlayer* Player = Cast<ABlastRunnerPlayer>(HitResult.GetActor());

	if (Player)
	{

		
		UE_LOG(LogTemp, Warning, TEXT("Enemy attacking player: %s"), *TargetPawn->GetName());
		Player->TakeDamage(1.f);
		UGameplayStatics::PlaySound2D(GetWorld(), BlastSound);
		this->Destroy();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Controller Cast FAILED : %s"), *TargetPawn->GetName());
	}

	


}






