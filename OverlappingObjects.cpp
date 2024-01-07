// Fill out your copyright notice in the Description page of Project Settings.


#include "OverlappingObjects.h"
//#include "Components/ShapeComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Sound/SoundBase.h"
#include "Components/SceneComponent.h"
#include "PawnBase.h"
#include "Kismet/KismetSystemLibrary.h"



// Sets default values
AOverlappingObjects::AOverlappingObjects()
{
	PrimaryActorTick.bCanEverTick = true;
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("mesh3d"));
	collisionSimple = CreateDefaultSubobject<USphereComponent>(FName("collision"));
	scene = CreateDefaultSubobject<USceneComponent>(FName("scenecomp"));
	SetRootComponent(scene);
	collisionSimple->SetupAttachment(GetRootComponent());
	mesh->SetupAttachment(RootComponent);
}

void AOverlappingObjects::BeginPlay()
{
	FTimerHandle spawnTimer2;

	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(spawnTimer2, this, &AOverlappingObjects::autoKill, 12.0f, false);

	//collisionSimple->OnComponentBeginOverlap.AddDynamic(this, &AOverlappingObjects::Overlap);
	//UGameplayStatics::GetAllActorsOfClass(this, pawnClass, pawns);
}
void AOverlappingObjects::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//AddActorLocalOffset(-1* speedConstantforMoving* GetActorForwardVector());
	//AddActorLocalOffset(-1*GetActorForwardVector()*10);
}
void AOverlappingObjects::Interact(){
	//UGameplayStatics::PlaySound2D(this, sound);
	//UGameplayStatics::SpawnEmitterAttached(effect, scene, FName("scene"), GetActorLocation(), GetActorRotation());
}

void AOverlappingObjects::autoKill() {
	GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Red, "asd");
	Destroy();
}