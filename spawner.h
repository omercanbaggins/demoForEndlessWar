// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "spawner.generated.h"


UCLASS()
class ENDLESSWAR_API Aspawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Aspawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void spawn();
	UFUNCTION()
	void SpawnEnemy();

	UFUNCTION()
	void overlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	UStaticMeshComponent* meshFloor;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UArrowComponent* arrow;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UBoxComponent* boxCol;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class USceneComponent* scene; //root
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<Aspawner> spawnclass; //FOR PATH
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class AOverlappingObjects> spawnEnemyClass; //FOR PATH


};
