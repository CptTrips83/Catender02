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

UBoxComponent* ACTInteractable::GetInteractionBoxComponent() const
{
	return InteractionBoxComponent;
}

void ACTInteractable::SetActive(const bool Active)
{
	GetInteractionBoxComponent()->SetCollisionEnabled(Active == true ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
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
