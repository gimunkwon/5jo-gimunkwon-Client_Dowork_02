#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryInfoWidget.generated.h"

class UTextBlock;
class UImage;

UCLASS()
class NBC_CLIENT_DOWORK_01_API UInventoryInfoWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void UpdateItemInfo(FName SelectedItemName);
	
protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> Image_Item;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Text_ItemName;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Text_ItemDescription;
	
	UPROPERTY()
	TMap<FName,FText> ItemDescription;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="DataTable")
	TObjectPtr<UDataTable> ItemDataTable;
};
