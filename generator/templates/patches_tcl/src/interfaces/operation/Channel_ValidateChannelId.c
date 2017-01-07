        uint16_t numChannels;
        if (model->GetTotalNumberOfChannels(model, objPath, &numChannels) != AJ_OK)
            return AJ_ERR_FAILURE;

        Array_Channel_ChannelInfoRecord availableChannels;
        if (model->MethodGetChannelList(model, objPath,0, numChannels, &availableChannels) != AJ_OK)
            return AJ_ERR_FAILURE;

        if (!valueIn_Array_Channel_ChannelInfoRecord(value, &availableChannels))
            return AJ_ERR_INVALID;

        FreeArray_Channel_ChannelInfoRecord(&availableChannels);