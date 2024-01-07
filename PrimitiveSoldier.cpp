// Fill out your copyright notice in the Description page of Project Settings.


#include "PrimitiveSoldier.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"
#include "Particles/ParticleSystem.h"
#include "Weapon.h"

// Sets default values
APrimitiveSoldier::APrimitiveSoldier()
{
	PrimaryActorTick.bCanEverTick = true;
	charmesh =CreateDefaultSubobject<UStaticMeshComponent>(FName("meshforSoldier"));
	spawnSoundC = CreateDefaultSubobject<UAudioComponent>(FName("SpawnSound"));
	childWeapon = CreateDefaultSubobject<UChildActorComponent>(FName("childW"));

	childWeapon->SetupAttachment(charmesh); 
	charmesh->SetupAttachment(GetRootComponent());
	spawnSoundC->SetupAttachment(charmesh);
}

void APrimitiveSoldier::BeginPlay()
{
	Super::BeginPlay();
	childWeapon->SetChildActorClass(childWclass);
	if (sound) {
		UGameplayStatics::PlaySound2D(this, sound);
	}

}

void APrimitiveSoldier::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APrimitiveSoldier::die()
{
	if (sound) {
		UGameplayStatics::PlaySound2D(this, sound);
	}
	if (dyingEffect) {
		UGameplayStatics::SpawnEmitterAttached(dyingEffect,charmesh,FName("mesh"),GetActorLocation(),GetActorRotation());
	}

	Destroy();

}

