    MutLock lock(s_alertsMutex);
    s_alerts.erase(std::remove(s_alerts.begin(), s_alerts.end(), arg_alertCode));
    return ER_OK;
