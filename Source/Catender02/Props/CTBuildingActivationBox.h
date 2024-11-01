
#pragma once

#include "CoreMinimal.h"
#include "Catender02/Objects/CTDestroyable.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "CTBuildingActivationBox.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE
(
	FOverlappingDestroyablesChanged
);

UCLASS()
class CATENDER02_API ACTBuildingActivationBox : public AActor
{
	GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	UBoxComponent* BoxBuildingVisibilityComponent;

	float CurrentBuildingVisibilityGrowSpeed;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	float BuildingVisibilitySlowDown = 0.0001f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	float MaxBuildingVisibilityGrowSpeed = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess=true))
    TEnumAsByte<ECTDirection> GrowDirection = Right;
	
	TArray<ACTDestroyable*> OverlappingDestroyables;

	FVector InitialRelativeLocation;
	float InitialXBoxExtent;

	void GrowBox();
	
public:
	ACTBuildingActivationBox();

	UFUNCTION(BlueprintPure)
	UBoxComponent* GetBoxBuildingVisibilityComponent();
protected:
	virtual void BeginPlay() override;

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

	UFUNCTION()
	virtual void OverlappingDestroyablesChanged();
	
public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintAssignable)
	FOverlappingDestroyablesChanged OnOverlappingDestroyablesChanged;
};
