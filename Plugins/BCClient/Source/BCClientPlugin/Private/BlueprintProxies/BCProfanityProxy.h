// Copyright 2016 bitHeads, Inc. All Rights Reserved.

#pragma once

#include "BCBlueprintCallProxyBase.h"
#include "IServerCallback.h"
#include "BCProfanityProxy.generated.h"

class ABrainCloud;

UCLASS(MinimalAPI)
class UBCProfanityProxy : public UBCBlueprintCallProxyBase, public IServerCallback
{
    GENERATED_BODY()

public:
    UBCProfanityProxy(const FObjectInitializer& ObjectInitializer);

    /**
    * Checks supplied text for profanity.
    *
    * Service Name - Profanity
    * Service Operation - ProfanityCheck
    *
    * Param - text The text to check
    * Param - languages Optional comma delimited list of two character language codes
    * Param - flagEmail Optional processing of email addresses
    * Param - flagPhone Optional processing of phone numbers
    * Param - flagUrls Optional processing of urls
    *
    * Significant error codes:
    *
    * 40421 - WebPurify not configured
    * 40422 - General exception occurred
    * 40423 - WebPurify returned an error (Http status != 200)
    * 40424 - WebPurify not enabled
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Profanity")
        static UBCProfanityProxy* ProfanityCheck(ABrainCloud *brainCloud, const FString& text, const FString& languages, bool flagEmail, bool flagPhone, bool flagUrls);

    /**
    * Replaces the characters of profanity text with a passed character(s).
    *
    * Service Name - Profanity
    * Service Operation - ProfanityReplaceText
    *
    * Param - text The text to check
    * Param - replaceSymbol The text to replace individual characters of profanity text with
    * Param - languages Optional comma delimited list of two character language codes
    * Param - flagEmail Optional processing of email addresses
    * Param - flagPhone Optional processing of phone numbers
    * Param - flagUrls Optional processing of urls
    *
    * Significant error codes:
    *
    * 40421 - WebPurify not configured
    * 40422 - General exception occurred
    * 40423 - WebPurify returned an error (Http status != 200)
    * 40424 - WebPurify not enabled
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Profanity")
        static UBCProfanityProxy* ProfanityReplaceText(ABrainCloud *brainCloud, const FString& text, const FString& replaceSymbol, const FString& languages, bool flagEmail, bool flagPhone, bool flagUrls);

    /**
    * Checks supplied text for profanity and returns a list of bad wors.
    *
    * Service Name - Profanity
    * Service Operation - ProfanityIdentifyBadWords
    *
    * Param - text The text to check
    * Param - languages Optional comma delimited list of two character language codes
    * Param - flagEmail Optional processing of email addresses
    * Param - flagPhone Optional processing of phone numbers
    * Param - flagUrls Optional processing of urls
    *
    * Significant error codes:
    *
    * 40421 - WebPurify not configured
    * 40422 - General exception occurred
    * 40423 - WebPurify returned an error (Http status != 200)
    * 40424 - WebPurify not enabled
    */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "BrainCloud|Profanity")
        static UBCProfanityProxy* ProfanityIdentifyBadWords(ABrainCloud *brainCloud, const FString& text, const FString& languages, bool flagEmail, bool flagPhone, bool flagUrls);

    //Response delegates
    UPROPERTY(BlueprintAssignable)
        FBrainCloudCallbackDelegate OnSuccess;

    UPROPERTY(BlueprintAssignable)
        FBrainCloudCallbackDelegate OnFailure;

protected:
    // IServerCallback interface
    void serverCallback(ServiceName serviceName, ServiceOperation serviceOperation, const FString& jsonData);
    void serverError(ServiceName serviceName, ServiceOperation serviceOperation, int32 statusCode, int32 reasonCode, const FString& jsonError);
    // End of IServerCallback interface
};
