
#include "CTBuilding.h"

#include "CTDestroyable.h"
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
	TArray<FHitResult> Hit; 
	const FVector Start = FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z);
	const FVector End = FVector(HQ->GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z);
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	GetWorld()->LineTraceMultiByChannel(Hit, Start, End, ECC_WorldDynamic, QueryParams);
	

	for(FHitResult HitResult : Hit)
	{
		if(AActor* Test = HitResult.GetActor(); Test->IsA(ACTDestroyable::StaticClass()))
		{
			ACTDestroyable* Destroyable = Cast<ACTDestroyable>(Test);
			if(Destroyable->GetBuildingComponent()->GetBuildingState() == EBuildingState::Invisible) continue;
			DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 5.0f, 0, 1.0f);
			return false;
		}		
		
	}

	DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 5.0f, 0, 1.0f);
	return true;
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


