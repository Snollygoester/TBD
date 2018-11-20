// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthWidget.h"
#include "Components/ProgressBar.h"
void UHealthWidget::SetHealthBarColor(FLinearColor Color)
{
	HealthBar->SetFillColorAndOpacity(Color);
	
}

void UHealthWidget::SetHealthBarPercent(float Percent)
{
	HealthBar->SetPercent(Percent);
}

void UHealthWidget::SetFuelBarPercent(float Percent)
{
	FuelBar->SetPercent(Percent);
}
