
#include "CTFriendlyNPCCharacter.h"


ACTFriendlyNPCCharacter::ACTFriendlyNPCCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACTFriendlyNPCCharacter::BeginPlay()
{
	Super::BeginPlay();	
}

void ACTFriendlyNPCCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACTFriendlyNPCCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

