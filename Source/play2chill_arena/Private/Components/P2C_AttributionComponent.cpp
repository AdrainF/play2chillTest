// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/P2C_AttributionComponent.h"

#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UP2C_AttributionComponent::UP2C_AttributionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
	Health = MaxHealth;
	Stamina = MaxStamina;
}

void UP2C_AttributionComponent::Server_ApplyHealthChange_Implementation(float Value, AActor* InstigatorActor,
	AActor* DamageActor)
{
	ApplyHealthChange(Value, InstigatorActor, DamageActor);
}

bool UP2C_AttributionComponent::Server_ApplyHealthChange_Validate(float Value, AActor* InstigatorActor,
	AActor* DamageActor)
{
	return true;
}


// Called when the game starts
void UP2C_AttributionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


void UP2C_AttributionComponent::OnRep_Health(const float OldHealth) 
{
	float Delta = Health - OldHealth;
	OnHealthChanged.Broadcast(this, Health, MaxHealth, Delta, LastInstigator, GetOwner());
}

void UP2C_AttributionComponent::OnRep_Stamina(const float OldStamina) 
{
	float Delta = Stamina - OldStamina;
	OnStaminaChanged.Broadcast(this, Stamina, MaxStamina, Delta);
}

void UP2C_AttributionComponent::OnRep_KillCount( const int32 OldKillCount) const
{
	OnKillCountChanged.Broadcast(KillCount);
}

void UP2C_AttributionComponent::ApplyHealthChange(float Value, AActor* InstigatorActor, AActor* DamageActor)
{
	if (GetOwnerRole() != ROLE_Authority || !IsAlive() || Value == 0.0f) return;
	

	float OldHealth = Health;
	LastInstigator = InstigatorActor;
	const float ActualDelta = Health - OldHealth;
	Health = FMath::Clamp(Health + Value, 0.0f, MaxHealth);
	
	OnHealthChanged.Broadcast(this,Health, MaxHealth, ActualDelta, LastInstigator, DamageActor);
}

void UP2C_AttributionComponent::ApplyStaminaChange(float Value)
{
}


void UP2C_AttributionComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UP2C_AttributionComponent, Health);
	//DOREPLIFETIME(UP2C_AttributionComponent, MaxHealth);
	DOREPLIFETIME_CONDITION(UP2C_AttributionComponent, MaxHealth, COND_InitialOnly);
	DOREPLIFETIME(UP2C_AttributionComponent, Stamina);
	//DOREPLIFETIME(UP2C_AttributionComponent, MaxStamina);
	DOREPLIFETIME_CONDITION(UP2C_AttributionComponent, MaxStamina, COND_InitialOnly);
	DOREPLIFETIME(UP2C_AttributionComponent, LastInstigator);
	DOREPLIFETIME(UP2C_AttributionComponent, KillCount);
}

// Called every frame
void UP2C_AttributionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

