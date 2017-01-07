    std::ostringstream strm;

    // Qt rich text, auto-detected
    strm << "<html><body>"
         << "<h1>Channels</h1>\n"
         << "<table>\n"
         << "<thead><tr><th bgcolor=\"lightblue\">ID</th><th bgcolor=\"lightblue\">Number</th><th bgcolor=\"lightblue\">Name</th></tr></thead>\n";


    for (auto& entry : listOfChannelInfoRecords)
    {
          strm << "<tr><td>" <<entry.channelID.c_str()
               << "</td><td>" << entry.channelNumber.c_str()
               << "</td><td>" << entry.channelName.c_str()
               << "</td></tr>\n";
    }
    strm << "</table>"
         << "</body></html>\n";

    auto str = strm.str();
    auto dlg = new org_alljoyn_SmartSpaces_Operation_Channel_ShowChannelList(this, str.c_str());
    dlg->run();
    delete dlg;
