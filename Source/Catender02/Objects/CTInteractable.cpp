#include "CTInteractable.h"

#include "Catender02/Character/CTPlayerCharacter.h"
#include "Components/CapsuleComponent.h"

ACTInteractable::ACTInteractable()
{
	BoxComponentInteraction = CreateDefaultSubobject<UBoxComponent>("Box Interaction");
	BoxComponentInteraction->SetupAttachment(GetRootComponent());
	
	GetCapsuleComponent()->OnComponentBeginOverlap.Clear();
	GetCapsuleComponent()->OnComponentEndOverlap.Clear();
	
	BoxComponentInteraction->OnComponentBeginOverlap.AddDynamic(this, &ACTInteractable::OnBoxBeginOverlapInteraction);
	BoxComponentInteraction->OnComponentEndOverlap.AddDynamic(this, &ACTInteractable::OnBoxEndOverlapInteraction);
}

UBoxComponent* ACTInteractable::GetBoxComponentInteraction() const
{
	return BoxComponentInteraction;
}

void ACTInteractable::SetActive(const bool Active)
{
	GetBoxComponentInteraction()->SetCollisionEnabled(Active == true ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
}

void ACTInteractable::OnBoxBeginOverlapInteraction(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACTPlayerCharacter* PlayerCharacter = Cast<ACTPlayerCharacter>(OtherActor);

	if (!PlayerCharacter) return;

	PlayerCharacter->GetPlayerInteractionComponent()->AddToOverlappingInteractables(this);
}

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
