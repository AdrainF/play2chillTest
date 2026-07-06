// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "P2C_CharacterBase.generated.h"

class UP2C_AttributionComponent;
class UWidgetComponent;

UCLASS()
class PLAY2CHILL_ARENA_API AP2C_CharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AP2C_CharacterBase();

	UPROPERTY(Blueprintable, BlueprintReadWrite, Category = "Components")
	UP2C_AttributionComponent* AttributionComp;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	TObjectPtr<UWidgetComponent> OverheadHealthWidget;

	UFUNCTION()
	void UpdateOverheadHealth(UP2C_AttributionComponent* AttributionComponent, float OldValue, float  MaxValue , float NewValue , AActor* InstigatorActor, AActor* DamagedActor);
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
