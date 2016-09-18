Example Project Application for iOS
===================================

1. Introduction

Ezio Mobile SDK Example is a sample iOS application designed to demonstrate
the basics of creating an iOS application based on the Ezio Mobile SDK.

The application demonstrates the following behavior:
* Security guideline compliance of EzioMobileSDK_security_guideline.pdf.
* How to create a Token (requires a configured EPS).
* How to list tokens.
* How to generate an OTP that can be verified by a server.

2. Prerequisites

* Mac
* Xcode

3. Open and setup the project

In Xcode:
* File -> Open -> EzioMobileSdkCapExample.xcodeproj
* Add the EzioMobile.framework in the project's "Link Binary with Libraries" list.

4. Configure the App

The application will not work as provided.  It first must be setup to be
provisioned with the user credentials.  To enable this, perform the following
steps:
* Perform an "Allocate Application" operation in the EPS to get the PIN and
  registration code.  See Appendix for how to do this in a test environemnt.
* Edit FakeUI.m to add the PIN, registration code, etc.
* Edit FakeAppData.m to add your EPS settings, etc.
* Edit EMTlsConfiguration in Example.m if the security of the network
  connection needs to be lowered (e.g. using an http instead of https).

5. Run the Example App

The application prints the results of 3 tasks.
    1. Jailbreak detection - Check if the device is jailbroken. Abort app if jailbroken.	
    2. Provisioning - Attempts to provisioning the device.
    3. Generate Otp - Generates a CAP Mode 2 OTP for all available tokens.

---------------------------------------
Appendix

1. Security Guidelines

This project follows all relevant security guidelines established in the
EzioMobileSDK_security_guidelines.pdf document.  All guidelines followed are
commented inside the source code.  For project specific guidelines, the
following are followed:

* GEN05. No debug symbols

2. EPS 1.X Allocate Application

NOTE: This only serves as a quick reference.  See the EPS 1.X Integration
Guide for further details.

The following URL can be used in a web browser (or wget, etc.) to request the
EPS to allocate an application.  However, the following must be modified:
* The path up to '?' must be changed to point to your EPS.
* The ISSUER must be updated to match the issuer of the EPS.

https://localhost/eps/EnrolmentServlet?METHOD=ALLOCATEAPPLICATION&CARDTYPE=3600&ISSUER=Test1&CARDSTATE=INACTIVE&FUNCTIONS=OTP,%20SIGN&EXPIREDATE=20200101&NAME=Example&CARDNUMBER=1234123412341234&GIDVERSION=01

The response will contain the PIN and registration code if successful.

3. EPS 2.X Enroll Application

NOTE: This only serves as a quick reference.  See the EPS 2.X Integration
Guide for further details.

The following URL can be used to request the EPS to enroll the user with a new
device.  However, the following must be modified:
* The path up to 'https://localhost/" must be changed to point to your EPS.

https://localhost/enroller/api/enrollment/cap/enroll

The following XML payload must be sent as the data portion of the HTTP POST.
However, the following must be modified:
* userId - The name of the user to enroll
* pan - The PAN (card number)
* psn - The PSN (a 2 digit sequence number)
* domain - The EPS domain for CAP
The combination of the PAN and PSN must be unique.

    <?xml version="1.0" encoding="UTF-8" standalone="yes"?>
    <capToken xmlns="http://gemalto.com/ezio/mobile/eps/api">
        <userId>TODO</userId>
        <pan>TODO</pan>
        <psn>TODO</psn>
        <domain>TODO</domain>
        <activationDate>2012-12-31T15:23:59-08:00</activationDate>
        <expirationDate>2023-12-31T15:23:59-08:00</expirationDate>
        <activationState>ACTIVE</activationState>
        <externalProvisioningMeta/>
    </capToken>

The "Content-Type" must be set to "application/xml"

The response will contain the PIN and registration code if successful.

Example:
    wget --header="Content-Type: application/xml" --post-data "<data>" <url> -O -
