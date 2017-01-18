    std::vector<ChannelInterface::ChannelInfoRecord> channels;

    auto status = HAL::ReadProperty(m_busPath, "org.alljoyn.SmartSpaces.Operation.Channel", "__ChannelList", channels);

    if (status != ER_OK) {
        error = FEATURE_NOT_AVAILABLE;
        return status;
    }

    if (arg_startingRecord >= channels.size()) {
        error = INVALID_VALUE;
    } else {
        for (auto i = arg_startingRecord; i < arg_startingRecord + arg_numRecords && i < channels.size(); ++i) {
            arg_listOfChannelInfoRecords.push_back(channels[i]);
        }
    }

    return ER_OK;
