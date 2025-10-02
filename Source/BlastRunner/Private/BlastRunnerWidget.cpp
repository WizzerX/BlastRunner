// Fill out your copyright notice in the Description page of Project Settings.


#include "BlastRunnerWidget.h"
#include "Components/ProgressBar.h"
void UBlastRunnerWidget::NativeConstruct()
{
	Super::NativeConstruct();



}

void UBlastRunnerWidget::UpdateUI(float Value)
{
	TimeBomb->SetPercent(Value);




}
