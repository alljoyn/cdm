    MutLock lock(s_alertsMutex);
    s_alerts.clear();
    return ER_OK;
