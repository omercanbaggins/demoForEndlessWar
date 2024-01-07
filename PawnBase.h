// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PawnBase.generated.h"

UCLASS()
class ENDLESSWAR_API APawnBase : public APawn
{
	GENERATED_BODY()

private:

	int point = 0;
	
	UFUNCTION()
	void ZoomInZoomOut(float V);

	UPROPERTY(EditDefaultsOnly)
	class UBoxComponent* sphere;

	UPROPERTY(EditDefaultsOnly)
	class UCameraComponent* cam;

	UPROPERTY(EditDefaultsOnly)
	class USpringArmComponent* cmboom;	
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void rotatePlayer(float V);
	float StartVectorY;
public:
	APawnBase();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void setPoint() { point++; }
	void setPoint(int a) { point += a; }
	UFUNCTION()
	FVector getLoc() const;
	UFUNCTION()
	void slide(float V);
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION(BlueprintCallable)
	FORCEINLINE int getPoint() const { return point; }
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UChildActorComponent* ChildfirstSoldier; //ilk asker
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	TSubclassOf<UActorComponent> childactorClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class AWeapon> childSoldierclass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FVector tempVec;


};
