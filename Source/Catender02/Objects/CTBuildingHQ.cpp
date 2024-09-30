

#include "CTBuildingHQ.h"


ACTBuildingHQ::ACTBuildingHQ()
{	
	PrimaryActorTick.bCanEverTick = true;
}

void ACTBuildingHQ::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACTBuildingHQ::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACTBuildingHQ::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

bool ACTBuildingHQ::HasLineOfSightToHQ()
{
	return true;
}

