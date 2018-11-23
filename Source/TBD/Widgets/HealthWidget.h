// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthWidget.generated.h"

/**
 * 
 */
UCLASS()
class TBD_API UHealthWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar * HealthBar;
	UPROPERTY(meta = (BindWidget))
	class UProgressBar * FuelBar;
	UPROPERTY(meta = (BindWidget))
		class UImage * Ximage;
	UPROPERTY(meta = (BindWidget))
		class UImage * Ximage1;
	UPROPERTY(meta = (BindWidget))
		class UImage * Ximage2;
	int I = 0;

public:
	void SetHealthBarColor(FLinearColor Color);
	void  SetHealthBarPercent(float Percent);
	void  SetFuelBarPercent(float Percent);
	void SetXimage();
};
