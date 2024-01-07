// Fill out your copyright notice in the Description page of Project Settings.


#include "spawner.h"
#include "OverlapRespond.h"
#include "OverlappingObjects.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "PawnBase.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values
Aspawner::Aspawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	meshFloor = CreateDefaultSubobject<UStaticMeshComponent>(FName("meshf"));
	arrow = CreateDefaultSubobject<UArrowComponent>(FName("arrow"));
	boxCol = CreateDefaultSubobject<UBoxComponent>(FName("collisionc"));
	scene = CreateDefaultSubobject<USceneComponent>(FName("rootScene"));

	SetRootComponent(scene);
	boxCol->SetupAttachment(RootComponent);
	arrow->SetupAttachment(RootComponent);
	meshFloor->SetupAttachment(RootComponent);
	
}
FTimerHandle spawnTimer;

void Aspawner::BeginPlay()
{
	Super::BeginPlay();
	boxCol->OnComponentBeginOverlap.AddDynamic(this, &Aspawner::overlap);
	boxCol->OnComponentEndOverlap.AddDynamic(this, &Aspawner::EndOverlap);
	//UKismetSystemLibrary::K2_SetTimer(this, "SpawnEnemy", 2.0f, true);
	GetWorld()->GetTimerManager().SetTimer(spawnTimer, this, &Aspawner::SpawnEnemy, 1.0f, true, 0.1f);
}

void Aspawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FActorSpawnParameters params = FActorSpawnParameters::FActorSpawnParameters();
int rangeX;
int rangeY;

FVector currentPlayerLoc;

void Aspawner::SpawnEnemy() {
	rangeX = UKismetMathLibrary::RandomIntegerInRange(800,1250);
	rangeY = UKismetMathLibrary::RandomIntegerInRange(-250, 250);

	if (UKismetMathLibrary::Abs_Int(rangeY) < 50) {
		if (rangeY < 0) {
			rangeY = -150;
		}
		else {
			rangeY = 150;
		}
	}
	if (Cast<APawnBase>(UGameplayStatics::GetPlayerPawn(this, 0))) {
		currentPlayerLoc = Cast<APawnBase>(UGameplayStatics::GetPlayerPawn(this, 0))->getLoc();
		currentPlayerLoc.X += rangeX;
		currentPlayerLoc.Y += rangeY;
		GetWorld()->SpawnActor<AOverlappingObjects>(spawnEnemyClass, currentPlayerLoc, FRotator(0), params);
	}
	else {
		GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Red, FString("failed"), true);

	}
}
void Aspawner::spawn()
{
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	GetWorld()->SpawnActor<Aspawner>(spawnclass, arrow->GetComponentLocation(),FRotator(0), params);
	GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Red, FString("spawner spawn!!"), true);

}
void Aspawner::overlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {

	GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Red, FString("OVERLAPPED!!"), true);
};

void Aspawner::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	if (Cast<APawnBase>(OtherActor)) {
		boxCol->DestroyComponent();
		Destroy();
		spawn();
	}
};

