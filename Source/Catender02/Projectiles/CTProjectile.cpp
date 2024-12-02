

#include "CTProjectile.h"

#include "Components/CapsuleComponent.h"


ACTProjectile::ACTProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovementComponent->UpdatedComponent = RootComponent;

	ProjectileMovementComponent->InitialSpeed = 800.0f;
	ProjectileMovementComponent->MaxSpeed = 800.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = false;
	ProjectileMovementComponent->ProjectileGravityScale = 0.5f;
}

void ACTProjectile::LaunchProjectile(const FVector Target, float LaunchSpeedMod, float LaunchAngleMod)
{
	TargetLocation = Target;
	LaunchSpeedModifier = LaunchSpeedMod;
	LaunchAngleModifier = LaunchAngleMod;

	ProjectileMovementComponent->Velocity = CalculateLaunchVelocity();
}

float ACTProjectile::GetDamage() const
{
	return Damage;
}

void ACTProjectile::BeginPlay()
{
	Super::BeginPlay();

    GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ACTProjectile::OnProjectileHit);
}


UProjectileMovementComponent* ACTProjectile::GetProjectileMovementComponent() const
{
	return ProjectileMovementComponent;
}


FVector ACTProjectile::CalculateLaunchVelocity() const
{
	FVector2D TargetLocation2D = FVector2D(TargetLocation.X, TargetLocation.Z);
	
	FVector2D StartLocation = FVector2D(GetActorLocation().X, GetActorLocation().Z);
	FVector2D Direction = TargetLocation2D - StartLocation;
	
	// Calculate the distance to the target and normalize direction
	float Distance = Direction.Size();
	Direction.Y += Distance * 0.15f;
	Direction = Direction.GetSafeNormal();

	// Calculate the launch speed (this is a simplified example, adjust as needed)
	float LaunchSpeed = FMath::Sqrt((GetProjectileMovementComponent()->ProjectileGravityScale * Distance) / FMath::Sin(2 * FMath::DegreesToRadians(45.f)));

	return FVector(Direction.X, 0.f, Direction.Y) * (LaunchSpeed * LaunchSpeedModifier);
}

void ACTProjectile::OnProjectileHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void ACTProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

