

#include "ACTProjectile.h"


AACTProjectile::AACTProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Collision Sphere"));
	SetRootComponent(CollisionSphereComponent);
	
	ProjectileSpriteComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Projectile Sprite"));
	ProjectileSpriteComponent->SetupAttachment(RootComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovementComponent->UpdatedComponent = RootComponent;

	ProjectileMovementComponent->InitialSpeed = 800.0f;
	ProjectileMovementComponent->MaxSpeed = 800.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = false;
	ProjectileMovementComponent->ProjectileGravityScale = 0.5f;
}

void AACTProjectile::LaunchProjectile(const FVector Target)
{
	TargetLocation = Target;

	ProjectileMovementComponent->Velocity = CalculateLaunchVelocity();

	GetWorld()->GetTimerManager().SetTimer(
		LifeSpanHandle,
		this,
		&AACTProjectile::OnLifeSpanEnded,
		LifeSpan,
		false
	);
}

void AACTProjectile::BeginPlay()
{
	Super::BeginPlay();

	GetCollisionSphereComponent()->OnComponentBeginOverlap.AddDynamic(this, &AACTProjectile::OnProjectileHit);
}

UPrimitiveComponent* AACTProjectile::GetProjectileSpriteComponent() const
{
	return ProjectileSpriteComponent;
}

UProjectileMovementComponent* AACTProjectile::GetProjectileMovementComponent() const
{
	return ProjectileMovementComponent;
}

USphereComponent* AACTProjectile::GetCollisionSphereComponent() const
{
	return CollisionSphereComponent;
}

FVector AACTProjectile::CalculateLaunchVelocity() const
{
	FVector2D TargetLocation2D = FVector2D(TargetLocation.X, TargetLocation.Z);
	
	FVector2D StartLocation = FVector2D(GetActorLocation());
	FVector2D Direction = TargetLocation2D - StartLocation;
    
	// Calculate the distance to the target and normalize direction
	float Distance = Direction.Size();
	Direction.Normalize();

	// Calculate the launch speed (this is a simplified example, adjust as needed)
	float LaunchSpeed = FMath::Sqrt((GetProjectileMovementComponent()->ProjectileGravityScale * Distance) / FMath::Sin(2 * FMath::DegreesToRadians(45.f)));

	return FVector(Direction.X, 0.f, Direction.Y) * LaunchSpeed;
}

void AACTProjectile::OnProjectileHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void AACTProjectile::OnLifeSpanEnded()
{
}

void AACTProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

