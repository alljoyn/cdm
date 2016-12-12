    Array_Channel_ChannelInfoRecord* channels = getChannels();

    InitArray_Channel_ChannelInfoRecord(listOfChannelInfoRecords, 0);

    if (startingRecord >= channels->numElems)
    {
        return AJ_ERR_FAILURE;
    }

    for (size_t i = startingRecord; i < startingRecord + numRecords && i < channels->numElems; ++i)
    {
        size_t j = ExtendArray_Channel_ChannelInfoRecord(listOfChannelInfoRecords, 1);
        listOfChannelInfoRecords->elems[j] = channels->elems[i];
        CopyChannel_ChannelInfoRecord(&channels->elems[i], &listOfChannelInfoRecords->elems[j]);
    }

    return AJ_OK;
