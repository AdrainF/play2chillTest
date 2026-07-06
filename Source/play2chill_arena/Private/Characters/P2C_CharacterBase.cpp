// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/P2C_CharacterBase.h"

#include "Components/P2C_AttributionComponent.h"
#include "Components/WidgetComponent.h"
#include "UI/P2C_OverheadHealthWidget.h"


// Sets default values
AP2C_CharacterBase::AP2C_CharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AttributionComp=CreateDefaultSubobject<UP2C_AttributionComponent>(TEXT("AttributionComp"));
	AttributionComp->OnHealthChanged.AddDynamic(this, &AP2C_CharacterBase::UpdateOverheadHealth);
	
	OverheadHealthWidget=CreateDefaultSubobject<UWidgetComponent>(TEXT("OverheadHealthComp"));
	OverheadHealthWidget->SetupAttachment(RootComponent);
	OverheadHealthWidget->SetWidgetSpace(EWidgetSpace::Screen);
	OverheadHealthWidget->SetDrawAtDesiredSize(true);
	OverheadHealthWidget->SetVisibility(false);

}

void AP2C_CharacterBase::UpdateOverheadHealth(UP2C_AttributionComponent* AttributionComponent, float OldValue,
	float MaxValue, float NewValue, AActor* InstigatorActor, AActor* DamagedActor)
{
	if (!OverheadHealthWidget) return;
	
	const bool bShouldBeVisible = (NewValue < MaxValue) && (NewValue > 0.f);
	OverheadHealthWidget->SetVisibility(bShouldBeVisible);
 
	if (bShouldBeVisible)
	{
		if (UP2C_OverheadHealthWidget* HealthWidget = Cast<UP2C_OverheadHealthWidget>(OverheadHealthWidget->GetUserWidgetObject()))
		{
			HealthWidget->SetHealthPercent(NewValue / MaxValue);
		}
	}
}

// Called when the game starts or when spawned
void AP2C_CharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AP2C_CharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AP2C_CharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

