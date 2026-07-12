// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles/P2C_ProjectileBase.h"

#include "Components/P2C_AttributionComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

class UP2C_AbilitySystemComponent;
// Sets default values
AP2C_ProjectileBase::AP2C_ProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent=CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->InitSphereRadius(ProjectileRadius);
	RootComponent = CollisionComponent;
	
	ProjectileMovementComponent=CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->ProjectileGravityScale=0.0f;
	ProjectileMovementComponent->InitialSpeed=ProjectileSpeed;

	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bInitialVelocityInLocalSpace = true;
	
	EffectComp=CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EffectComp"));
	EffectComp->SetupAttachment(RootComponent);


	
	bReplicates = true;
//	SetReplicateMovement(true);
//	SetNetUpdateFrequency(33.0f);
	
}

void AP2C_ProjectileBase::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!HasAuthority()) return;
	if (OtherActor && OtherActor!= GetInstigator())
	{
		UP2C_AttributionComponent* AttributeComp=Cast<UP2C_AttributionComponent>(OtherActor->GetComponentByClass(UP2C_AttributionComponent::StaticClass()));

		if (AttributeComp)
		{
			ProcessHit(OtherActor);
		}
		
	}
}

void AP2C_ProjectileBase::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!HasAuthority()) return;
	if (OtherActor != GetInstigator())
	{
		Explode();
	}
}

// Called when the game starts or when spawned
void AP2C_ProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
	if (HasAuthority())
	{
		CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AP2C_ProjectileBase::OnBeginOverlap);
		CollisionComponent->OnComponentHit.AddDynamic(this, &AP2C_ProjectileBase::OnActorHit);
	}
}

void AP2C_ProjectileBase::ProcessHit(AActor* OtherActor)
{
	if (!HasAuthority()) return;
 
	
	if (bHasImpacted || OtherActor == GetInstigator() || OtherActor == this) return;
 
	bHasImpacted = true;
 
	
	if (OtherActor)
	{
		UP2C_AttributionComponent* AttributeComp = Cast<UP2C_AttributionComponent>(OtherActor->GetComponentByClass(UP2C_AttributionComponent::StaticClass()));
		if (AttributeComp)
		{
			AttributeComp->Server_ApplyHealthChange(-10.0f, GetInstigator(), OtherActor);
		}
	}
	
	Explode();
}

void AP2C_ProjectileBase::Explode_Implementation()
{
	if (ensure(IsValid(this)))
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());
		UGameplayStatics::PlaySoundAtLocation(this, ExplodeSound, GetActorLocation(), GetActorRotation());
		Destroy();

	}
	
}

// Called every frame
void AP2C_ProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

