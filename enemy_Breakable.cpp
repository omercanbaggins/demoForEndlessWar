// Fill out your copyright notice in the Description page of Project Settings.


#include "enemy_Breakable.h"
#include "PawnBase.h"
#include "Kismet/GameplayStatics.h"
#include "Weapon.h"
#include "Kismet/KismetMathLibrary.h"


/*Aenemy_Breakable::Aenemy_Breakable() {
	meshToDestruct = CreateDefaultSubobject<UDestructibleMComponent>(FName("destructible"));
	meshToDestruct-SetupAttachment(RootComponent)
}
*/ 

Aenemy_Breakable::Aenemy_Breakable() {
	meshforW = CreateDefaultSubobject<UStaticMeshComponent>(FName("weaponToGive"));
	meshforW->SetupAttachment(RootComponent);
	meshforW->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
void Aenemy_Breakable::BeginPlay() {

	Super::BeginPlay();
	int randomEnumIndex = UKismetMathLibrary::RandomIntegerInRange(1, 3);
	weaponToHold = (containedWeapon)randomEnumIndex;
	health = Health; //one is come from interface other come from base enemy class this problem will be fixed
	if(weaponData)
		weaponStruct = weaponData->FindRow<FWeaponInformation>(UEnumFuncs::getEnumName(weaponToHold), "asd");
		if (weaponStruct){
			meshforW->SetStaticMesh(weaponStruct->weaponMesh);
		}
	}
TArray<AActor*> weapons; //getactors function needs AActor array. This will be converted into AWeapon* using cast 

void Aenemy_Breakable::affectPlayer(AWeapon* weaponRef) //when this actor is killed this function is invoked in order to give player new weapon
{
	weaponRef->GetClass();
	UGameplayStatics::GetAllActorsOfClass(this, weaponRef->GetClass(), weapons);
	if (weapons.Num() > 0) {	
		for (int i = 0; i < weapons.Num() && weapons[i]; i++) {
			Cast<AWeapon>(weapons[i])->setWeaponType(UEnumFuncs::getEnumName(weaponToHold));
		}
	}
	Destroy();

}

FName rn = FName("tank");
void Aenemy_Breakable::respondToOverlap(APawnBase* playerRef)
{
	playerRef->Destroy();
}


/*if (pawns[0]) {
				FVector vectorSubst = GetActorLocation() - pawns[0]->GetActorLocation();
				vectorSubst.Z = 0;
				SetActorRotation(vectorSubst.Rotation());
			}*/