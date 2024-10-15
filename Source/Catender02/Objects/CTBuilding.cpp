
#include "CTBuilding.h"

#include "CTDestroyable.h"
#include "Catender02/Objects/CTBuildingHQ.h"

ACTBuilding::ACTBuilding()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACTBuilding::BeginPlay()
{
	Super::BeginPlay();
	SetActive(false);
}

void ACTBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACTBuilding::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}