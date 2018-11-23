// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnPointParent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Parents/CharacterParent.h"
#include "Kismet/KismetMathLibrary.h"
// Sets default values
ASpawnPointParent::ASpawnPointParent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;


}

// Called when the game starts or when spawned
void ASpawnPointParent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASpawnPointParent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawnPointParent::SetUp()
{
	CharactersParents.Empty();
	TArray<AActor *> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACharacterParent::StaticClass(), Actors);
	for (AActor * Actor : Actors)
	{
		ACharacterParent  *  CharacterParent = Cast< ACharacterParent>(Actor);
		if (CharacterParent != nullptr)
		{
			if (!CharacterParent->bIsDead)
			{
				CharactersParents.Add(CharacterParent);
			}
		}
	}
}

FVector ASpawnPointParent::FindPointToSpawn()
{
	SetUp();
	switch (CharactersParents.Num())
	{
	case 1: {

		for (FVector SpawnPoint : SpawnPoints)
		{
			float CurrntDist = 0;
			CurrntDist = FVector::Dist(CharactersParents[0]->GetActorLocation(), SpawnPoint);
			if (Dist < CurrntDist)
			{
				Dist = CurrntDist;
				FinalSpawnPoint = SpawnPoint;
			}
			
		}
		Dist = 0;
		return FinalSpawnPoint;
		break;
	}
	case 2: {
		for (FVector SpawnPoint : SpawnPoints)
		{
			float CurrntDist = 0;
			TArray<float > Dists;
			Dists.Add(FVector::Dist(CharactersParents[0]->GetActorLocation(), SpawnPoint));
			Dists.Add(FVector::Dist(CharactersParents[1]->GetActorLocation(), SpawnPoint));
			int32 Index;
			UKismetMathLibrary::MinOfFloatArray(Dists, Index, CurrntDist);
			if (Dist < CurrntDist)
			{
				Dist = CurrntDist;
				FinalSpawnPoint = SpawnPoint;
			}	
		}
		UE_LOG(LogTemp, Warning, TEXT(" 2 "));
		Dist = 0;
		return FinalSpawnPoint;
		break;
	}
	case 3: {
		for (FVector SpawnPoint : SpawnPoints)
		{
			float CurrntDist = 0;
			TArray<float > Dists;
			Dists.Add(FVector::Dist(CharactersParents[0]->GetActorLocation(), SpawnPoint));
			Dists.Add(FVector::Dist(CharactersParents[1]->GetActorLocation(), SpawnPoint));
			Dists.Add(FVector::Dist(CharactersParents[2]->GetActorLocation(), SpawnPoint));
			int32 Index;
			UKismetMathLibrary::MinOfFloatArray(Dists, Index, CurrntDist);
			if (Dist < CurrntDist)
			{
				UE_LOG(LogTemp, Warning, TEXT(" %f "), Dist);
				Dist = CurrntDist;
				FinalSpawnPoint = SpawnPoint;
			}
		}
		UE_LOG(LogTemp, Warning, TEXT(" 3 "));
		Dist = 0;
		return FinalSpawnPoint;
		break;
	}
			UE_LOG(LogTemp, Warning, TEXT(" %d char num "), CharactersParents.Num());
			return FVector(0,0,0);
	}
	UE_LOG(LogTemp, Warning, TEXT(" %d char num "), CharactersParents.Num());
	return  FVector(0, 0, 0);
}
