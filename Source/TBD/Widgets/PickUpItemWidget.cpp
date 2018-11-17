// Fill out your copyright notice in the Description page of Project Settings.

#include "PickUpItemWidget.h"
#include "Components/ProgressBar.h"
void UPickUpItemWidget::SetProgressBarImage(FSlateBrush Image)
{
	PickUpProgressBar->WidgetStyle.FillImage = Image;
	
}

void UPickUpItemWidget::SetProgressBarPercent(float Percent)
{
	PickUpProgressBar->SetPercent(Percent);
}
