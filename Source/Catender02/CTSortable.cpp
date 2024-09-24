
#include "CTSortable.h"

#include "Components/CTSortingComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ACTSortable::ACTSortable()
{
	SortingComponent = CreateDefaultSubobject<UCTSortingComponent>(TEXT("Sorting"));
	AddOwnedComponent(SortingComponent);
}

/**
 * @brief Updates the rotation of the character based on its current velocity.
 *
 * This function checks the current velocity of the character and adjusts the yaw rotation
 * accordingly. If the velocity in the X direction is negative, it sets the yaw to 180 degrees.
 * The updated rotation is then set in the controller.
 */
void ACTSortable::UpdateRotation()
{
	FVector CurrentVelocity = GetCharacterMovement()->Velocity;
	
	if(CurrentVelocity.X == 0) return;
		
	AController* Controller = GetController();
	
	if(!Controller) return;

	float Yaw = 0;

	if(CurrentVelocity.X < 0)
	{
		Yaw = 180;
	}

	FRotator Rotation = FRotator(0, Yaw, 0);
	
    Controller->SetControlRotation(Rotation);
}

void ACTSortable::BeginPlay()
{
	Super::BeginPlay();

	GameModeLevel = static_cast<ACTGameModeLevel*>(GetWorld()->GetAuthGameMode());

	
}
