
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

int UCTWorldResourceComponent::GetResourceAmount(const EResourceType ResourceType)
{
	const FResourceData* ResourceData = GetResourceData(ResourceType);

	if (!ResourceData) return 0;	
	
	return ResourceData->Resource.Amount;
}


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

	const int OldAmount = ResourceData->Resource.Amount;
	int ReturningAmount = 0; // Variable für die Menge, die nach dem Hinzufügen verbleibt
	const int MaxResourceAmount = GetMaxResources(); // Maximal erlaubte Gesamtmenge an Ressourcen
	const int CurrentResourceAmount = GetAmountAllResources(); // Aktuelle Gesamtmenge aller Ressourcen

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

	const int NewAmount = ResourceData->Resource.Amount;

	OnResourceAmountChanged.Broadcast(ResourceType, OldAmount, NewAmount);
	
	return ReturningAmount; // Gebe die Menge zurück, die nicht hinzugefügt werden konnte
}

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

	const int OldAmount = ResourceData->Resource.Amount;
	
	if (ResourceData->Resource.Amount < Amount)
	{
		return false;
	}

	ResourceData->Resource.Amount -= Amount;

	const int NewAmount = ResourceData->Resource.Amount;

	OnResourceAmountChanged.Broadcast(ResourceType, OldAmount, NewAmount);
	
	return true;
}

void UCTWorldResourceComponent::SetMaxResources(int NewAmount)
{
	MaxResources = FMath::Clamp(NewAmount, 0, 100);
}


bool UCTWorldResourceComponent::IsUnlockResource(const EResourceType ResourceType)
{
	const FResourceData* ResourceData = GetResourceData(ResourceType);	
	
	return !ResourceData ? false : ResourceData->IsUnlockResource;;
}


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


int UCTWorldResourceComponent::GetMaxResources() const
{	
	return MaxResources;
}


bool UCTWorldResourceComponent::CheckResource(EResourceType Resource, int NeededAmount)
{
	if (const FResourceData* ResourceData = GetResourceData(Resource))
	{
		if(ResourceData->IsUnlockResource)
		{
			return ResourceData->Resource.Amount >= 1;
		}		
		return ResourceData->Resource.Amount >= NeededAmount;
	}
	return false;
}

