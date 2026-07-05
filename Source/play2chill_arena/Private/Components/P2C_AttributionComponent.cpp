// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/P2C_AttributionComponent.h"

#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UP2C_AttributionComponent::UP2C_AttributionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	Health = MaxHealth;
	Stamina = MaxStamina;
}


// Called when the game starts
void UP2C_AttributionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


void UP2C_AttributionComponent::OnRep_Health(float OldHealth)
{
	float Delta = Health - OldHealth;
	OnHealthChanged.Broadcast(this, Health, MaxHealth, Delta, LastInstigator, GetOwner());
}

void UP2C_AttributionComponent::OnRep_Stamina(float OldStamina)
{
	float Delta = Stamina - OldStamina;
	OnStaminaChanged.Broadcast(this, Stamina, MaxStamina, Delta);
}

void UP2C_AttributionComponent::ApplyHealthChange(float Value, AActor* InstigatorActor, AActor* DamageActor)
{
	if (Value == 0.0f || !IsAlive()) return;

	float OldHealth = Health;
	LastInstigator = InstigatorActor;

	Health = FMath::Clamp(Health + Value, 0.0f, MaxHealth);
	
	OnHealthChanged.Broadcast(this,Health, MaxHealth, Value, LastInstigator, DamageActor);
}

void UP2C_AttributionComponent::ApplyStaminaChange(float Value)
{
}


void UP2C_AttributionComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UP2C_AttributionComponent, Health);
	DOREPLIFETIME(UP2C_AttributionComponent, MaxHealth);
	DOREPLIFETIME(UP2C_AttributionComponent, Stamina);
	DOREPLIFETIME(UP2C_AttributionComponent, MaxStamina);
	DOREPLIFETIME(UP2C_AttributionComponent, LastInstigator);
}

// Called every frame
void UP2C_AttributionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

