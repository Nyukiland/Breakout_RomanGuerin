#include "BKManager.h"
#include "BKBrick.h"
#include "Kismet/GameplayStatics.h"

ABKManager* ABKManager::Instance = nullptr;

ABKManager* ABKManager::Get()
{
	if (Instance != nullptr)
	{
		return Instance;
	}

	UWorld* World = GEngine->GetWorldFromContextObjectChecked(GWorld);
	if (World)
	{
		Instance = Cast<ABKManager>(UGameplayStatics::GetActorOfClass(World, ABKManager::StaticClass()));
	}

	if (Instance == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("ABKManager::Get() - No ABKManager found in the current world!"));
	}

	return Instance;
}

void ABKManager::BeginPlay()
{
	Super::BeginPlay();

	Instance = this;

	GenerateTile(YellowBrick);
}

void ABKManager::GenerateTile(ABKBrick* Brick)
{
	FVector Position = Brick->GetActorLocation();
	TSubclassOf<ABKBrick> BrickClass = Brick->GetClass();

	for (int i = 0; i <= BrickPerLine; i++)
	{
		if (i == 0) continue;

		Spawn(BrickClass, Position + FVector(0, 105 * i, 0));
	}

	Position += FVector(55, 0, 0);

	for (int i = 0; i <= BrickPerLine; i++)
	{
		Spawn(BrickClass, Position + FVector(0, 105 * i, 0));
	}
}

void ABKManager::Spawn(TSubclassOf<ABKBrick> Brick, FVector Position)
{
	AActor* ActorSpawned = GetWorld()->SpawnActor<ABKBrick>(Brick, Position, FRotator(0, 0, 0));
		ObjectCollision.Add(ActorSpawned);
}