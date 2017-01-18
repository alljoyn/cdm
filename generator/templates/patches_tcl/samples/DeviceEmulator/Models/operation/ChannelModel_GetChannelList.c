    AJ_Status status = AJ_OK;
    Array_Channel_ChannelInfoRecord channels;

    InitArray_Channel_ChannelInfoRecord(&channels, 0);

    Element* elem = HAL_ReadProperty(objPath, "org.alljoyn.SmartSpaces.Operation.Channel", "__ChannelList");

    if (elem) {
        HAL_Decode_Array_Channel_ChannelInfoRecord(elem, &channels);
        BSXML_FreeElement(elem);

        InitArray_Channel_ChannelInfoRecord(listOfChannelInfoRecords, 0);

        if (startingRecord < channels.numElems)
        {
            for (size_t i = startingRecord; i < startingRecord + numRecords && i < channels.numElems; ++i)
            {
                size_t j = ExtendArray_Channel_ChannelInfoRecord(listOfChannelInfoRecords, 1);
                listOfChannelInfoRecords->elems[j] = channels.elems[i];
                CopyChannel_ChannelInfoRecord(&channels.elems[i], &listOfChannelInfoRecords->elems[j]);
            }
        }
    } else {
        return AJ_ERR_FAILURE;
    }

    FreeArray_Channel_ChannelInfoRecord(&channels);
    return status;
