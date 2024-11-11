
#include "CTGameModeLevel.h"

#include "Catender02/Objects/CTBuildingHQ.h"
#include "Kismet/GameplayStatics.h"

ACTGameModeLevel::ACTGameModeLevel()
{
	SortingLayerDataComponent = CreateDefaultSubobject<UCTSortingLayerDataComponent>(TEXT("Sorting Layer Data Component"));
	AddOwnedComponent(SortingLayerDataComponent);

	WorldResourceComponent = CreateDefaultSubobject<UCTWorldResourceComponent>(TEXT("World Resource Component"));
	AddOwnedComponent(WorldResourceComponent);

	WorldBuildableComponent = CreateDefaultSubobject<UCTWorldBuildableComponent>(TEXT("World Buildable Component"));
	AddOwnedComponent(WorldBuildableComponent);

	WorldBuildingVisibilityComponent = CreateDefaultSubobject<UCTWorldBuildingVisibilityComponent>(TEXT("World Building Visibility Component"));
	AddOwnedComponent(WorldBuildingVisibilityComponent);

	WorldDayTimeComponent = CreateDefaultSubobject<UCTWorldDayTimeComponent>(TEXT("World Day Time Component"));
	AddOwnedComponent(WorldDayTimeComponent);
}

void ACTGameModeLevel::BeginPlay()
{
	Super::BeginPlay();

	BuildingHQ = Cast<ACTBuildingHQ>(UGameplayStatics::GetActorOfClass(this, ACTBuildingHQ::StaticClass()));
}

ACTBuildingHQ* ACTGameModeLevel::GetBuildingHQ()
{
	return BuildingHQ;
}

UCTSortingLayerDataComponent* ACTGameModeLevel::GetSortingLayerDataComponent()
{
	return SortingLayerDataComponent;
}

UCTWorldResourceComponent* ACTGameModeLevel::GetWorldResourceComponent()
{
	return WorldResourceComponent;
}

UCTWorldBuildableComponent* ACTGameModeLevel::GetWorldBuildableComponent()
{
	return WorldBuildableComponent;
}

UCTWorldDayTimeComponent* ACTGameModeLevel::GetWorldDayTimeComponent()
{
	return WorldDayTimeComponent;
}
