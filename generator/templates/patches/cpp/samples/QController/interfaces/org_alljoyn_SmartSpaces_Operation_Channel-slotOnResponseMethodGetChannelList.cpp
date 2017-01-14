    std::ostringstream strm;

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
    messages_->setTextFormat(Qt::RichText);
    messages_->setText(str.c_str());
