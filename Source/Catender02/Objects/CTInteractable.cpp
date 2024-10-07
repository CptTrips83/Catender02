#include "CTInteractable.h"

#include "Catender02/Character/CTPlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

void ACTInteractable::UpdateInteractionCollision(const bool CollisionEnabled)
{
	GetInteractionBoxComponent()->SetCollisionEnabled(CollisionEnabled ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
}

ACTInteractable::ACTInteractable()
{
	InteractionBoxComponent = CreateDefaultSubobject<UBoxComponent>("Box Interaction");
	InteractionBoxComponent->SetupAttachment(GetRootComponent());

	InteractionWidget = CreateDefaultSubobject<UCTWidgetComponent>("Widget Interaction");
	InteractionWidget->SetupAttachment(GetRootComponent());
	
	GetCapsuleComponent()->OnComponentBeginOverlap.Clear();
	GetCapsuleComponent()->OnComponentEndOverlap.Clear();
	
	InteractionBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ACTInteractable::OnBoxBeginOverlapInteraction);
	InteractionBoxComponent->OnComponentEndOverlap.AddDynamic(this, &ACTInteractable::OnBoxEndOverlapInteraction);
}

void ACTInteractable::CreateDynamicMaterialForSprite()
{
	if (!GetSprite()) return;
	
	UMaterialInterface* MaterialInterface = GetSprite()->GetMaterial(0);
	if (!MaterialInterface) return;

	if(MaterialInterface->IsA(UMaterialInstanceDynamic::StaticClass())) return;
	
	// Create a dynamic material instance
	UMaterialInstanceDynamic* DynamicMaterialInstance = UMaterialInstanceDynamic::Create(MaterialInterface, this);

	if (!DynamicMaterialInstance) return;
			
	// Assign the dynamic material instance to the sprite component
	GetSprite()->SetMaterial(0, DynamicMaterialInstance);
}




void ACTInteractable::BeginPlay()
{
	Super::BeginPlay();

	CreateDynamicMaterialForSprite();
	
	//ToggleInteractionWidget(false);
}

bool ACTInteractable::CanInteract() const
{
	return true;
}

void ACTInteractable::ToggleInteractionWidget(const bool IsActive)
{
	UWidgetComponent* Widget = GetInteractionWidget();

	if(!Widget->GetWidgetClass())
	{
		Widget->SetVisibility(false);
		return;
	}
	
	Widget->SetVisibility(IsActive);
}


UBoxComponent* ACTInteractable::GetInteractionBoxComponent() const
{
	return InteractionBoxComponent;
}

UCTWidgetComponent* ACTInteractable::GetInteractionWidget() const
{
	return InteractionWidget;
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
void ACTInteractable::Highlight(const bool IsHighlighted) 
{
	UMaterialInterface* MaterialInterface = GetSprite()->GetMaterial(0);

	UMaterialInstanceDynamic* MaterialInstanceDynamic = Cast<UMaterialInstanceDynamic>(MaterialInterface);
		
	if(!MaterialInstanceDynamic) return;
	
	if (IsHighlighted)
	{
		MaterialInstanceDynamic->SetScalarParameterValue("HighlightMultiplier", 0.05f);
	}
	else
	{
		MaterialInstanceDynamic->SetScalarParameterValue("HighlightMultiplier", 0);
	}

	float Multiplier = 0;
	
	MaterialInstanceDynamic->GetScalarParameterValue(FHashedMaterialParameterInfo ("HighlightMultiplier"), Multiplier);
	FString DebugMessage = UKismetStringLibrary::Concat_StrStr("CanBeBuild(): ", FString::SanitizeFloat(Multiplier));
	
	UKismetSystemLibrary::PrintString(this, DebugMessage);
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
