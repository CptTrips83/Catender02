

#include "ACTEnemyNPCCharacter.h"

ACTEnemyNPCCharacter::ACTEnemyNPCCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ACTEnemyNPCCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACTEnemyNPCCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACTEnemyNPCCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

