// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreWidget.h"
#include "Components/ProgressBar.h"
void UScoreWidget::UpdateHealth(float value)
{
	Health->SetPercent(value);

	UE_LOG(LogTemp, Warning, TEXT("Percentage Update"));
}
