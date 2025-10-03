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

void UBlastRunnerWidget::MakeChargeToGreen()
{
	FLinearColor NewColor = FLinearColor::Green;
	
	TimeBomb->WidgetStyle.FillImage.TintColor = FSlateColor(NewColor);

}

void UBlastRunnerWidget::MakeChargeToYellow()
{
	//FProgressBarStyle BarStyle = TimeBomb->WidgetStyle;
	FLinearColor NewColor = FLinearColor::Yellow; 
	TimeBomb->WidgetStyle.FillImage.TintColor = FSlateColor(NewColor);
	


}

void UBlastRunnerWidget::MakeChargeToRed()
{
	FLinearColor NewColor = FLinearColor::Red; 
	TimeBomb->WidgetStyle.FillImage.TintColor = FSlateColor(NewColor);


}
