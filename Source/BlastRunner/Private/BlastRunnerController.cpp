// Fill out your copyright notice in the Description page of Project Settings.


#include "BlastRunnerController.h"
#include "Components/Widget.h"
#include "ScoreWidget.h"
ABlastRunnerController::ABlastRunnerController()
{

	

}

void ABlastRunnerController::BeginPlay()
{

	Widget = CreateWidget<UScoreWidget>(this, widgetclass);
	if (Widget)
	{
		Widget->AddToViewport();
	}


}
