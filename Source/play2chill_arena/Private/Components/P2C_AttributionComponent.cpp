// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/P2C_AttributionComponent.h"

#include "Core/P2C_ArenaGameMode.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UP2C_AttributionComponent::UP2C_AttributionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
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


void UP2C_AttributionComponent::Server_ApplyStaminaChange_Implementation(float Value)
{
	ApplyStaminaChange(Value);
}

bool UP2C_AttributionComponent::Server_ApplyStaminaChange_Validate(float Value)
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
	const float Delta = Health - OldHealth;
	OnHealthChanged.Broadcast(this, Health, MaxHealth, Delta, LastInstigator, GetOwner());
}

void UP2C_AttributionComponent::OnRep_Stamina(const float OldStamina) 
{
	const float Delta = Stamina - OldStamina;
	OnStaminaChanged.Broadcast(this, Stamina, MaxStamina, Delta);
}



void UP2C_AttributionComponent::ApplyHealthChange(float Value, AActor* InstigatorActor, AActor* DamageActor)
{
	if (GetOwnerRole() != ROLE_Authority || !IsAlive() || Value == 0.0f) return;
	

	const float OldHealth = Health;
	LastInstigator = InstigatorActor;
	Health = FMath::Clamp(Health + Value, 0.0f, MaxHealth);
	const float ActualDelta = Health - OldHealth;
	if (Health==0.0f)
	{   
		AController* KillerController = nullptr;
		AController* VictimController = nullptr;
		
		APawn* VictimPawn = Cast<APawn>(GetOwner());
		if (VictimPawn)
		{
			VictimController = VictimPawn->GetController();
		}

		APawn* InstigatorPawn = Cast<APawn>(InstigatorActor);
		if (InstigatorPawn)
		{
			KillerController = InstigatorPawn->GetController();
		}
		else if (AController* DirectlyInstigator = Cast<AController>(InstigatorActor))
		{
			KillerController = DirectlyInstigator;
		}
		
		
		
		AP2C_ArenaGameMode* GMArena= GetWorld()->GetAuthGameMode<AP2C_ArenaGameMode>();

		if (GMArena && KillerController && VictimController)
		{
			GMArena->NotifyKill(KillerController, VictimController);
			OnDeath.Broadcast(this,InstigatorActor,DamageActor);
		}
		
	}
	
	OnHealthChanged.Broadcast(this,Health, MaxHealth, ActualDelta, LastInstigator, DamageActor);
}

void UP2C_AttributionComponent::ApplyStaminaChange(float Value)
{
	if (GetOwnerRole() != ROLE_Authority ||  Value == 0.0f) return;

	const float OldStamina = Stamina;
	Stamina = FMath::Clamp(Stamina + Value, 0.0f, Stamina);
	const float ActualDelta = Stamina - OldStamina;

	OnStaminaChanged.Broadcast(this,Stamina,MaxStamina,ActualDelta);
}

void UP2C_AttributionComponent::HandleStaminaRegen(const float DeltaTime)
{
	if (Stamina < MaxStamina)
	{
		// Obliczamy nową wartość
		const float OldStamina = Stamina;
		const float NewStamina = Stamina + (StaminaRegenRate * DeltaTime);
		const float ActualDelta = Stamina - OldStamina;
		// Clamp zapobiega przekroczeniu MaxStamina
		Stamina = FMath::Clamp(NewStamina, 0.0f, MaxStamina);
		OnStaminaChanged.Broadcast(this,Stamina,MaxStamina,ActualDelta);
	}
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
	DOREPLIFETIME_CONDITION(UP2C_AttributionComponent, StaminaRegenRate, COND_InitialOnly);
}

// Called every frame
void UP2C_AttributionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	HandleStaminaRegen(DeltaTime);
	// ...
}

