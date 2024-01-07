// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OverlapRespond.h"
#include "OverlappingObjects.generated.h"


UCLASS()
class ENDLESSWAR_API AOverlappingObjects : public AActor
{

	GENERATED_BODY()
	
public:	
	AOverlappingObjects();

protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly)
	class USphereComponent* collisionSimple;
	//UPROPERTY()
	//class USoundBase* sound;
	//UPROPERTY()
	//class UParticleSystem* effect;
	UPROPERTY()
	class USceneComponent* scene;
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* mesh;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class APawnBase> pawnClass;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	int speedConstantforMoving = 1; //to arrange speed to move
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int Health =1;
	
public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE int getHealth() {
		return Health;
	};

	UFUNCTION(BlueprintCallable)
	FORCEINLINE int getSpeedConstant() {
		return speedConstantforMoving;
	};
	UFUNCTION(BlueprintCallable)
	void setHealth(int h) {
		Health = h;
	};
		
	UFUNCTION(BlueprintCallable)
	void setSpeedConstant(int s) {
		speedConstantforMoving = s;
	};
	
	void Interact();

	void autoKill();

	virtual void Tick(float DeltaTime) override;

};
