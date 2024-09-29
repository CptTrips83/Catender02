
#include "CTBuilding.h"

#include "CTDestroyable.h"


ACTBuilding::ACTBuilding()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACTBuilding::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACTBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	
}

void ACTBuilding::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


