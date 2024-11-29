#include "BKManager.h"
#include "BKManager.h"
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

	PrepTile();
}

void ABKManager::PrepTile()
{
	GenerateTile(YellowBrick);
}

void ABKManager::GenerateTile(TSubclassOf<ABKBrick> Brick)
{
	FVector Position = SpawnPos;

	for (int i = 0; i <= BrickPerLine; i++)
	{
		if (i == 0) continue;

		Spawn(Brick, Position + FVector(0, 105 * i, 0));
	}

	Position += FVector(55, 0, 0);

	for (int i = 0; i <= BrickPerLine; i++)
	{
		Spawn(Brick, Position + FVector(0, 105 * i, 0));
	}
}

void ABKManager::Spawn(TSubclassOf<ABKBrick> Brick, FVector Position)
{
	AActor* ActorSpawned = GetWorld()->SpawnActor<ABKBrick>(Brick, Position, FRotator(0, 0, 0));
		ObjectCollision.Add(ActorSpawned);
}

void ABKManager::EndGame()
{

}

void ABKManager::RemoveFromObjectCollision(ABKBrick* Brick)
{
	if (!ObjectCollision.Contains(Brick)) return;

	ObjectCollision.Remove(Brick);
	CheckForBrickLeft();
}

void ABKManager::CheckForBrickLeft()
{
	for (AActor* Actor : ObjectCollision)
	{
		if (Actor && Actor->IsA<ABKBrick>()) 
		{
			return;
		}
	}
	
	if (!Phase2)
	{
		GenerateTile(YellowBrick);
		Phase2 = true;
	}
	else
	{
		EndGame();
	}
}