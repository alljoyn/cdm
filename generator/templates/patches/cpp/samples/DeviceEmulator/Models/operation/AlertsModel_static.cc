static std::vector<AlertsInterface::AlertCodesDescriptor> s_descriptions = {
    // alertCode description
    {1,   "bad",    },
    {2,   "worse"   },
    {3,   "stuffed" }
};

using MutLock = std::lock_guard<std::mutex>;

static std::vector<uint16_t> s_alerts;
static std::mutex s_alertsMutex;

static bool AlertCommand(const std::string& key, const StringVec& args)
{
    bool ok = false;

    if (args.size() == 2)
    {
        if (args[0] == "alert")
        {
            std::istringstream strm(args[1]);
            uint16_t a;
            strm >> a;
            ok = true;
            MutLock lock(s_alertsMutex);
            s_alerts.push_back(a);
        }
    }

    return ok;
}

static bool s_subscribed = Commands::Instance().Subscribe("alert", AlertCommand, "alert args");

