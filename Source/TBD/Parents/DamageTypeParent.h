// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "DamageTypeParent.generated.h"

/**
 * 
 */
UCLASS()
class TBD_API UDamageTypeParent : public UDamageType
{
	GENERATED_BODY()
	
public:
UPROPERTY(EditAnywhere)
float BaseDamage = 1;
UPROPERTY(EditAnywhere)
bool bIsDamageOverTime = false;
UPROPERTY(EditAnywhere)
float DamageUpdateTime = 1;
UPROPERTY(EditAnywhere)
int DamageUpdateNumber = 5;
UPROPERTY(EditAnywhere)
float DamageOverTimeDamage = 2;
UPROPERTY()
AActor * ActorToIgnre;
UPROPERTY(EditAnywhere)
bool bIsFire = false;
};
