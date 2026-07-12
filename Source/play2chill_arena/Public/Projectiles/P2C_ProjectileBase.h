// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "P2C_ProjectileBase.generated.h"

class UProjectileMovementComponent;
class USphereComponent;
class UParticleSystemComponent;
UCLASS()
class PLAY2CHILL_ARENA_API AP2C_ProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AP2C_ProjectileBase();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	TObjectPtr<USphereComponent> CollisionComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* EffectComp;
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* ImpactVFX;
	UPROPERTY(EditAnywhere, Category = "Audio")
	UAudioComponent* FlySound;
	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundBase* ExplodeSound;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float ProjectileSpeed=1000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float ProjectileDamage=10.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float ProjectileRadius=15.0f;

	protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UFUNCTION(BlueprintCallable, Category = "Projectile")
	void ProcessHit(AActor* OtherActor);
	UFUNCTION(BlueprintCallable, Category = "Projectile")
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Explode();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	bool bHasImpacted = false;

};
