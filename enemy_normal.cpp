// Fill out your copyright notice in the Description page of Project Settings.


#include "enemy_normal.h"
#include "Weapon.h"
#include "PrimitiveSoldier.h"
#include "PawnBase.h"
#include "Kismet/GameplayStatics.h"

void Aenemy_normal::BeginPlay() {
	Super::BeginPlay();

	health = Health;
}
void Aenemy_normal::respondToOverlap(APawnBase* playerRef)
{
	playerRef-> Destroy();
}

void Aenemy_normal::affectPlayer(AWeapon* weaponRef)
{
	APawnBase* player = Cast<APawnBase>(weaponRef->GetParentActor());
	if (player) {
		GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Red, FString::FromInt(player->getPoint()), true);
		player->setPoint();
		Destroy();
	}
}
APawnBase* player;
void Aenemy_normal::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	player = Cast<APawnBase>(UGameplayStatics::GetPlayerPawn(this, 0));
		if(player) {
		FVector vectorSubst = GetActorLocation() - player->GetActorLocation();
		vectorSubst.Z = 0;
		SetActorRotation(vectorSubst.Rotation());
	}
}