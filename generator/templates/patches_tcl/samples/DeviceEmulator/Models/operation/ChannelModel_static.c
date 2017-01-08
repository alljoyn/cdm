static Array_Channel_ChannelInfoRecord* getChannels(void)
{
    static Array_Channel_ChannelInfoRecord s_channels;

    if (!s_channels.elems) {
        InitArray_Channel_ChannelInfoRecord(&s_channels, 0);
        size_t i = 0;

        i = ExtendArray_Channel_ChannelInfoRecord(&s_channels, 1);
        s_channels.elems[i].channelID = strdup("a");
        s_channels.elems[i].channelNumber = strdup("1");
        s_channels.elems[i].channelName = strdup("Hobbit News");

        i = ExtendArray_Channel_ChannelInfoRecord(&s_channels, 1);
        s_channels.elems[i].channelID = strdup("b");
        s_channels.elems[i].channelNumber = strdup("2");
        s_channels.elems[i].channelName = strdup("Shire Shopping Network");
    }

    return &s_channels;
}

static void CopyChannel_ChannelInfoRecord(Channel_ChannelInfoRecord* value, Channel_ChannelInfoRecord* copy)
{
    copy->channelID = strdup(value->channelID);
    copy->channelNumber = strdup(value->channelNumber);
    copy->channelName = strdup(value->channelName);
}
