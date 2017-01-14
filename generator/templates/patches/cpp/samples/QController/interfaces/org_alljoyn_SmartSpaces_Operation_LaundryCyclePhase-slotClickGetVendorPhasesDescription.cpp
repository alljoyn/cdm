    QString lang = languageTag.c_str();
    if (lang.isEmpty())
    {
        lang = "en";
    }
    ok = DialogGetLang(this, lang);
    auto ascii = lang.toStdString();
    languageTag = ascii.c_str();
