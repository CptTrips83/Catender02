
#include "CTSortable.h"

#include "Components/CTSortingComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ACTSortable::ACTSortable()
{
	SortingComponent = CreateDefaultSubobject<UCTSortingComponent>(TEXT("Sorting"));
	AddOwnedComponent(SortingComponent);
}

void ACTSortable::BeginPlay()
{
	Super::BeginPlay();

	GameModeLevel = static_cast<ACTGameModeLevel*>(GetWorld()->GetAuthGameMode());

	
}
