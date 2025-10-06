// Fill out your copyright notice in the Description page of Project Settings.


#include "BlastRunnerController.h"
#include "Components/Widget.h"
#include "ScoreWidget.h"
#include "DeathScreen.h"
#include "BlastRunner/Public/BlastRunnerPlayer.h"
#include  "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
ABlastRunnerController::ABlastRunnerController()
{

	

}

void ABlastRunnerController::UpdateHealth(float value)
{
	if (Widget)
	{
		Widget->UpdateHealth(value);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("CAST FAILED"));
	}

}

void ABlastRunnerController::UpadateScore(int NewScore)
{
	if (Widget)
	{
		DeathScore = NewScore;
		FString ScoreString = FString::Printf(TEXT("SCORE: %d"), NewScore);
		Widget->Text->SetText(FText::FromString(ScoreString));
	}

}

void ABlastRunnerController::DeathUI()
{
	if (Widget)
	{
		Widget->RemoveFromParent();
		DeathWidget = CreateWidget<UDeathScreen>(this, DeathUIWidget);
		DeathWidget->AddToViewport();
		FString Score = FString::Printf(TEXT("SCORE:%d"), DeathScore);
		DeathWidget->Score->SetText(FText::FromString(Score));
		bShowMouseCursor = true;
		
	}




}

void ABlastRunnerController::RestartGame()
{

	if (DeathWidget)
	{
		DeathWidget->RemoveFromParent();
	}
	 ABlastRunnerPlayer* PlayerX = Cast<ABlastRunnerPlayer>(GetPawn());
	 FName CurrentLevel = FName(*GetWorld()->GetName());
	 UGameplayStatics::OpenLevel(this, CurrentLevel);




	Widget = CreateWidget<UScoreWidget>(this, widgetclass);
	if (Widget)
	{
		Widget->AddToViewport();

	}




}

void ABlastRunnerController::BeginPlay()
{

	Widget = CreateWidget<UScoreWidget>(this, widgetclass);
	if (Widget)
	{
		Widget->AddToViewport();
		
	}


}
