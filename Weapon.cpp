// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "OverlappingObjects.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"


// Sets default values
AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	rootScene = CreateDefaultSubobject<USceneComponent>(FName("root"));
	weaponFront = CreateDefaultSubobject<USphereComponent>(FName("namlu"));
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("weapon"));

	SetRootComponent(rootScene);
	mesh->SetupAttachment(RootComponent);
	weaponFront->SetupAttachment(mesh);
	timeForFiring = 1.0f;

}
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(timerhandle, this, &AWeapon::Fire, timeForFiring, true, timeForFiring);
	setWeaponType("auto");
}
void AWeapon::setWeaponType(FName rowname) {
	if (table) {
		GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Red, FString("succeed"), true);
		tableInstance = table->FindRow<FWeaponInformation>(rowname, "asd", true);

		if (tableInstance) {
			timeForFiring = tableInstance->firingTime;
			sound = tableInstance->firingSound;
			effect = tableInstance->firingParticle;
			mesh->SetStaticMesh(tableInstance->weaponMesh);
			GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
			GetWorldTimerManager().SetTimer(timerhandle, this, &AWeapon::Fire, timeForFiring, true, timeForFiring);
		}
	}
	else {
		GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Red, FString("failed"), true);

	}
}
FHitResult hitresults;
FVector End;
IOverlapRespond* hitA;
void AWeapon::Fire() {
	UGameplayStatics::PlaySound2D(this, sound);
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), effect, weaponFront->GetComponentLocation(), weaponFront->GetComponentRotation());

	End = weaponFront->GetComponentLocation() + mesh->GetForwardVector() * 1000;
	GetWorld()->LineTraceSingleByChannel(hitresults, weaponFront->GetComponentLocation(), End, ECollisionChannel::ECC_Camera);
	DrawDebugLine(GetWorld(), weaponFront->GetComponentLocation(), End, FColor::Red, true, 0.2f);
	hitA = Cast<IOverlapRespond>(hitresults.GetActor());

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), effect, hitresults.ImpactPoint, FRotator(0));
	if (hitA) {
		if (hitA->getDamage(2) <= 0) {
				hitA->affectPlayer(this);
		}
	}
}

void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}
