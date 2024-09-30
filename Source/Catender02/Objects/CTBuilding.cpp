
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
	
}

void ACTBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateInteractionCollision();
}

void ACTBuilding::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

/**
 * Checks if there is a direct line of sight between this building and the HQ building.
 *
 * The method performs a line trace from this building's location to the HQ building's location.
 * If any Destroyables are detected along the line trace, it returns false.
 * If no obstacles are detected, it returns true.
 *
 * @return True if there is a direct line of sight to the HQ, false otherwise.
 */
bool ACTBuilding::HasLineOfSightToHQ()
{	
	const ACTBuildingHQ* HQ = GetGameMode()->GetBuildingHQ();
	if(!HQ) return false;
	TArray<FHitResult> HitResult; 
	const FVector Start = FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z);
	const FVector End = FVector(HQ->GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z);
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	const ECollisionChannel CollisionChannel = GetGameMode()->WorldBuildingVisibilityComponent->BuildingVisibilityChannel;
	
	GetWorld()->LineTraceMultiByChannel(HitResult, Start, End, CollisionChannel, QueryParams);

	for(const FHitResult Hit : HitResult)
	{
		const FVector HitLocation = FVector(Hit.Location.X, GetActorLocation().Y, GetActorLocation().Z); 
		DrawDebugLine(GetWorld(), Start, HitLocation, FColor::Red, false, 1.0f, 0, 1.0f);
		
		return false;
	}
	
	DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1.0f, 0, 1.0f);
	return true;
}

/**
 * Updates the interaction collision state of the building.
 *
 * This method checks the current state of the building. If the building is not in an
 * Invisible or Inactive state, the method returns early. Otherwise, it checks if there
 * is a direct line of sight to the HQ. Based on the result, it sets the building's active
 * state accordingly: active if there is a line of sight, inactive if there is not.
 */
void ACTBuilding::UpdateInteractionCollision()
{
	if(GetBuildingComponent()->GetBuildingState() != EBuildingState::Invisible &&
		GetBuildingComponent()->GetBuildingState() != EBuildingState::Inactive) return;

	if(HasLineOfSightToHQ())
	{
		SetActive(true);
	}
	else
	{
		SetActive(false);
	}
}


