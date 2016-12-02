// A static list of channels
static std::vector<ChannelInterface::ChannelInfoRecord> s_channels = {
    // channelID channelNumber channelName
    {"a",   "1",    "Hobbit News"},
    {"b",   "2",    "Shire Shopping Network"}
};

static const char* BusPath = "/CDM/Channel";

static bool ChannelCommand(const std::string& key, const StringVec& args, CdmControllee& controllee)
{
    bool ok = false;

    if (args.size() >= 1)
    {
        if (args[0] == "signal")
        {
            if (auto iface = controllee.GetInterface<ChannelIntfControllee>(BusPath, "org.alljoyn.SmartSpaces.Operation.Channel"))
            {
                iface->EmitChannelListChanged();
                ok = true;
            }
        }
    }

    return ok;
}

static bool s_subscribed = Commands::Instance().Subscribe("channel", ChannelCommand, "channel signal");

