// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PrimitiveSoldier.generated.h"


UCLASS()
class ENDLESSWAR_API APrimitiveSoldier : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* charmesh;

	UPROPERTY(EditAnywhere)
	class UAudioComponent* spawnSoundC;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* dyingEffect;

	APrimitiveSoldier();

	virtual void Tick(float DeltaTime) override;

	int a = 5;
	void die();
	UPROPERTY(EditAnywhere)
	class USoundBase* sound;
	UPROPERTY(EditDefaultsOnly)
	UChildActorComponent* childWeapon; 
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AWeapon> childWclass;


protected:
	virtual void BeginPlay() override;

};
