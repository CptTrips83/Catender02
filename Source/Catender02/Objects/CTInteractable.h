#pragma once

#include "CoreMinimal.h"
#include "./Catender02/CTSortable.h"
#include "Catender02/UI/CTUserWidgetMain.h"
#include "Catender02/UI/CTWidgetComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/BoxComponent.h"
#include "CTInteractable.generated.h"


UCLASS()
class CATENDER02_API ACTInteractable : public ACTSortable
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* InteractionBoxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCTWidgetComponent* InteractionWidget;

	
protected:
	virtual void UpdateInteractionCollision(bool CollisionEnabled);
		
public:
	
	ACTInteractable();
	
	void CreateDynamicMaterialForSprite();
	virtual void BeginPlay() override;
	virtual bool CanInteract() const;

	UFUNCTION(BlueprintCallable)
	virtual void ToggleInteractionWidget(bool IsActive);
	
	UFUNCTION(BlueprintCallable)
	UBoxComponent* GetInteractionBoxComponent() const;

	UFUNCTION(BlueprintPure)
	UCTWidgetComponent* GetInteractionWidget() const;
	
	UFUNCTION(BlueprintCallable)
	virtual void SetActive(bool Active);

	UFUNCTION(BlueprintCallable)
	virtual void Highlight(bool IsHighlighted);
	
	UFUNCTION()
	virtual void OnBoxBeginOverlapInteraction
	(
		UPrimitiveComponent* OverlappedComp, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult& SweepResult
	);

	UFUNCTION()
	virtual void OnBoxEndOverlapInteraction 
	(
		UPrimitiveComponent* OverlappedComp, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex
	);

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	virtual void Interact(ACTSortable* OtherSortable) override;
};
