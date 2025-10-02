// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BlastRunnerWidget.generated.h"

/**
 * 
 */



UCLASS()
class BLASTRUNNER_API UBlastRunnerWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* TimeBomb;


	virtual void NativeConstruct();

	
	void UpdateUI(float Value);


	
};
