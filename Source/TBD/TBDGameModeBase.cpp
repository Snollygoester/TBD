// Fill out your copyright notice in the Description page of Project Settings.

#include "TBDGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "GameFramework/PlayerStart.h"
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
				UGameplayStatics::GetPlayerController(GetWorld(), Index)->Possess(Pawn);
				Players.AddUnique(Pawn);
			}
		}
	}
}



