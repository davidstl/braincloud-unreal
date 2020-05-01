// Copyright 2018 bitHeads, Inc. All Rights Reserved.

#include "BrainCloudTimeUtils.h"
#include "BCClientPluginPrivatePCH.h"
#include "BrainCloudWrapper.h"
#include "BCWrapperProxy.h"

BrainCloudTimeUtils::BrainCloudTimeUtils(BrainCloudClient *client) : _client(client){};

int64 BrainCloudTimeUtils::UTCDateTimeToUTCMillis(FDateTime dateTime)
{
    FTimespan mySpan;
    FDateTime date = dateTime.UtcNow();
    FDateTime myFDateTime(1970, 1, 1, 0, 0, 0, 0);
    int64 ticks = date.GetTicks() - myFDateTime.GetTicks();
    int64 ts = ticks / mySpan.GetTicks();
    return ts;
}

FDateTime BrainCloudTimeUtils::UTCMillisToUTCDateTime(int64 utcDateTime)
{
    FTimespan mySpan;
    FDateTime timeInTicks = utcDateTime * mySpan.GetTicks();
    FDateTime myFDateTime= FDateTime(1970, 1, 1, 0, 0, 0, 0)+timeInTicks.GetTicks();
    return myFDateTime;
}

FDateTime BrainCloudTimeUtils::LocalTimeToUTCTime(FDateTime localDate)
{
    return localDate.UtcNow();
}
    
FDateTime BrainCloudTimeUtils::UTCTimeToLocalTime (FDateTime utcDate)
{
    return utcDate.Now();
    utcDate.ToString();
}
