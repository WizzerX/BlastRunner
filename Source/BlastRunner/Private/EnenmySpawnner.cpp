// Fill out your copyright notice in the Description page of Project Settings.


#include "EnenmySpawnner.h"
#include "Components/BoxComponent.h"
#include "BlastRunner/Public/BlastRunnerPlayer.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
AEnenmySpawnner::AEnenmySpawnner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));
	SetRootComponent(SpawnVolume);

    
    Player = Cast<ABlastRunnerPlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

void AEnenmySpawnner::SpawnEnemy()
{
    if (!EnemyClass) return;

    FVector Origin = SpawnVolume->GetComponentLocation();
    FVector Extent = SpawnVolume->GetScaledBoxExtent();

    FVector SpawnLocation = Origin + FVector(
        FMath::FRandRange(-Extent.X, Extent.X),
        FMath::FRandRange(-Extent.Y, Extent.Y),
        0.f
    );

  

    FHitResult Hit;
    FCollisionQueryParams Params;
    Params.bTraceComplex = true;
    Params.AddIgnoredActor(this); // ignore the spawner itself

    float SpawnRadius = 50.f; // radius of the sphere to check

    bool bBlocked = GetWorld()->SweepSingleByChannel(
        Hit,
        SpawnLocation,
        SpawnLocation,           // same start/end for sphere check
        FQuat::Identity,
        ECC_WorldStatic,         // collision channel to check (walls, floor, static objects)
        FCollisionShape::MakeSphere(SpawnRadius),
        Params
    );

    FRotator SpawnRotation = FRotator(0.f, FMath::FRandRange(0.f, 360.f), 0.f);
    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;


    if (!bBlocked)
    {
        GetWorld()->SpawnActor<AActor>(EnemyClass, SpawnLocation, SpawnRotation, SpawnParams);

       
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Spawn blocked at location!"));
    }






}

// Called when the game starts or when spawned
void AEnenmySpawnner::BeginPlay()
{
	Super::BeginPlay();
	
    GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AEnenmySpawnner::SpawnEnemy, 4.f, true);



}

// Called every frame
void AEnenmySpawnner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

