// Fill out your copyright notice in the Description page of Project Settings.


#include "BoundWall.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BlastRunner/Public/BlastRunnerPlayer.h"
// Sets default values
ABoundWall::ABoundWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponents"));
	SetRootComponent(BoxComponent);

	WallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
	WallMesh->SetupAttachment(BoxComponent);

}

// Called when the game starts or when spawned
void ABoundWall::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ABoundWall::OnOverlapBegin);
	
}

void ABoundWall::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABlastRunnerPlayer* Player = Cast<ABlastRunnerPlayer>(OtherActor);
	if (Player)
	{
		UE_LOG(LogTemp, Warning, TEXT("Wall is colliding!"));
		UGameplayStatics::PlaySound2D(GetWorld(),WallExplosion);
		Player->TakeDamage(1.f);
		Player->PlayerDeath();
		return;
	}

}

void ABoundWall::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

// Called every frame
void ABoundWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

