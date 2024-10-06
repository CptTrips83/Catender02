

#include "CTDestroyable.h"


ACTDestroyable::ACTDestroyable()
{
	PrimaryActorTick.bCanEverTick = true;

	BuildingVisibilityCollision = CreateDefaultSubobject<UBoxComponent>(FName("BuildingVisibilityCollision"));
	BuildingVisibilityCollision->SetupAttachment(GetRootComponent());
	BuildingVisibilityCollision->SetBoxExtent(FVector(32.0f, 100.0f, 100.0f));
	
}

void ACTDestroyable::BeginPlay()
{
	Super::BeginPlay();

	GetBuildingComponent()->OnConstructionFinished.AddDynamic(this, &ACTDestroyable::ConstructionFinished);
}

void ACTDestroyable::UpdateInteractionCollision(bool CollisionEnabled)
{	
	Super::UpdateInteractionCollision(CollisionEnabled);
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

