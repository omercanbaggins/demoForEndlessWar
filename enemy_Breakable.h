// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OverlappingObjects.h"
#include "weaponStructs.h"
#include "enemy_Breakable.generated.h"


/**
 * 

UENUM()
enum class containedWeapon:uint32{
	gun_normal=1,
	gun_tank,
	gun_auto
}; */
UCLASS()
class ENDLESSWAR_API Aenemy_Breakable : public AOverlappingObjects, public IOverlapRespond
{
	GENERATED_BODY()
public:
	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	containedWeapon weaponToHold;
	Aenemy_Breakable();
	virtual void BeginPlay() override;
	virtual void affectPlayer(class AWeapon* weaponRef) override;
	virtual void respondToOverlap(class APawnBase* playerRef) override;
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* meshforW;
	UPROPERTY(EditDefaultsOnly)
	UDataTable* weaponData;
	FWeaponInformation* weaponStruct;
	//UPROPERTY(EditDefaultsOnly)
	//class UDestructibleComponent* meshToDestruct;
};
