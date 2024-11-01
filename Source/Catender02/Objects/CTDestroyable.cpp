

#include "CTDestroyable.h"

#include "Components/CapsuleComponent.h"


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

	GetInteractionBoxComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ACTDestroyable::DestroyBuilding()
{
	GetBuildingComponent()->SetBuildingState(Invisible);
	GetBuildingComponent()->UpdateBuilding();

	GetCapsuleComponent()->SetCollisionObjectType(ECC_WorldDynamic);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
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
	GetGameMode()->GetWorldBuildableComponent()->RemoveBuildable(this);
	GetInteractionBoxComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Destroy();
}

