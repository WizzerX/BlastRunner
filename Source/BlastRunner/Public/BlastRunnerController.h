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



class UScoreWidget* Widget;

UPROPERTY(EditAnywhere, BlueprintReadWrite)
TSubclassOf<UUserWidget>widgetclass;

virtual void BeginPlay() override;
	
};
