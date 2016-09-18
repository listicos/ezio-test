Example Project Application for iOS
===================================

1. Introduction

Ezio Mobile SDK Example is a sample iOS application designed to demonstrate
the basics of creating an iOS application based on the Ezio Mobile SDK.

The application demonstrates the following behavior:
* Security guideline compliance of EzioMobileSDK_security_guideline.pdf.
* How to register to the OOB server.
* How to fetch a message.
* How to acknowledge a message.
* How to respond to a Transaction Verification.
* How to reply a user message.

Most of the code related to OOB functionality are located in ViewController.m .

And the application specific data are located in FakeAppData.m . Values inside
this file must not be used by a real application because they are not universal settings.

2. Prerequisites

* Mac
* Xcode

3. Open and setup the project

In Xcode:
* File -> Open -> OOBSampleApp.xcodeproj
* Add the EzioMobile.framework in the project's "Link Binary with Libraries" list.

4. Configure the App

The application will not work as provided.  It first must be setup to be
provisioned with the user credentials.  To enable this, perform the following
steps:
* Edit FakeAppData.m to add your OOB settings and Activation Code, etc.
* Edit EMTlsConfiguration in ViewController.m if the security of the network
  connection needs to be lowered.

  Note: the 'Debug' version of the library should be used in case of Tls is 
  configured to allow insecure connection (http), hostname mismatch or self-signed
  certificate.

5. Run the Example App
* It is recommended to uninstall other Ezio Mobile example applications installed
  previously before running this App.

6. Enroll
* Perform an "Enrolment" operation to the OOBS to get the registration code
  and client Id. See Appendix for how to do this in a test environment.

7. Register
* Register the client.

8. Dispatch message to OOB Server
* Request can be sent to OOB server, and the mobile application
  will be able to retrieve the message using Ezio Mobile SDK.

9. Fetch messages
* There are 3 types of messages which can be received by the client, namely : 
TransactionVerify, User-Message, Generic Message. Refer OOB Integration Guide for details.
  
---------------------------------------
Appendix

1. Security Guidelines

This project follows all relevant security guidelines established in the
EzioMobileSDK_security_guidelines.pdf document.  All guidelines are followed
are commented inside the source code.  For project specific guidelines, the
following are followed:

* GEN01. Code obfuscation
* GEN05. No debug symbols

2. Register to the OOBS

NOTE: This only serves as a quick reference. See the OOBS Integration
Guide for further details.

The following URL can be used to request the OOBS to register the user with a new
device.  However, the following must be modified:
* The path up to 'https://localhost/" must be changed to point to your OOBS.

https://localhost/oobs-dispatcher/domains/default/users/my-user/applications/OobsTest/register

The following XML payload must be sent as the data portion of the HTTP POST.
However, the following must be modified:
* registrationCode - The registration code. OOBS should return the same registration code if request succeed.

    <?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>
    <RegisterRequest xmlns=\"http://gemalto.com/ipms/dispatcher/api/transport\" >
     <registrationSecurityMethod>REG_CODE</registrationSecurityMethod>
     <registrationCode>TODO</registrationCode>
     <validityPeriodSecs>600</validityPeriodSecs>
     <notificationProfiles />
    </RegisterRequest>

The "Content-Type" must be set to "application/xml"
The "Authorization" must be set to "Basic XXXXXXXXXXXXXXX"

The response will contain the registration code and client Id if successful.

Example:
    wget --header="Authorization: Basic XXXXXXXXXXXXXXX" --header="Content-Type: application/xml" --post-data "<data>" <url> -O -
