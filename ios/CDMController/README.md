#Build Steps
 1. Build AllJoyn Core for your architecture using the alljoyn_darwin xcode project
 2. Build the AllJoynFramework_iOS xcode project
 3. Build the cdm_darwin xcode project
 4. Build and run this project

#Known Issues
## No devices appear in the list
This can occur on subsequent builds. 
A workaround is to uninstall the application and then reinstall it i.e. a fresh install.