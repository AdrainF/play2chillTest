// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "P2C_AttributionComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FOnHealthChanged, UP2C_AttributionComponent*, AttributionComp, float, Health, float, MaxHealth, float, HealthDelta, AActor*, InstigatorActor, AActor*, DamageActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnStaminaChanged, UP2C_AttributionComponent*, AttributionComp, float, Stamina, float, MaxStamina, float, StaminaDelta);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PLAY2CHILL_ARENA_API UP2C_AttributionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UP2C_AttributionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Attributes
	UPROPERTY(EditAnywhere, ReplicatedUsing = OnRep_Health, Category = "Attributes")
	float Health=0.0f;
	UPROPERTY(EditAnywhere, Replicated, Category = "Attributes")
	float MaxHealth=100.0f;
	UPROPERTY(EditAnywhere, ReplicatedUsing = OnRep_Stamina, Category = "Attributes")
	float Stamina=0.0f;
	UPROPERTY(EditAnywhere, Replicated, Category = "Attributes")
	float MaxStamina=100.0f;

	UPROPERTY(Replicated)
	AActor* LastInstigator;
	// Replication
	UFUNCTION()
	void OnRep_Health(float OldHealth);
	UFUNCTION()
	void OnRep_Stamina(float OldStamina);

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	void ApplyHealthChange(float Value, AActor* InstigatorActor = nullptr, AActor* DamageActor = nullptr);
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	void ApplyStaminaChange(float Value);
	
public:
	
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnHealthChanged OnHealthChanged;
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnStaminaChanged OnStaminaChanged;
	
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool IsAlive() const { return Health > 0.0f; }
 
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	float GetHealth() const { return Health; }
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	float GetStamina() const {return Stamina; }
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	float GetMaxHealth() const { return MaxHealth; }
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	float GetMaxStamina() const {return MaxStamina; }

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
