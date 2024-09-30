
#include "CTBuilding.h"

#include "Catender02/Objects/CTBuildingHQ.h"
#include "Kismet/KismetSystemLibrary.h"

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

bool ACTBuilding::HasLineOfSightToHQ()
{	
	const ACTBuildingHQ* HQ = GetGameMode()->GetBuildingHQ();
	FHitResult Hit; 
	const FVector Start = FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z);
	const FVector End = FVector(HQ->GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z);
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	GetWorld()->LineTraceSingleByProfile(Hit, Start, End, "Destroyable", QueryParams);
	DrawDebugLine(GetWorld(), Start, End, Hit.bBlockingHit ? FColor::Blue : FColor::Red, false, 5.0f, 0, 1.0f);

	return Hit.bBlockingHit;
}

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


