

#include "CTBuildingActivationBox.h"

#include "Catender02/Objects/CTBuilding.h"


void ACTBuildingActivationBox::CalculateGrowSpeed()
{
	int NumOverlappingDestroyables = OverlappingDestroyables.Num();

	if(NumOverlappingDestroyables <= 0) CurrentBuildingVisibilityGrowSpeed = MaxBuildingVisibilityGrowSpeed;

	CurrentBuildingVisibilityGrowSpeed -= BuildingVisibilitySlowDown;

	if(CurrentBuildingVisibilityGrowSpeed < 0) CurrentBuildingVisibilityGrowSpeed = 0;
}

void ACTBuildingActivationBox::GrowBox()
{
	FVector NewBoxExtent = FVector(
		GetBoxBuildingVisibilityComponent()->GetUnscaledBoxExtent().X + CurrentBuildingVisibilityGrowSpeed,
		GetBoxBuildingVisibilityComponent()->GetUnscaledBoxExtent().Y,
		GetBoxBuildingVisibilityComponent()->GetUnscaledBoxExtent().Z
	);
	
	GetBoxBuildingVisibilityComponent()->SetBoxExtent(NewBoxExtent, true);

	float CurrentGrowExtentX = GetBoxBuildingVisibilityComponent()->GetUnscaledBoxExtent().X - InitialXBoxExtent;

	CurrentGrowExtentX *= GrowDirection == Right ? 1 : -1;
	
	FVector NewRelativeLocation = FVector(
		InitialRelativeLocation.X + (CurrentGrowExtentX),
		InitialRelativeLocation.Y,
		InitialRelativeLocation.Z
	);

	GetBoxBuildingVisibilityComponent()->SetRelativeLocation(NewRelativeLocation);
}

ACTBuildingActivationBox::ACTBuildingActivationBox()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxBuildingVisibilityComponent = CreateDefaultSubobject<UBoxComponent>("Box Building Visibility");
	BoxBuildingVisibilityComponent->SetupAttachment(GetRootComponent());
}

UBoxComponent* ACTBuildingActivationBox::GetBoxBuildingVisibilityComponent()
{
	return BoxBuildingVisibilityComponent;
}

void ACTBuildingActivationBox::BeginPlay()
{
	Super::BeginPlay();
	
	GetBoxBuildingVisibilityComponent()->OnComponentBeginOverlap.AddDynamic(
		this,
		&ACTBuildingActivationBox::OnBoxBeginOverlapInteraction
	);

	GetBoxBuildingVisibilityComponent()->OnComponentEndOverlap.AddDynamic(
		this,
		&ACTBuildingActivationBox::OnBoxEndOverlapInteraction
	);

	OnOverlappingDestroyablesChanged.AddDynamic(this, &ACTBuildingActivationBox::OverlappingDestroyablesChanged);

	InitialRelativeLocation = GetBoxBuildingVisibilityComponent()->GetRelativeLocation();
	InitialXBoxExtent = GetBoxBuildingVisibilityComponent()->GetScaledBoxExtent().X;

	OverlappingDestroyablesChanged();
}

void ACTBuildingActivationBox::OnBoxBeginOverlapInteraction(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor) return;	
	if (ACTBuilding* Building = Cast<ACTBuilding>(OtherActor))
	{
		Building->SetActive(true);
	}
	if (ACTDestroyable* Destroyable = Cast<ACTDestroyable>(OtherActor))
	{
		if(Destroyable->GetBuildingComponent()->GetBuildingState() == Invisible) return;
		Destroyable->GetInteractionBoxComponent()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		OverlappingDestroyables.Add(Destroyable);
		OnOverlappingDestroyablesChanged.Broadcast();
	}
}

void ACTBuildingActivationBox::OnBoxEndOverlapInteraction(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (ACTDestroyable* Destroyable = Cast<ACTDestroyable>(OtherActor))
	{
		OverlappingDestroyables.Remove(Destroyable);
		OnOverlappingDestroyablesChanged.Broadcast();
	}
}

void ACTBuildingActivationBox::OverlappingDestroyablesChanged()
{
	
}

void ACTBuildingActivationBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CalculateGrowSpeed();
	GrowBox();
}

