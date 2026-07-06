// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/P2C_OverheadHealthWidget.h"

#include "Components/ProgressBar.h"

void UP2C_OverheadHealthWidget::SetHealthPercent(float Percent)
{
	HealthBar->SetPercent(Percent);
}
