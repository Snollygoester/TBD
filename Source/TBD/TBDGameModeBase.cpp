// Fill out your copyright notice in the Description page of Project Settings.

#include "TBDGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "GameFramework/PlayerStart.h"
#include "Parents/CharacterParent.h"
#include "Widgets/HealthWidget.h"
#include "Engine/World.h"
#include "Public/TimerManager.h"
void ATBDGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayersStartPoints);
	for (size_t i = 0; i < PlayerToSpawn ; i++) 
	{
		Index = i;
		for (size_t i = 0; i < PlayersStartPoints.Num(); i++)
		{
			if (PlayersStartPoints[i]->ActorHasTag(FName(*FString::FromInt(Index)))) {
				UGameplayStatics::CreatePlayer(GetWorld(), Index);
				APawn * Pawn = GetWorld()->SpawnActor<APawn>(PawnToSpawn, PlayersStartPoints[i]->GetActorTransform());
				ACharacterParent * chart = Cast<ACharacterParent>(Pawn);
					if (chart != nullptr) {
						chart->PlayerUniqueTag = FString::FromInt(i);
						chart->Tags.Add(FName(*chart->PlayerUniqueTag));
						UHealthWidget * HealthWidget = CreateWidget< UHealthWidget>(GetWorld(), HealthWidgetSubClass);
						HealthWidget->AddToViewport();
						HealthWidget->SetPositionInViewport(Positions[i]);
						HealthWidget->SetHealthBarColor(Colors[i]);
						HealthWidget->SetHealthBarPercent(1);
						chart->SetHealthWidget(HealthWidget);
					}
				UGameplayStatics::GetPlayerController(GetWorld(), Index)->Possess(Pawn);
				Players.AddUnique(Pawn);
			}
		}
	}
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ATBDGameModeBase::OnGameStart, TimeUntilGameStart);
}

void ATBDGameModeBase::OnGameStart()
{
	for (APawn *Pawn : Players)
	{
		ACharacterParent * chart = Cast<ACharacterParent>(Pawn);
		if (chart != nullptr) {
			chart->BisGameStarted = true;
		}
	}
}
