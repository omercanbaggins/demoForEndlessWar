// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "weaponStructs.h"
#include "Weapon.generated.h"

UCLASS()
class ENDLESSWAR_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeapon();
	virtual void Tick(float DeltaTime) override;
	UPROPERTY()
	FTimerHandle timerhandle;

	FWeaponInformation* tableInstance;
	UPROPERTY(EditDefaultsOnly)
	FName rowName;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* mesh;
	UPROPERTY(EditAnywhere)
	float timeForFiring;
	UPROPERTY(EditAnywhere)
	UParticleSystem* effect;
	UPROPERTY(EditAnywhere)
	USoundBase* sound;
	UPROPERTY(EditAnywhere)
	UDataTable* table;
	UPROPERTY(EditAnywhere)
	class USphereComponent* weaponFront;
	UPROPERTY(EditAnywhere)
	USceneComponent* rootScene;
	void setWeaponType(FName rowname);


protected:
	virtual void BeginPlay() override;


	void Fire();

};
