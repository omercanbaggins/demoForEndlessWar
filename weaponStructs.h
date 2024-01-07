#pragma once
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "weaponStructs.generated.h"

USTRUCT()
struct FWeaponInformation :public FTableRowBase {
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
	UStaticMesh* weaponMesh;

	UPROPERTY(EditDefaultsOnly)
	float firingTime;

	UPROPERTY(EditDefaultsOnly)
	UParticleSystem* firingParticle;

	UPROPERTY(EditDefaultsOnly)
	USoundBase* firingSound;
};

UENUM()
enum class containedWeapon :uint32 {
	gun_normal = 1,
	gun_tank,
	gun_auto
};

UCLASS()
class UEnumFuncs:public UObject {
	GENERATED_BODY()
public:
	static containedWeapon weaponToHold;
	FORCEINLINE static FName getEnumName(containedWeapon w) {
	
		FName enumName;
		switch (w) {
		case containedWeapon::gun_normal:
			enumName = FName("normal");
			break;
		case containedWeapon::gun_tank:
			enumName = FName("tank");
			break;
		case containedWeapon::gun_auto:
			enumName = FName("auto");
			break;
		}
		return enumName;
	}
	UEnumFuncs() = default;
};