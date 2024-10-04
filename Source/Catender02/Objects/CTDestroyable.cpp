

#include "CTDestroyable.h"


ACTDestroyable::ACTDestroyable()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACTDestroyable::BeginPlay()
{
	Super::BeginPlay();

	GetBuildingComponent()->OnConstructionFinished.AddDynamic(this, &ACTDestroyable::ConstructionFinished);
}

void ACTDestroyable::UpdateInteractionCollision(bool CollisionEnabled)
{
	
}

void ACTDestroyable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACTDestroyable::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACTDestroyable::ConstructionFinished(ACTBuildable* Buildable)
{
	GetGameMode()->WorldBuildableComponent->RemoveBuildable(this);
	Destroy();
}

