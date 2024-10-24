
#pragma once

#include "CoreMinimal.h"
#include "Catender02/CTSortable.h"
#include "CTPickable.generated.h"



UCLASS()
class CATENDER02_API ACTPickable : public ACTSortable
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	float DestructionTimer = 1;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	TArray<FResource> Resources; 

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	USoundBase* PickupSound = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	USoundBase* DropSound = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess=true))
    TArray<TEnumAsByte<ECollisionChannel>> PickupChannels;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	UCapsuleComponent* PickupComponent = nullptr;
	
	UFUNCTION()
	void PlayPickupSound() const;
	UFUNCTION()
	void PlayDropSound() const;
	UFUNCTION()
	void PlayPickAnimation() const;
	UFUNCTION()
	void DisableCollision() const;
	UFUNCTION()
	void ApplyResources() const;

	UFUNCTION()
	void DestroyPickup();
	
public:
	ACTPickable();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	virtual void OnCapsuleBeginOverlap
	(
		UPrimitiveComponent* OverlappedComp, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult& SweepResult
	);
};
