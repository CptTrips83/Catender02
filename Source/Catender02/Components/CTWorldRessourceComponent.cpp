
#include "CTWorldResourceComponent.h"

UCTWorldResourceComponent::UCTWorldResourceComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	Resources.Add(FResourceData(FResource(EResourceType::Gold, 0), false));
	Resources.Add(FResourceData(FResource(EResourceType::Meat, 0), false));
	Resources.Add(FResourceData(FResource(EResourceType::Wood, 0), true));
	Resources.Add(FResourceData(FResource(EResourceType::Stone, 0), true));
	Resources.Add(FResourceData(FResource(EResourceType::Iron, 0), true));
}


void UCTWorldResourceComponent::BeginPlay()
{
	Super::BeginPlay();
}

/**
 * Retrieves the data of a specified resource type.
 *
 * @param ResourceType The type of the resource whose data is to be retrieved.
 * @return A pointer to the FResourceData of the specified resource type. Returns nullptr if the resource type is not found.
 */
FResourceData* UCTWorldResourceComponent::GetResourceData(const EResourceType ResourceType)
{
	for (FResourceData& ResourceData : Resources)
	{
		if(ResourceData.Resource.ResourceType == ResourceType)
		{
			return &ResourceData;
		}
	}
	return nullptr;
}


void UCTWorldResourceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

/**
 * Retrieves the amount of a specified resource type currently available.
 *
 * @param ResourceType The type of resource whose amount is to be retrieved.
 * @return The amount of the specified resource type available. Returns 0 if the resource type is not found.
 */
int UCTWorldResourceComponent::GetResourceAmount(const EResourceType ResourceType)
{
	const FResourceData* ResourceData = GetResourceData(ResourceType);

	if (!ResourceData) return 0;	
	
	return ResourceData->Resource.Amount;
}

/**
 * Attempts to add a specified amount of a given resource type.
 *
 * @param ResourceType The type of resource to add.
 * @param Amount The amount of the resource to add.
 * @return The amount that could not be added due to capacity constraints.
 */
int UCTWorldResourceComponent::TryAddResourceAmount(const EResourceType ResourceType, const int Amount)
{
	// Erhalte die Daten der angeforderten Ressource
	FResourceData* ResourceData = GetResourceData(ResourceType); 
	if (!ResourceData)
	{
		UE_LOG(LogTemp, Warning, TEXT("Resource data not found."));
		return 0;
	}

	// Überprüfe, ob die hinzuzufügende Menge negativ ist
	if (Amount < 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Amount is negative."));
		return 0;
	}

	int ReturningAmount = 0; // Variable für die Menge, die nach dem Hinzufügen verbleibt
	int MaxResourceAmount = GetMaxResources(); // Maximal erlaubte Gesamtmenge an Ressourcen
	int CurrentResourceAmount = GetAmountAllResources(); // Aktuelle Gesamtmenge aller Ressourcen

	// Überprüfe die Konsistenz der Gesamtsummen
	if (CurrentResourceAmount > MaxResourceAmount)
	{
		UE_LOG(LogTemp, Warning, TEXT("Current resource amount exceeds maximum allowed resources."));
		return 0;
	}

	int RemainingResourceAmount = MaxResourceAmount - CurrentResourceAmount; // Der verfügbare Platz zur Speicherung von Ressourcen

	// Überprüfe, ob die hinzuzufügende Menge den verbleibenden Platz übersteigt
	if (Amount > RemainingResourceAmount)
	{
		ReturningAmount = Amount - RemainingResourceAmount; // Setze die verbleibende Menge, die nicht hinzugefügt werden konnte
		ResourceData->Resource.Amount += RemainingResourceAmount; // Fülle den verfügbaren Platz vollständig aus
	}
	else
	{
		ResourceData->Resource.Amount += Amount; // Ansonsten füge die vollständige angeforderte Menge hinzu
	}

	// Überprüfen, dass die Ressourcensumme nicht negativ wird
	if (ResourceData->Resource.Amount < 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Resulting resource amount is out of bounds."));
		ResourceData->Resource.Amount = 0;
		return 0;
	}

	return ReturningAmount; // Gebe die Menge zurück, die nicht hinzugefügt werden konnte
}

/**
 * Attempts to subtract a specified amount of a given resource type.
 *
 * @param ResourceType The type of resource to subtract.
 * @param Amount The amount of the resource to subtract.
 * @return true if the resource amount was successfully subtracted; false otherwise.
 */
bool UCTWorldResourceComponent::TrySubtractResourceAmount(const EResourceType ResourceType, int Amount)
{
	FResourceData* ResourceData = GetResourceData(ResourceType);

	if (!ResourceData)
	{
		UE_LOG(LogTemp, Warning, TEXT("Resource data not found."));
		return false;
	}

	// Überprüfe, ob die hinzuzufügende Menge negativ ist
	if (Amount < 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Amount is negative."));
		return false;
	}

	if (ResourceData->Resource.Amount < Amount)
	{
		return false;
	}

	ResourceData->Resource.Amount -= Amount;
	
	return true;
}

/**
 * Determines if a specified resource type is unlocked.
 *
 * @param ResourceType The type of the resource to check for being unlocked.
 * @return True if the specified resource type is unlocked, false otherwise.
 */
bool UCTWorldResourceComponent::IsUnlockResource(const EResourceType ResourceType)
{
	const FResourceData* ResourceData = GetResourceData(ResourceType);	
	
	return !ResourceData ? false : ResourceData->IsUnlockResource;;
}

/**
 * Calculates the total amount of all resources, excluding unlock resources.
 *
 * @return The total amount of non-unlock resources.
 */
int UCTWorldResourceComponent::GetAmountAllResources()
{
	int Result = 0;

	for (FResourceData ResourceData : Resources)
	{
		// Amount nicht berücksichtigen wenn IsUnlockResource == true
		if (IsUnlockResource(ResourceData.Resource.ResourceType)) continue;

		Result += ResourceData.Resource.Amount;
	}

	return Result;
}

/**
 * Retrieves the maximum allowable number of resources.
 *
 * @return The maximum number of resources that can be held.
 */
int UCTWorldResourceComponent::GetMaxResources() const
{	
	return MaxResources;
}

