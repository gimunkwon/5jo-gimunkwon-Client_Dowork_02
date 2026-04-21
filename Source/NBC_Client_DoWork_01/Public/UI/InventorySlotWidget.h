#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventorySlotWidget.generated.h"

class UImage;
class UButton;
class UPaperSprite;

UCLASS()
class NBC_CLIENT_DOWORK_01_API UInventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void UpdateSlotImage(UPaperSprite* SpriteImage);
	virtual void NativeConstruct() override;
	
protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> Image_Item;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> Btn_InvenSlot;
};
