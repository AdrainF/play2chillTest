// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/P2C_CharacterBase.h"

// Sets default values
AP2C_CharacterBase::AP2C_CharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

