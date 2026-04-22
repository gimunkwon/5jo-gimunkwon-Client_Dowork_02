#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Global/MyPlayerTitle.h"
#include "MyPlayer.generated.h"

class UMyPlayerInventory;

UCLASS()
class NBC_CLIENT_DOWORK_01_API AMyPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	AMyPlayer();
	
	FORCEINLINE UMyPlayerInventory* GetInventory() const {return InventoryAC;}
	FORCEINLINE const TSet<EPlayer_Title>& GetPlayerTitle() const {return PlayerTitle;}
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="ActorComponent")
	TObjectPtr<UMyPlayerInventory> InventoryAC;
	
	// 칭호
	TSet<EPlayer_Title> PlayerTitle;
public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
