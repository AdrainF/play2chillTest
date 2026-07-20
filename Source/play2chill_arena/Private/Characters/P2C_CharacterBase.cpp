// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/P2C_CharacterBase.h"

#include "Components/P2C_AttributionComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UI/P2C_OverheadHealthWidget.h"


// Sets default values
AP2C_CharacterBase::AP2C_CharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	PrimaryActorTick.TickInterval = 0.1f;

	AttrComp=CreateDefaultSubobject<UP2C_AttributionComponent>(TEXT("AttributionComp"));
	
	OverheadHealthWidget=CreateDefaultSubobject<UWidgetComponent>(TEXT("OverheadHealthComp"));
	OverheadHealthWidget->SetupAttachment(RootComponent);
	OverheadHealthWidget->SetWidgetSpace(EWidgetSpace::Screen);
	OverheadHealthWidget->SetDrawAtDesiredSize(true);
	OverheadHealthWidget->SetVisibility(false);
	OverheadHealthWidget->SetIsReplicated(true);
}

void AP2C_CharacterBase::UpdateOverheadHealth(UP2C_AttributionComponent* AttributionComp, float Health,
	float MaxHealth , float HealthDelta, AActor* InstigatorActor, AActor* DamagedActor)
{
	if (!OverheadHealthWidget) return;
	
	const bool bShouldBeVisible = (Health < MaxHealth) && (Health > 0.f);
	OverheadHealthWidget->SetVisibility(bShouldBeVisible);
 
	if (bShouldBeVisible)
	{
		if (UP2C_OverheadHealthWidget* HealthWidget = Cast<UP2C_OverheadHealthWidget>(OverheadHealthWidget->GetWidget()))
		{
			HealthWidget->SetHealthPercent(Health / MaxHealth);
		}
	}
}

// Called when the game starts or when spawned
void AP2C_CharacterBase::BeginPlay()
{
	Super::BeginPlay();

	if (AttrComp)
	{
		//Bind the UpdateOverheadHealth function to the OnHealthChanged event of the AttributionComp
		if (!AttrComp->OnHealthChanged.IsAlreadyBound(this, &AP2C_CharacterBase::UpdateOverheadHealth))
		{
			AttrComp->OnHealthChanged.AddDynamic(this, &AP2C_CharacterBase::UpdateOverheadHealth);
		}
		
		// Initialize the overhead health widget with the current health values
		UpdateOverheadHealth(AttrComp, AttrComp->GetHealth(), AttrComp->GetMaxHealth(), AttrComp->GetHealth(), nullptr, this);
	}
}

// Called every frame
void AP2C_CharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	OptimizationCheckTimer += DeltaTime;
	if (OptimizationCheckTimer >= 1.0f)
	{
		OptimizationCheckTimer = 0.0f;
        
		APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
		if (PC && PC->GetPawn())
		{
			float Distance = FVector::Dist(GetActorLocation(), PC->GetPawn()->GetActorLocation());
 
			if (Distance > MaxVisibilityDistance)
			{
				PrimaryActorTick.TickInterval = 0.5f;
			}
			else if (Distance > 2000.0f)
			{
				PrimaryActorTick.TickInterval = 0.1f;
			}
			else
			{
				PrimaryActorTick.TickInterval = 0.0f;
			}
		}
	}
}

// Called to bind functionality to input
void AP2C_CharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
}

