/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for any
 *    purpose with or without fee is hereby granted, provided that the above
 *    copyright notice and this permission notice appear in all copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/
//Code Under Test
#include <HaeAboutData.h>


#include <alljoyn/version.h>
#include <gtest/gtest.h>
#include <qcc/String.h>

#include <map>
#include <alljoyn/hae/DeviceTypeDescription.h>

namespace ajn{
namespace services{

TEST(HaeAboutDataTest, constants) {
  //HAE Unique
    EXPECT_STREQ("CountryOfProduction", ajn::services::HaeAboutData::HaeAboutKeys::COUNTRY_OF_PRODUCTION.c_str());
    EXPECT_STREQ("CorporateBrand", ajn::services::HaeAboutData::CORPORATE_BRAND.c_str());
    EXPECT_STREQ("ProductBrand", ajn::services::HaeAboutData::PRODUCT_BRAND.c_str());
    EXPECT_STREQ("Location", ajn::services::HaeAboutData::LOCATION.c_str());
    EXPECT_STREQ("DeviceTypeDescription", ajn::services::HaeAboutData::DEVICE_TYPE_DESCRIPTION.c_str());

}
    


TEST(HaeAboutDataTest, VerifyFieldValues) {
    HaeAboutData aboutData;

    //CountryOfProduction
    EXPECT_FALSE(aboutData.IsFieldRequired(HaeAboutData::COUNTRY_OF_PRODUCTION.c_str()));
    EXPECT_FALSE(aboutData.IsFieldAnnounced(HaeAboutData::COUNTRY_OF_PRODUCTION.c_str()));
    EXPECT_TRUE(aboutData.IsFieldLocalized(HaeAboutData::COUNTRY_OF_PRODUCTION.c_str()));
    EXPECT_STREQ("s", aboutData.GetFieldSignature(HaeAboutData::COUNTRY_OF_PRODUCTION.c_str()));

    //CorporateBrand
    EXPECT_FALSE(aboutData.IsFieldRequired(HaeAboutData::CORPORATE_BRAND.c_str()));
    EXPECT_FALSE(aboutData.IsFieldAnnounced(HaeAboutData::CORPORATE_BRAND.c_str()));
    EXPECT_TRUE(aboutData.IsFieldLocalized(HaeAboutData::CORPORATE_BRAND.c_str()));
    EXPECT_STREQ("s", aboutData.GetFieldSignature(HaeAboutData::CORPORATE_BRAND.c_str()));

    //ProductBrand
    EXPECT_FALSE(aboutData.IsFieldRequired(HaeAboutData::PRODUCT_BRAND.c_str()));
    EXPECT_FALSE(aboutData.IsFieldAnnounced(HaeAboutData::PRODUCT_BRAND.c_str()));
    EXPECT_TRUE(aboutData.IsFieldLocalized(HaeAboutData::PRODUCT_BRAND.c_str()));
    EXPECT_STREQ("s", aboutData.GetFieldSignature(HaeAboutData::PRODUCT_BRAND.c_str()));

    //Location
    EXPECT_TRUE(aboutData.IsFieldRequired(HaeAboutData::LOCATION.c_str()));
    EXPECT_TRUE(aboutData.IsFieldAnnounced(HaeAboutData::LOCATION.c_str()));
    EXPECT_TRUE(aboutData.IsFieldLocalized(HaeAboutData::LOCATION.c_str()));
    EXPECT_STREQ("s", aboutData.GetFieldSignature(HaeAboutData::LOCATION.c_str()));

    //DeviceTypeDescription
    EXPECT_TRUE(aboutData.IsFieldRequired(HaeAboutData::DEVICE_TYPE_DESCRIPTION.c_str()));
    EXPECT_TRUE(aboutData.IsFieldAnnounced(HaeAboutData::DEVICE_TYPE_DESCRIPTION.c_str()));
    EXPECT_FALSE(aboutData.IsFieldLocalized(HaeAboutData::DEVICE_TYPE_DESCRIPTION.c_str()));
    EXPECT_STREQ("a(uo)", aboutData.GetFieldSignature(HaeAboutData::DEVICE_TYPE_DESCRIPTION.c_str()));

}


TEST(HaeAboutDataTest, DefaultLanguageNotSpecified) {
    QStatus status = ER_FAIL;
    HaeAboutData aboutData;
    
    //HAE SPECIFIC
    status = aboutData.SetCountryOfProduction("A Country");
    EXPECT_EQ(ER_ABOUT_DEFAULT_LANGUAGE_NOT_SPECIFIED, status);
    
    status = aboutData.SetCorporateBrand("A Company");
    EXPECT_EQ(ER_ABOUT_DEFAULT_LANGUAGE_NOT_SPECIFIED, status);
    
    status = aboutData.SetProductBrand("A Brand");
    EXPECT_EQ(ER_ABOUT_DEFAULT_LANGUAGE_NOT_SPECIFIED, status);
    
    status = aboutData.SetLocation("A place in my home");
    EXPECT_EQ(ER_ABOUT_DEFAULT_LANGUAGE_NOT_SPECIFIED, status);
    
}


//MFF - Spot check changing new HAE fields
TEST(HaeAboutDataTest, CopyConstructor) {
    HaeAboutData aboutData("en");
    char* language;
    aboutData.GetDefaultLanguage(&language);
    EXPECT_STREQ("en", language);
    char* ajSoftwareVersion;
    aboutData.GetAJSoftwareVersion(&ajSoftwareVersion);
    EXPECT_STREQ(ajn::GetVersion(), ajSoftwareVersion);

    HaeAboutData aboutDataCopy(aboutData);
    aboutDataCopy.GetDefaultLanguage(&language);
    EXPECT_STREQ("en", language);

    aboutDataCopy.GetAJSoftwareVersion(&ajSoftwareVersion);
    EXPECT_STREQ(ajn::GetVersion(), ajSoftwareVersion);

    //should be able to change each copy independent of one another
    QStatus status = aboutData.SetProductBrand("Brand");
    EXPECT_EQ(ER_OK, status);

    status = aboutDataCopy.SetProductBrand("New Brand");
    EXPECT_EQ(ER_OK, status);

    char* brand;
    status = aboutData.GetProductBrand(&brand);
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("Brand", brand);

    status = aboutDataCopy.GetProductBrand(&brand);
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("New Brand", brand);
}
    
    
//MFF - Spot check changing new HAE fields
TEST(HaeAboutDataTest, AssignmentOperator) {
    HaeAboutData aboutData("en");
    char* language;
    aboutData.GetDefaultLanguage(&language);
    EXPECT_STREQ("en", language);
    char* ajSoftwareVersion;
    aboutData.GetAJSoftwareVersion(&ajSoftwareVersion);
    EXPECT_STREQ(ajn::GetVersion(), ajSoftwareVersion);

    // Self assignment
    aboutData = aboutData;
    HaeAboutData aboutDataCopy;
    aboutDataCopy = aboutData;
    aboutDataCopy.GetDefaultLanguage(&language);
    EXPECT_STREQ("en", language);

    aboutDataCopy.GetAJSoftwareVersion(&ajSoftwareVersion);
    EXPECT_STREQ(ajn::GetVersion(), ajSoftwareVersion);

    //should be able to change each copy independent of one another
    QStatus status = aboutData.SetCorporateBrand("Company");
    EXPECT_EQ(ER_OK, status);

    status = aboutDataCopy.SetCorporateBrand("Copy Company");
    EXPECT_EQ(ER_OK, status);

    char* brand;
    status = aboutData.GetCorporateBrand(&brand);
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("Company", brand);

    status = aboutDataCopy.GetCorporateBrand(&brand);
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("Copy Company", brand);
}

    
TEST(HaeAboutDataTest, SetCountryOfProduction) {
    QStatus status = ER_FAIL;
    HaeAboutData aboutData("en");
    char* language;
    status = aboutData.GetDefaultLanguage(&language);
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("en", language);
    char* ajSoftwareVersion;
    status = aboutData.GetAJSoftwareVersion(&ajSoftwareVersion);
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ(ajn::GetVersion(), ajSoftwareVersion);

    status = aboutData.SetCountryOfProduction("Italy");
    EXPECT_EQ(ER_OK, status);

    char* country;
    status = aboutData.GetCountryOfProduction(&country);
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("Italy", country);

    status = aboutData.SetCountryOfProduction("Italia", "it");
    EXPECT_EQ(ER_OK, status);

    status = aboutData.GetCountryOfProduction(&country, "it");
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("Italia", country);
}


TEST(HaeAboutDataTest, SetCorporateBrand) {
    QStatus status = ER_FAIL;
    HaeAboutData aboutData("en");

    status = aboutData.SetCorporateBrand("Company");
    EXPECT_EQ(ER_OK, status);

    char* brand;
    status = aboutData.GetCorporateBrand(&brand);
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("Company", brand);

    status = aboutData.SetCorporateBrand("회사", "ko");
    EXPECT_EQ(ER_OK, status);

    status = aboutData.GetCorporateBrand(&brand, "ko");
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("회사", brand);
}

TEST(HaeAboutDataTest, SetProductBrand) {
    QStatus status = ER_FAIL;
    HaeAboutData aboutData("en");

    status = aboutData.SetProductBrand("Product");
    EXPECT_EQ(ER_OK, status);

    char* brand;
    status = aboutData.GetProductBrand(&brand);
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("Product", brand);

    status = aboutData.SetProductBrand("製品", "ja");
    EXPECT_EQ(ER_OK, status);

    status = aboutData.GetProductBrand(&brand, "ja");
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("製品", brand);
}


TEST(HaeAboutDataTest, SetLocation) {
    QStatus status = ER_FAIL;
    HaeAboutData aboutData("en");

    status = aboutData.SetLocation("upstairs bedroom");
    EXPECT_EQ(ER_OK, status);

    char* location;
    status = aboutData.GetLocation(&location);
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("upstairs bedroom", location);

    status = aboutData.SetLocation("habitación del segundo piso", "es");
    EXPECT_EQ(ER_OK, status);

    status = aboutData.GetLocation(&location, "es");
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("habitación del segundo piso", location);
}


TEST(HaeAboutDataTest, SetDeviceTypeDescription) {
    QStatus status = ER_FAIL;
    HaeAboutData aboutData("en");
    
    DeviceTypeDescription description;
    description.AddDeviceType(THERMOSTAT, "/Hae/Thermostat");
    status = aboutData.SetDeviceTypeDescription(&description);
    EXPECT_EQ(ER_OK, status);

    DeviceTypeDescription*  returnedDescription = new DeviceTypeDescription();
    status = aboutData.GetDeviceTypeDescription( &returnedDescription);
    EXPECT_EQ(ER_OK, status);

    std::multimap<DeviceType, qcc::String>::const_iterator it = returnedDescription->GetDescriptions().begin();
    EXPECT_EQ(THERMOSTAT, it->first);
    EXPECT_STREQ("/Hae/Thermostat", it->second.c_str() );
    
}


TEST(HaeAboutDataTest, IsValid)
{
    QStatus status = ER_FAIL;
    HaeAboutData aboutData("en");

    EXPECT_FALSE(aboutData.IsValid());
    uint8_t appId[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
    status = aboutData.SetAppId(appId, 16);
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetDeviceId("fakeID");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetAppName("Application");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetManufacturer("Manufacturer");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetModelNumber("123456");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetDescription("A poetic description of this application");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetSoftwareVersion("0.1.2");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetLocation("upstairs bedroom");
    EXPECT_EQ(ER_OK, status);
    DeviceTypeDescription description;
    description.AddDeviceType(THERMOSTAT, "/Hae/Thermostat");
    status = aboutData.SetDeviceTypeDescription(&description);
    EXPECT_EQ(ER_OK, status);
    
    EXPECT_TRUE(aboutData.IsValid());
    

    EXPECT_FALSE(aboutData.IsValid("es"));

    status = aboutData.SetSupportedLanguage("es");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetAppName("aplicacion", "es");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetManufacturer("manufactura", "es");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetDescription("Una descripcion poetica de esta aplicacion", "es");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetLocation("habitación del segundo piso", "es");
    EXPECT_EQ(ER_OK, status);
    
    EXPECT_TRUE(aboutData.IsValid("es"));
}

    
TEST(HaeAboutDataTest, IsValid_Negative)
{
    QStatus status = ER_FAIL;
    HaeAboutData aboutData;
//Core fields are tested in Core test cases
    status = aboutData.SetDefaultLanguage("en");
    EXPECT_EQ(ER_OK, status);
    uint8_t appId[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
    status = aboutData.SetAppId(appId, 16);
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetDeviceId("fakeID");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetAppName("Application");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetManufacturer("Manufacturer");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetModelNumber("123456");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetDescription("A poetic description of this application");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetSoftwareVersion("0.1.2");
    EXPECT_EQ(ER_OK, status);
    
    //Hae Fields Missing
    EXPECT_FALSE(aboutData.IsValid());;
    status = aboutData.SetLocation("upstairs bedroom");
    EXPECT_EQ(ER_OK, status);
    DeviceTypeDescription description;
    description.AddDeviceType(THERMOSTAT, "/Hae/Thermostat");
    status = aboutData.SetDeviceTypeDescription(&description);
    EXPECT_EQ(ER_OK, status);
    
    

    // Now all required fields are set for english
    EXPECT_TRUE(aboutData.IsValid());

    status = aboutData.SetSupportedLanguage("es");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetAppName("aplicacion", "es");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetManufacturer("manufactura", "es");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetDescription("Una descripcion poetica de esta aplicacion", "es");
    EXPECT_EQ(ER_OK, status);
    //Missing HAE mandatory localized field, location
    EXPECT_FALSE(aboutData.IsValid("es"));
    
    status = aboutData.SetLocation("habitación del segundo piso", "es");
    EXPECT_EQ(ER_OK, status);
    
    EXPECT_TRUE(aboutData.IsValid("es"));

}

    
TEST(HaeAboutDataTest, GetAboutData)
{
    QStatus status = ER_FAIL;
    HaeAboutData aboutData("en");

    uint8_t appId[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
    status = aboutData.SetAppId(appId, 16);
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetDeviceId("fakeID");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetAppName("Application");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetManufacturer("Manufacture");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetModelNumber("123456");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetDescription("A poetic description of this application");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetSoftwareVersion("0.1.2");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetCountryOfProduction("Italy");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetCorporateBrand("Company");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetProductBrand("Product");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetLocation("upstairs bedroom");
    EXPECT_EQ(ER_OK, status);
    DeviceTypeDescription description;
    description.AddDeviceType(THERMOSTAT, "/Hae/Thermostat");
    status = aboutData.SetDeviceTypeDescription(&description);
    EXPECT_EQ(ER_OK, status);
    EXPECT_TRUE(aboutData.IsValid());

    status = aboutData.SetSupportedLanguage("es");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetAppName("aplicacion", "es");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetManufacturer("manufactura", "es");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetDescription("Una descripcion poetica de esta aplicacion", "es");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetLocation("habitación del segundo piso", "es");
    EXPECT_EQ(ER_OK, status);

    EXPECT_TRUE(aboutData.IsValid("es"));

    MsgArg aboutArg;
    status = aboutData.GetAboutData(&aboutArg);
    EXPECT_EQ(ER_OK, status);

//    printf("*****\n%s\n*****\n", aboutArg.ToString().c_str());

    MsgArg* args;

    aboutArg.GetElement("{sv}", AboutData::APP_ID, &args);
    int8_t* appIdOut;
    size_t appIdNum;
    args->Get("ay", &appIdNum, &appIdOut);
    ASSERT_EQ(16u, appIdNum);
    for (size_t i = 0; i < appIdNum; ++i) {
        EXPECT_EQ(appId[i], appIdOut[i]);
    }

    aboutArg.GetElement("{sv}", HaeAboutData::COUNTRY_OF_PRODUCTION.c_str(), &args);
    char* country;
    args->Get("s", &country);
    EXPECT_STREQ("Italy", country);

    aboutArg.GetElement("{sv}", HaeAboutData::CORPORATE_BRAND.c_str(), &args);
    char* company;
    args->Get("s", &company);
    EXPECT_STREQ("Company", company);

    aboutArg.GetElement("{sv}", HaeAboutData::PRODUCT_BRAND.c_str(), &args);
    char* brand;
    args->Get("s", &brand);
    EXPECT_STREQ("Product", brand);

    aboutArg.GetElement("{sv}", HaeAboutData::LOCATION.c_str(), &args);
    char* location;
    args->Get("s", &location);
    EXPECT_STREQ("upstairs bedroom", location);

    aboutArg.GetElement("{sv}", HaeAboutData::DEVICE_TYPE_DESCRIPTION.c_str(), &args);
//    printf("********\n%s\n********\n", args->ToString().c_str());

    MsgArg* entries;
    size_t elemSize = 0;
    status = args->Get("a(uo)", &elemSize, &entries);
    EXPECT_EQ(ER_OK, status);
    EXPECT_EQ(1, elemSize);
//    printf("********\n%s\n********\n", entries[0].ToString().c_str());

    DeviceType deviceType;
    char* objectPath;
    status = entries[0].Get("(uo)", &deviceType, &objectPath);
    EXPECT_EQ(ER_OK, status);
    EXPECT_EQ(THERMOSTAT, deviceType);
    EXPECT_STREQ("/Hae/Thermostat", objectPath );
}


TEST(HaeAboutDataTest, GetMsgArg_es_language)
{
    QStatus status = ER_FAIL;
    HaeAboutData aboutData("en");

    uint8_t appId[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
    status = aboutData.SetAppId(appId, 16);
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetDeviceId("fakeID");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetAppName("Application");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetManufacturer("Manufacture");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetModelNumber("123456");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetDescription("A poetic description of this application");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetSoftwareVersion("0.1.2");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetLocation("upstairs bedroom");
    EXPECT_EQ(ER_OK, status);
    DeviceTypeDescription description;
    description.AddDeviceType(THERMOSTAT, "/Hae/Thermostat");
    status = aboutData.SetDeviceTypeDescription(&description);
    EXPECT_EQ(ER_OK, status);
    EXPECT_TRUE(aboutData.IsValid());

    status = aboutData.SetSupportedLanguage("es");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetAppName("aplicacion", "es");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetManufacturer("manufactura", "es");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetDescription("Una descripcion poetica de esta aplicacion", "es");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetLocation("habitación del segundo piso", "es");
    EXPECT_EQ(ER_OK, status);

    EXPECT_TRUE(aboutData.IsValid("es"));

    MsgArg aboutArg;
    status = aboutData.GetAboutData(&aboutArg, "es");
    EXPECT_EQ(ER_OK, status);

    //printf("*****\n%s\n*****\n", aboutArg.ToString().c_str());

    MsgArg* args;

    aboutArg.GetElement("{sv}", HaeAboutData::LOCATION.c_str(), &args);
    char* location;
    args->Get("s", &location);
    EXPECT_STREQ("habitación del segundo piso", location);
}



TEST(HaeAboutDataTest, GetAnnouncedAboutData)
{
    QStatus status = ER_FAIL;
    HaeAboutData aboutData("en");

    uint8_t appId[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
    status = aboutData.SetAppId(appId, 16);
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetDeviceId("fakeID");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetAppName("Application");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetManufacturer("Manufacture");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetModelNumber("123456");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetDescription("A poetic description of this application");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetSoftwareVersion("0.1.2");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetLocation("upstairs bedroom");
    EXPECT_EQ(ER_OK, status);
    DeviceTypeDescription description;
    description.AddDeviceType(THERMOSTAT, "/Hae/Thermostat");
    status = aboutData.SetDeviceTypeDescription(&description);
    EXPECT_EQ(ER_OK, status);
    EXPECT_TRUE(aboutData.IsValid());

    MsgArg announceArg;
    status = aboutData.GetAnnouncedAboutData(&announceArg);
    EXPECT_EQ(ER_OK, status);

    MsgArg* args;



    announceArg.GetElement("{sv}", HaeAboutData::LOCATION.c_str(), &args);
    char* location;
    args->Get("s", &location);
    EXPECT_STREQ("upstairs bedroom", location);

    announceArg.GetElement("{sv}", HaeAboutData::DEVICE_TYPE_DESCRIPTION.c_str(), &args);

    MsgArg* entries;
    size_t elemSize = 0;
    status = args->Get("a(uo)", &elemSize, &entries);
    EXPECT_EQ(ER_OK, status);
    EXPECT_EQ(1, elemSize);

    DeviceType deviceType;
    char* objectPath;
    status = entries[0].Get("(uo)", &deviceType, &objectPath);
    EXPECT_EQ(ER_OK, status);
    EXPECT_EQ(THERMOSTAT, deviceType);
    EXPECT_STREQ("/Hae/Thermostat", objectPath );
}


TEST(HaeAboutDataTest, InitUsingMsgArgBadSignature) {
    QStatus status = ER_FAIL;
    HaeAboutData aboutData("en");
    MsgArg notADictionary("s", "incorrect type.");

    status = aboutData.CreatefromMsgArg(notADictionary);
    EXPECT_EQ(ER_BUS_SIGNATURE_MISMATCH, status);
}

TEST(HaeAboutDataTest, InitUsingMsgArg)
{
    QStatus status = ER_FAIL;
    HaeAboutData aboutData("en");

    uint8_t appId[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
    status = aboutData.SetAppId(appId, 16);
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetDeviceId("fakeID");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetAppName("Application");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetManufacturer("Manufacturer");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetModelNumber("123456");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetDescription("A poetic description of this application");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetSoftwareVersion("0.1.2");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetLocation("upstairs bedroom");
    EXPECT_EQ(ER_OK, status);
    DeviceTypeDescription description;
    description.AddDeviceType(THERMOSTAT, "/Hae/Thermostat");
    status = aboutData.SetDeviceTypeDescription(&description);
    EXPECT_EQ(ER_OK, status);
    EXPECT_TRUE(aboutData.IsValid());

    status = aboutData.SetSupportedLanguage("es");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetAppName("aplicacion", "es");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetManufacturer("manufactura", "es");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetLocation("habitación del segundo piso", "es");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetDescription("Una descripcion poetica de esta aplicacion", "es");
    EXPECT_EQ(ER_OK, status);
    status = aboutData.SetLocation("habitación del segundo piso", "es");
    EXPECT_EQ(ER_OK, status);
    EXPECT_TRUE(aboutData.IsValid("es"));

    MsgArg arg;
    status = arg.Set("s", "888-555-1234");
    EXPECT_EQ(ER_OK, status);

    status = aboutData.SetField("SupportNumber", arg);
    EXPECT_EQ(ER_OK, status);

    status = arg.Set("s", "800-555-4321");
    EXPECT_EQ(ER_OK, status);

    status = aboutData.SetField("SupportNumber", arg, "es");
    EXPECT_EQ(ER_OK, status);

    MsgArg aboutArg;
    aboutData.GetAboutData(&aboutArg);

    HaeAboutData aboutDataInit("en");
    status = aboutDataInit.CreatefromMsgArg(aboutArg);
    EXPECT_EQ(ER_OK, status);

    DeviceTypeDescription*  returnedDescription = new DeviceTypeDescription();
    status = aboutDataInit.GetDeviceTypeDescription( &returnedDescription);
    EXPECT_EQ(ER_OK, status);

    std::multimap<DeviceType, qcc::String>::const_iterator it = returnedDescription->GetDescriptions().begin();
    EXPECT_EQ(THERMOSTAT, it->first);
    EXPECT_STREQ("/Hae/Thermostat", it->second.c_str() );

    char* location;
    status = aboutData.GetLocation(&location);
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("upstairs bedroom", location);

    status = aboutData.GetLocation(&location, "es");
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("habitación del segundo piso", location);

}
    TEST(HaeAboutDataTest, CreateFromXml_fails_missingLocation) {
        QStatus status = ER_FAIL;
        HaeAboutData aboutData;
        qcc::String xml =
        "<AboutData>"
        "  <AppId>000102030405060708090A0B0C0D0E0C</AppId>"
        "  <DefaultLanguage>en</DefaultLanguage>"
        "  <DeviceName>My Device Name</DeviceName>"
        "  <DeviceName lang = 'es'>Nombre de mi dispositivo</DeviceName>"
        "  <DeviceId>baddeviceid</DeviceId>"
        "  <AppName>My Application Name</AppName>"
        "  <AppName lang = 'es'>Mi Nombre de la aplicación</AppName>"
        "  <Manufacturer>Company</Manufacturer>"
        "  <Manufacturer lang = 'es'>Empresa</Manufacturer>"
        "  <ModelNumber>Wxfy388i</ModelNumber>"
        "  <Description>A detailed description provided by the application.</Description>"
        "  <Description lang = 'es'>Una descripción detallada proporcionada por la aplicación.</Description>"
        "  <DateOfManufacture>2014-01-08</DateOfManufacture>"
        "  <SoftwareVersion>1.0.0</SoftwareVersion>"
        "  <HardwareVersion>1.0.0</HardwareVersion>"
        "  <SupportUrl>www.example.com</SupportUrl>"
        "  <UserDefinedTag>Can only accept strings anything other than strings must be done using the AboutData Class SetField method</UserDefinedTag>"
        "  <UserDefinedTag lang='es'>Sólo se puede aceptar cadenas distintas de cadenas nada debe hacerse utilizando el método AboutData Clase SetField</UserDefinedTag>"
//        "  <Location>upstairs bedroom</Location>"
//        "  <Location lang='es'>habitación del segundo piso</Location>"
        "  <DeviceTypeDescription><TypeDescription><device_type>6</device_type><object_path>/Hae/Thermostat</object_path></TypeDescription></DeviceTypeDescription>"
        "</AboutData>";
        status = aboutData.CreateFromXml(xml);
        EXPECT_EQ(ER_ABOUT_ABOUTDATA_MISSING_REQUIRED_FIELD, status);
    }



TEST(HaeAboutDataTest, CreateFromXml_fails_missingDeviceTypeDescription) {
        QStatus status = ER_FAIL;
        HaeAboutData aboutData;
        qcc::String xml =
        "<AboutData>"
        "  <AppId>000102030405060708090A0B0C0D0E0C</AppId>"
        "  <DefaultLanguage>en</DefaultLanguage>"
        "  <DeviceName>My Device Name</DeviceName>"
        "  <DeviceName lang = 'es'>Nombre de mi dispositivo</DeviceName>"
        "  <DeviceId>baddeviceid</DeviceId>"
        "  <AppName>My Application Name</AppName>"
        "  <AppName lang = 'es'>Mi Nombre de la aplicación</AppName>"
        "  <Manufacturer>Company</Manufacturer>"
        "  <Manufacturer lang = 'es'>Empresa</Manufacturer>"
        "  <ModelNumber>Wxfy388i</ModelNumber>"
        "  <Description>A detailed description provided by the application.</Description>"
        "  <Description lang = 'es'>Una descripción detallada proporcionada por la aplicación.</Description>"
        "  <DateOfManufacture>2014-01-08</DateOfManufacture>"
        "  <SoftwareVersion>1.0.0</SoftwareVersion>"
        "  <HardwareVersion>1.0.0</HardwareVersion>"
        "  <SupportUrl>www.example.com</SupportUrl>"
        "  <UserDefinedTag>Can only accept strings anything other than strings must be done using the AboutData Class SetField method</UserDefinedTag>"
        "  <UserDefinedTag lang='es'>Sólo se puede aceptar cadenas distintas de cadenas nada debe hacerse utilizando el método AboutData Clase SetField</UserDefinedTag>"
        "  <Location>upstairs bedroom</Location>"
        "  <Location lang='es'>habitación del segundo piso</Location>"
//        "  <DeviceTypeDescription><TypeDescription><device_type>6</device_type><object_path>/Hae/Thermostat</object_path></TypeDescription></DeviceTypeDescription>"
        "</AboutData>";
        status = aboutData.CreateFromXml(xml);
        EXPECT_EQ(ER_ABOUT_ABOUTDATA_MISSING_REQUIRED_FIELD, status);
}

TEST(HaeAboutDataTest, CreateFromXml_fails_missingDeviceTypeDescriptionStructureTag) {
        QStatus status = ER_FAIL;
        HaeAboutData aboutData;
        qcc::String xml =
        "<AboutData>"
        "  <AppId>000102030405060708090A0B0C0D0E0C</AppId>"
        "  <DefaultLanguage>en</DefaultLanguage>"
        "  <DeviceName>My Device Name</DeviceName>"
        "  <DeviceName lang = 'es'>Nombre de mi dispositivo</DeviceName>"
        "  <DeviceId>baddeviceid</DeviceId>"
        "  <AppName>My Application Name</AppName>"
        "  <AppName lang = 'es'>Mi Nombre de la aplicación</AppName>"
        "  <Manufacturer>Company</Manufacturer>"
        "  <Manufacturer lang = 'es'>Empresa</Manufacturer>"
        "  <ModelNumber>Wxfy388i</ModelNumber>"
        "  <Description>A detailed description provided by the application.</Description>"
        "  <Description lang = 'es'>Una descripción detallada proporcionada por la aplicación.</Description>"
        "  <DateOfManufacture>2014-01-08</DateOfManufacture>"
        "  <SoftwareVersion>1.0.0</SoftwareVersion>"
        "  <HardwareVersion>1.0.0</HardwareVersion>"
        "  <SupportUrl>www.example.com</SupportUrl>"
        "  <UserDefinedTag>Can only accept strings anything other than strings must be done using the AboutData Class SetField method</UserDefinedTag>"
        "  <UserDefinedTag lang='es'>Sólo se puede aceptar cadenas distintas de cadenas nada debe hacerse utilizando el método AboutData Clase SetField</UserDefinedTag>"
        "  <Location>upstairs bedroom</Location>"
        "  <Location lang='es'>habitación del segundo piso</Location>"
        "  <DeviceTypeDescription><device_type>6</device_type><object_path>/Hae/Thermostat</object_path></DeviceTypeDescription>"
        "</AboutData>";
        status = aboutData.CreateFromXml(xml);
        EXPECT_EQ(ER_ABOUT_ABOUTDATA_MISSING_REQUIRED_FIELD, status);
    }

TEST(HaeAboutDataTest, CreateFromXml_fails_stringDeviceType) {
        QStatus status = ER_FAIL;
        HaeAboutData aboutData;
        qcc::String xml =
        "<AboutData>"
        "  <AppId>000102030405060708090A0B0C0D0E0C</AppId>"
        "  <DefaultLanguage>en</DefaultLanguage>"
        "  <DeviceName>My Device Name</DeviceName>"
        "  <DeviceName lang = 'es'>Nombre de mi dispositivo</DeviceName>"
        "  <DeviceId>baddeviceid</DeviceId>"
        "  <AppName>My Application Name</AppName>"
        "  <AppName lang = 'es'>Mi Nombre de la aplicación</AppName>"
        "  <Manufacturer>Company</Manufacturer>"
        "  <Manufacturer lang = 'es'>Empresa</Manufacturer>"
        "  <ModelNumber>Wxfy388i</ModelNumber>"
        "  <Description>A detailed description provided by the application.</Description>"
        "  <Description lang = 'es'>Una descripción detallada proporcionada por la aplicación.</Description>"
        "  <DateOfManufacture>2014-01-08</DateOfManufacture>"
        "  <SoftwareVersion>1.0.0</SoftwareVersion>"
        "  <HardwareVersion>1.0.0</HardwareVersion>"
        "  <SupportUrl>www.example.com</SupportUrl>"
        "  <UserDefinedTag>Can only accept strings anything other than strings must be done using the AboutData Class SetField method</UserDefinedTag>"
        "  <UserDefinedTag lang='es'>Sólo se puede aceptar cadenas distintas de cadenas nada debe hacerse utilizando el método AboutData Clase SetField</UserDefinedTag>"
        "  <Location>upstairs bedroom</Location>"
        "  <Location lang='es'>habitación del segundo piso</Location>"
    "  <DeviceTypeDescription><TypeDescription><device_type>THERMOSTAT</device_type><object_path>/Hae/Thermostat</object_path></TypeDescription></DeviceTypeDescription>"
        "</AboutData>";
        status = aboutData.CreateFromXml(xml);
        EXPECT_EQ(ER_ABOUT_ABOUTDATA_MISSING_REQUIRED_FIELD, status);
    }



TEST(HaeAboutDataTest, CreateFromXml_from_qcc_string) {
    QStatus status = ER_FAIL;
    HaeAboutData aboutData;
    qcc::String xml =
        "<AboutData>"
        "  <AppId>000102030405060708090A0B0C0D0E0C</AppId>"
        "  <DefaultLanguage>en</DefaultLanguage>"
        "  <DeviceName>My Device Name</DeviceName>"
        "  <DeviceName lang = 'es'>Nombre de mi dispositivo</DeviceName>"
        "  <DeviceId>baddeviceid</DeviceId>"
        "  <AppName>My Application Name</AppName>"
        "  <AppName lang = 'es'>Mi Nombre de la aplicación</AppName>"
        "  <Manufacturer>Company</Manufacturer>"
        "  <Manufacturer lang = 'es'>Empresa</Manufacturer>"
        "  <ModelNumber>Wxfy388i</ModelNumber>"
        "  <Description>A detailed description provided by the application.</Description>"
        "  <Description lang = 'es'>Una descripción detallada proporcionada por la aplicación.</Description>"
        "  <DateOfManufacture>2014-01-08</DateOfManufacture>"
        "  <SoftwareVersion>1.0.0</SoftwareVersion>"
        "  <HardwareVersion>1.0.0</HardwareVersion>"
        "  <SupportUrl>www.example.com</SupportUrl>"
        "  <UserDefinedTag>Can only accept strings anything other than strings must be done using the AboutData Class SetField method</UserDefinedTag>"
        "  <UserDefinedTag lang='es'>Sólo se puede aceptar cadenas distintas de cadenas nada debe hacerse utilizando el método AboutData Clase SetField</UserDefinedTag>"
        "  <Location>upstairs bedroom</Location>"
        "  <Location lang='es'>habitación del segundo piso</Location>"
        "  <DeviceTypeDescription><TypeDescription><device_type>6</device_type><object_path>/Hae/Thermostat</object_path></TypeDescription></DeviceTypeDescription>"
        "</AboutData>";
    status = aboutData.CreateFromXml(xml);
    EXPECT_EQ(ER_OK, status);

    MsgArg aboutArg;
    status = aboutData.GetAboutData(&aboutArg);
    EXPECT_EQ(ER_OK, status);

//    printf("*****\n%s\n*****\n", aboutArg.ToString().c_str());

    char* location;
    status = aboutData.GetLocation(&location);
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("upstairs bedroom", location);

    status = aboutData.GetLocation(&location, "es");
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("habitación del segundo piso", location);

    DeviceTypeDescription*  returnedDescription = new DeviceTypeDescription();
    status = aboutData.GetDeviceTypeDescription( &returnedDescription);
    EXPECT_EQ(ER_OK, status);

    std::multimap<DeviceType, qcc::String>::const_iterator it = returnedDescription->GetDescriptions().begin();
    EXPECT_EQ(THERMOSTAT, it->first);
    EXPECT_STREQ("/Hae/Thermostat", it->second.c_str() );
}


/*
 * This test is identical to HaeAboutDataTest.CreateFromXml_from_qcc_string except
 * the xml string is passed in as a const char* not a qcc::String
 */
TEST(HaeAboutDataTest, CreateFromXml_from_char_string) {
    QStatus status = ER_FAIL;
    HaeAboutData aboutData;
    const char* xml =
        "<AboutData>"
        "  <AppId>000102030405060708090A0B0C0D0E0C</AppId>"
        "  <DefaultLanguage>en</DefaultLanguage>"
        "  <DeviceName>My Device Name</DeviceName>"
        "  <DeviceName lang = 'es'>Nombre de mi dispositivo</DeviceName>"
        "  <DeviceId>baddeviceid</DeviceId>"
        "  <AppName>My Application Name</AppName>"
        "  <AppName lang = 'es'>Mi Nombre de la aplicación</AppName>"
        "  <Manufacturer>Company</Manufacturer>"
        "  <Manufacturer lang = 'es'>Empresa</Manufacturer>"
        "  <ModelNumber>Wxfy388i</ModelNumber>"
        "  <Description>A detailed description provided by the application.</Description>"
        "  <Description lang = 'es'>Una descripción detallada proporcionada por la aplicación.</Description>"
        "  <DateOfManufacture>2014-01-08</DateOfManufacture>"
        "  <SoftwareVersion>1.0.0</SoftwareVersion>"
        "  <HardwareVersion>1.0.0</HardwareVersion>"
        "  <SupportUrl>www.example.com</SupportUrl>"
        "  <UserDefinedTag>Can only accept strings anything other than strings must be done using the AboutData Class SetField method</UserDefinedTag>"
        "  <UserDefinedTag lang='es'>Sólo se puede aceptar cadenas distintas de cadenas nada debe hacerse utilizando el método AboutData Clase SetField</UserDefinedTag>"
        "  <Location>upstairs bedroom</Location>"
        "  <Location lang='es'>habitación del segundo piso</Location>"
        "  <DeviceTypeDescription><TypeDescription><device_type>6</device_type><object_path>/Hae/Thermostat</object_path></TypeDescription></DeviceTypeDescription>"
        "</AboutData>";
    status = aboutData.CreateFromXml(xml);
    EXPECT_EQ(ER_OK, status);

    char* location;
    status = aboutData.GetLocation(&location);
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("upstairs bedroom", location);

    status = aboutData.GetLocation(&location, "es");
    EXPECT_EQ(ER_OK, status);
    EXPECT_STREQ("habitación del segundo piso", location);

    DeviceTypeDescription*  returnedDescription = new DeviceTypeDescription();
    status = aboutData.GetDeviceTypeDescription( &returnedDescription);
    EXPECT_EQ(ER_OK, status);

    std::multimap<DeviceType, qcc::String>::const_iterator it = returnedDescription->GetDescriptions().begin();
    EXPECT_EQ(THERMOSTAT, it->first);
    EXPECT_STREQ("/Hae/Thermostat", it->second.c_str() );
}


TEST(HaeAboutDataTest, CreateFromXml_multiple_device_types) {
        QStatus status = ER_FAIL;
        HaeAboutData aboutData;
        qcc::String xml =
        "<AboutData>"
        "  <AppId>000102030405060708090A0B0C0D0E0C</AppId>"
        "  <DefaultLanguage>en</DefaultLanguage>"
        "  <DeviceName>My Device Name</DeviceName>"
        "  <DeviceName lang = 'es'>Nombre de mi dispositivo</DeviceName>"
        "  <DeviceId>baddeviceid</DeviceId>"
        "  <AppName>My Application Name</AppName>"
        "  <AppName lang = 'es'>Mi Nombre de la aplicación</AppName>"
        "  <Manufacturer>Company</Manufacturer>"
        "  <Manufacturer lang = 'es'>Empresa</Manufacturer>"
        "  <ModelNumber>Wxfy388i</ModelNumber>"
        "  <Description>A detailed description provided by the application.</Description>"
        "  <Description lang = 'es'>Una descripción detallada proporcionada por la aplicación.</Description>"
        "  <DateOfManufacture>2014-01-08</DateOfManufacture>"
        "  <SoftwareVersion>1.0.0</SoftwareVersion>"
        "  <HardwareVersion>1.0.0</HardwareVersion>"
        "  <SupportUrl>www.example.com</SupportUrl>"
        "  <UserDefinedTag>Can only accept strings anything other than strings must be done using the AboutData Class SetField method</UserDefinedTag>"
        "  <UserDefinedTag lang='es'>Sólo se puede aceptar cadenas distintas de cadenas nada debe hacerse utilizando el método AboutData Clase SetField</UserDefinedTag>"
        "  <Location>upstairs bedroom</Location>"
        "  <Location lang='es'>habitación del segundo piso</Location>"
        "  <DeviceTypeDescription><TypeDescription><device_type>2</device_type><object_path>/Hae/Alpha</object_path></TypeDescription><TypeDescription><device_type>3</device_type><object_path>/Hae/Beta</object_path></TypeDescription><TypeDescription><device_type>4</device_type><object_path>/Hae/Gamma</object_path></TypeDescription></DeviceTypeDescription>"
        "</AboutData>";
        status = aboutData.CreateFromXml(xml);
        EXPECT_EQ(ER_OK, status);

        MsgArg aboutArg;
        status = aboutData.GetAboutData(&aboutArg);
        EXPECT_EQ(ER_OK, status);

//        printf("*****\n%s\n*****\n", aboutArg.ToString().c_str());

        char* location;
        status = aboutData.GetLocation(&location);
        EXPECT_EQ(ER_OK, status);
        EXPECT_STREQ("upstairs bedroom", location);

        status = aboutData.GetLocation(&location, "es");
        EXPECT_EQ(ER_OK, status);
        EXPECT_STREQ("habitación del segundo piso", location);

        DeviceTypeDescription*  returnedDescription = new DeviceTypeDescription();
        status = aboutData.GetDeviceTypeDescription( &returnedDescription);
        EXPECT_EQ(ER_OK, status);

        std::multimap<DeviceType, qcc::String> returnedDescriptions = returnedDescription->GetDescriptions();
        EXPECT_EQ(3, returnedDescriptions.size());
        EXPECT_EQ(1, returnedDescriptions.count(REFRIGERATOR));
        EXPECT_EQ(1, returnedDescriptions.count(FREEZER));
        EXPECT_EQ(1, returnedDescriptions.count(ICE_MAKER));

        std::multimap<DeviceType, qcc::String>::const_iterator it = returnedDescriptions.find(REFRIGERATOR);
        EXPECT_STREQ("/Hae/Alpha", it->second.c_str() );
    }



}//namespace services
}//namespace ajn
