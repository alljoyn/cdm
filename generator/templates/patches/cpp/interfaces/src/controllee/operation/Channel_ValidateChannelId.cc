        uint16_t numChannels;
        if (m_ChannelModelInterface->GetTotalNumberOfChannels(numChannels) != ER_OK)
            return ER_FAIL;

        std::vector<ChannelInterface::ChannelInfoRecord> availableChannels;
        ErrorCode errorCode;
        if (m_ChannelModelInterface->GetChannelList(0, numChannels, availableChannels, errorCode, m_cdmControllee) != ER_OK)
            return ER_FAIL;

        if (std::find(availableChannels.begin(), availableChannels.end(), value) == availableChannels.end())
            return ER_INVALID_DATA;
