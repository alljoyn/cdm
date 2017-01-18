static void CopyChannel_ChannelInfoRecord(Channel_ChannelInfoRecord* value, Channel_ChannelInfoRecord* copy)
{
    copy->channelID = strdup(value->channelID);
    copy->channelNumber = strdup(value->channelNumber);
    copy->channelName = strdup(value->channelName);
}
