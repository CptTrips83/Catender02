
#include "CTWidgetComponent.h"

#include "CTUserWidgetMain.h"
#include "Catender02/Objects/CTInteractable.h"


UCTWidgetComponent::UCTWidgetComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCTWidgetComponent::BeginPlay()
{
	Super::BeginPlay();
	
    UCTUserWidgetMain* MainWidget = Cast<UCTUserWidgetMain>(GetWidget());
	if (!MainWidget) return;
	ACTInteractable* Interactable = Cast<ACTInteractable>(GetOwner());
	if (!Interactable) return;	
	MainWidget->SetOwningInteractable(Interactable);
}

void UCTWidgetComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                       FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

