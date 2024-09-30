
#include "CTSortable.h"

#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CTSortingComponent.h"
#include "Kismet/KismetMathLibrary.h"

ACTSortable::ACTSortable()
{
	SortingComponent = CreateDefaultSubobject<UCTSortingComponent>(TEXT("Sorting"));
	AddOwnedComponent(SortingComponent);

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ACTSortable::OnBoxBeginOverlap);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &ACTSortable::OnBoxEndOverlap);
}

ACTGameModeLevel* ACTSortable::GetGameMode() const
{
	return GameModeLevel;
}




void ACTSortable::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void ACTSortable::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void ACTSortable::BeginPlay()
{
	Super::BeginPlay();

	GameModeLevel = static_cast<ACTGameModeLevel*>(GetWorld()->GetAuthGameMode());

	
}

void ACTSortable::Interact(ACTSortable* OtherSortable)
{
	OtherSortable->Interact(this);
}

