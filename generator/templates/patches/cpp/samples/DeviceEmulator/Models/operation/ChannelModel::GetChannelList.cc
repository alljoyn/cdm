    if (arg_startingRecord >= s_channels.size())
    {
        error = INVALID_VALUE;
    }
    else
    {
        for (auto i = arg_startingRecord; i < arg_startingRecord + arg_numRecords && i < s_channels.size(); ++i)
        {
            arg_listOfChannelInfoRecords.push_back(s_channels[i]);
        }
    }

    return ER_OK;
