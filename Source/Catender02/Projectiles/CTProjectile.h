
#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookComponent.h"
#include "Catender02/CTSortable.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "CTProjectile.generated.h"

UCLASS()
class CATENDER02_API ACTProjectile : public ACTSortable
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile", meta = (AllowPrivateAccess = true))
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY()
	FVector TargetLocation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile", meta = (AllowPrivateAccess = true))
	float LaunchSpeedModifier = 150.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile", meta = (AllowPrivateAccess = true, MinValue = 0.f, MaxValue = 0.1f, MaxLength = 2f))
	float LaunchAngleModifier = 0.15f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile", meta = (AllowPrivateAccess = true))
	float Damage = 1.f;

public:
	ACTProjectile();	

	UFUNCTION(BlueprintCallable, Category = "Projectile")
	virtual void LaunchProjectile(FVector Target, float LaunchSpeedMod = 150.f, float LaunchAngleMod = 0.15f);

	UFUNCTION(BlueprintPure, Category = "Projectile")
	virtual float GetDamage() const;
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintPure, Category = "Projectile")
	virtual UProjectileMovementComponent* GetProjectileMovementComponent() const;

	UFUNCTION()
	virtual FVector CalculateLaunchVelocity() const;
	
	UFUNCTION()	
	virtual void OnProjectileHit(UPrimitiveComponent* OverlappedComp, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult& SweepResult);
public:
	virtual void Tick(float DeltaTime) override;
};
