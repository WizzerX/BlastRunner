// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BlastRunnerController.generated.h"

/**
 * 
 */
UCLASS()
class BLASTRUNNER_API ABlastRunnerController : public APlayerController
{
	GENERATED_BODY()

public:



ABlastRunnerController();
public:
void UpdateHealth(float value);

void UpadateScore(int NewScore);

class UScoreWidget* Widget;

int DeathScore;

UPROPERTY(EditAnywhere, BlueprintReadWrite)
TSubclassOf<UUserWidget>widgetclass;


UPROPERTY(EditAnywhere, BlueprintReadWrite)
TSubclassOf<UUserWidget>DeathUIWidget;

class UDeathScreen* DeathWidget;

void DeathUI();


UFUNCTION(BlueprintCallable)
void RestartGame();

virtual void BeginPlay() override;
	
};
