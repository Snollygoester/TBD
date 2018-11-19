// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TBDGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TBD_API ATBDGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
virtual void BeginPlay() override;
UPROPERTY()
TArray<class APawn *>  Players;
UPROPERTY(EditAnywhere)
TSubclassOf< class UHealthWidget > HealthWidgetSubClass;
UPROPERTY(EditAnywhere)
TArray< FLinearColor> Colors;
UPROPERTY(EditAnywhere)
TArray <FVector2D> Positions;
private:
TArray<AActor *> PlayersStartPoints;
UPROPERTY(EditAnywhere)
int PlayerToSpawn = 4;
int Index = 0;
UPROPERTY(EditAnywhere)
TSubclassOf<class APawn> PawnToSpawn;
};
