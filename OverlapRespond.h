// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "OverlapRespond.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UOverlapRespond : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ENDLESSWAR_API IOverlapRespond
{
	GENERATED_BODY()
public:
	int health;
	virtual void respondToOverlap(class APawnBase* playerRef) = 0; // function will be triggered inside beginoverlap function by the player pawn
	virtual void affectPlayer(class AWeapon* weaponRef) = 0; // this will be called when objects are destructed by the player or overlapped functions called.
	FORCEINLINE virtual int getDamage(int d) {
		health -= d;
		return health;
	};
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
};
