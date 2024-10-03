#include "CTInteractable.h"

#include "Catender02/Character/CTPlayerCharacter.h"
#include "Components/CapsuleComponent.h"

ACTInteractable::ACTInteractable()
{
	InteractionBoxComponent = CreateDefaultSubobject<UBoxComponent>("Box Interaction");
	InteractionBoxComponent->SetupAttachment(GetRootComponent());
	
	GetCapsuleComponent()->OnComponentBeginOverlap.Clear();
	GetCapsuleComponent()->OnComponentEndOverlap.Clear();
	
	InteractionBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ACTInteractable::OnBoxBeginOverlapInteraction);
	InteractionBoxComponent->OnComponentEndOverlap.AddDynamic(this, &ACTInteractable::OnBoxEndOverlapInteraction);
}

/**
 * Creates a dynamic material instance for the sprite component if it exists.
 *
 * This method checks if the sprite component is valid and retrieves its current material.
 * If the material is valid, a dynamic material instance is created and applied to the sprite component.
 * The dynamic material instance is stored in the `MaterialInstanceDynamic` member variable.
 */
void ACTInteractable::CreateDynamicMaterialForSprite()
{
	if (!GetSprite()) return;
	
	UMaterialInterface* MaterialInterface = GetSprite()->GetMaterial(0);
	if (!MaterialInterface) return;
		
	// Create a dynamic material instance
	UMaterialInstanceDynamic* DynamicMaterialInstance = UMaterialInstanceDynamic::Create(MaterialInterface, this);

	if (!DynamicMaterialInstance) return;
			
	// Assign the dynamic material instance to the sprite component
	GetSprite()->SetMaterial(0, DynamicMaterialInstance);

	MaterialInstanceDynamic = DynamicMaterialInstance;
}

void ACTInteractable::BeginPlay()
{
	Super::BeginPlay();

	CreateDynamicMaterialForSprite();
}

bool ACTInteractable::CanInteract() const
{
	return true;
}


UBoxComponent* ACTInteractable::GetInteractionBoxComponent() const
{
	return InteractionBoxComponent;
}

void ACTInteractable::SetActive(const bool Active)
{
	GetInteractionBoxComponent()->SetCollisionEnabled(Active == true ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
}

/**
 * Toggles the highlight effect on the interactive object.
 *
 * Adjusts the "HighlightMultiplier" parameter in the material instance dynamic to either enable or disable the highlight effect.
 *
 * @param IsHighlighted A boolean indicating whether the object should be highlighted or not.
 * If true, the highlight effect is activated; if false, it is deactivated.
 */
void ACTInteractable::Highlight(const bool IsHighlighted) const
{
	if(!MaterialInstanceDynamic) return;
	
	if (IsHighlighted)
	{
		MaterialInstanceDynamic->SetScalarParameterValue("HighlightMultiplier", 0.05f);
	}
	else
	{
		MaterialInstanceDynamic->SetScalarParameterValue("HighlightMultiplier", 0);
	}
}

/**
 * Handles the event when another component begins to overlap with the interaction box component.
 *
 * @param OverlappedComp Pointer to the component that was overlapped.
 * @param OtherActor Pointer to the other actor involved in the overlap.
 * @param OtherComp Pointer to the other component involved in the overlap.
 * @param OtherBodyIndex Index of the other body that is involved in the overlap.
 * @param bFromSweep Indicates if this overlap was the result of a sweep test.
 * @param SweepResult Details about the hit result of the sweep test, if the overlap was from a sweep.
 */
void ACTInteractable::OnBoxBeginOverlapInteraction(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACTPlayerCharacter* PlayerCharacter = Cast<ACTPlayerCharacter>(OtherActor);

	if (!PlayerCharacter) return;

	PlayerCharacter->GetPlayerInteractionComponent()->AddToOverlappingInteractables(this);
}

/**
 * Handles the event when another component ends overlap with the interaction box component.
 *
 * @param OverlappedComp Pointer to the component that was overlapped.
 * @param OtherActor Pointer to the other actor involved in the overlap.
 * @param OtherComp Pointer to the other component involved in the overlap.
 * @param OtherBodyIndex Index of the other body that is involved in the overlap.
 */
void ACTInteractable::OnBoxEndOverlapInteraction(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ACTPlayerCharacter* PlayerCharacter = Cast<ACTPlayerCharacter>(OtherActor);

	if (!PlayerCharacter) return;

	PlayerCharacter->GetPlayerInteractionComponent()->RemoveFromOverlappingInteractables(this);
}

void ACTInteractable::Interact(ACTSortable* OtherSortable)
{
	
}
